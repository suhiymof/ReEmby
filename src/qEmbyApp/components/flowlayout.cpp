#include "flowlayout.h"
#include <QWidget>

FlowLayout::FlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::FlowLayout(int margin, int hSpacing, int vSpacing)
    : m_hSpace(hSpacing), m_vSpace(vSpacing)
{
    setContentsMargins(margin, margin, margin, margin);
}

FlowLayout::~FlowLayout()
{
    while (!itemList.isEmpty())
        delete itemList.takeFirst();
}

void FlowLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
    invalidate();
}

int FlowLayout::horizontalSpacing() const
{
    if (m_hSpace >= 0) {
        return m_hSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int FlowLayout::verticalSpacing() const
{
    if (m_vSpace >= 0) {
        return m_vSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

int FlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size()) {
        QLayoutItem *item = itemList.takeAt(index);
        invalidate();
        return item;
    }
    return nullptr;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return { };
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}

void FlowLayout::invalidate()
{
    QLayout::invalidate();
    updateParentGeometry();
}

void FlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

void FlowLayout::setFirstLineTrailingSpacing(int spacing)
{
    const int safeSpacing = qMax(0, spacing);
    if (m_firstLineTrailingSpacing == safeSpacing) {
        return;
    }

    m_firstLineTrailingSpacing = safeSpacing;
    invalidate();
}

int FlowLayout::firstLineTrailingSpacing() const
{
    return m_firstLineTrailingSpacing;
}

QSize FlowLayout::sizeHint() const
{
    QSize size = minimumSize();
    int width = -1;

    if (const auto *parentWidget = qobject_cast<const QWidget *>(parent())) {
        width = parentWidget->contentsRect().width();
        const QWidget *p = parentWidget->parentWidget();
        while (width <= 0 && p) {
            width = p->contentsRect().width();
            p = p->parentWidget();
        }
    } else if (geometry().isValid()) {
        width = geometry().width();
    }

    // 估算行数用的宽度：setup 阶段（widget 尚未布局）所有祖先宽度都还是 0。
    // 此时若直接跳过 heightForWidth，sizeHint 只剩 minimumSize()（单个 item 的
    // 最小尺寸）→ 外层 QVBoxLayout 据此分配的高度不足 → 内容被裁至不可见
    // （详情页行动作按钮整行消失的根因）。
    //
    // 关键：始终用兜底 width 算行数，**不**信任 parentWidget 链——因为祖先链
    // 上常会"碰巧"找到已显示的祖先（比如主窗口 1920px），让 heightForWidth
    // 算出"1 行 36px"（所有按钮装一行），QVBoxLayout 据此给 36px 高度，按钮
    // 36px 高+边距 → 仍被裁。setup 阶段**没有**可信的"真实可用宽度"，必须用
    // 一个"保证多于 1 行"的窄宽度估算（让 buttons 多换几次行 → 高度偏高估）。
    // 布局稳定后 hasHeightForWidth()=true，外层带真实宽度重算、收敛。
    //
    // 用 400 而非更小：详情页典型文本容器宽 ~600，400 算 2-3 行（80-120px），
    // 实际需要 2 行 ~72px，偏高估 ~10-50px → 安全空白但不裁切。
    constexpr int kFallbackWidthForHeight = 400;
    size.setHeight(heightForWidth(kFallbackWidthForHeight));

    if (width > 0) {
        size.setWidth(qMax(size.width(), width));
    }

    return size;
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    for (const QLayoutItem *item : itemList) {
        if (const QWidget *wid = item->widget(); wid && wid->isHidden()) {
            continue;
        }
        size = size.expandedTo(item->minimumSize());
    }

    const QMargins margins = contentsMargins();
    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    return size;
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    for (QLayoutItem *item : itemList) {
        const QWidget *wid = item->widget();
        if (wid && wid->isHidden()) {
            continue;
        }
        int spaceX = horizontalSpacing();
        if (spaceX == -1) {
            spaceX = wid ? wid->style()->layoutSpacing(
                               QSizePolicy::PushButton,
                               QSizePolicy::PushButton,
                               Qt::Horizontal)
                         : 0;
        }
        int spaceY = verticalSpacing();
        if (spaceY == -1) {
            spaceY = wid ? wid->style()->layoutSpacing(
                               QSizePolicy::PushButton,
                               QSizePolicy::PushButton,
                               Qt::Vertical)
                         : 0;
        }

        const int lineRight = (y == effectiveRect.y())
                                  ? qMax(effectiveRect.x(),
                                         effectiveRect.right() - m_firstLineTrailingSpacing)
                                  : effectiveRect.right();
        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > lineRight && lineHeight > 0) {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent) {
        return -1;
    } else if (parent->isWidgetType()) {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    } else {
        return static_cast<QLayout *>(parent)->spacing();
    }
}

void FlowLayout::updateParentGeometry() const
{
    auto *parentWidget = qobject_cast<QWidget *>(parent());
    if (!parentWidget) {
        return;
    }

    parentWidget->updateGeometry();
    if (QWidget *outerWidget = parentWidget->parentWidget()) {
        outerWidget->updateGeometry();
    }
}
