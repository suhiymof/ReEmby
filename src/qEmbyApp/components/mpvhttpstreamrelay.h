#ifndef MPVHTTPSTREAMRELAY_H
#define MPVHTTPSTREAMRELAY_H

#include <QByteArray>
#include <QHash>
#include <QNetworkProxy>
#include <QObject>
#include <QUrl>
#include <QVector>

class QNetworkAccessManager;
class QNetworkReply;
class QTimer;
class QTcpServer;
class QTcpSocket;

// Local HTTP proxy sitting between mpv and the remote stream.
//
// This used to be a pure pass-through: every Range request from mpv was
// forwarded upstream verbatim, and the moment mpv closed its connection the
// upstream reply was aborted and whatever had already been downloaded was
// thrown away.
//
// That breaks sources whose audio track is stored apart from the video
// (non-interleaved layout, common for WEB-DL MP4). libavformat then asks for
// the audio in tiny chunks that alternate with the video, so every chunk costs
// a full round trip; when a round trip takes ~1.75s and one chunk only carries
// ~0.1s of audio, playback starves no matter how large the mpv buffers are.
//
// The relay now keeps a byte-range cache between mpv and upstream:
//   * upstream reads are shared by every mpv connection and keyed by absolute
//     file offset, so a read starting at X can serve any later request that
//     falls inside [X, X + readahead);
//   * when mpv disconnects mid-stream the upstream read is NOT aborted -- it
//     keeps going up to its limit and feeds the cache ("finish the read").
//     The next request for a nearby offset is answered from memory in
//     microseconds instead of paying another round trip.
class MpvHttpStreamRelay : public QObject {
    Q_OBJECT
public:
    explicit MpvHttpStreamRelay(QObject *parent = nullptr);
    ~MpvHttpStreamRelay() override;

    QUrl prepare(const QUrl &targetUrl, const QString &serverId,
                 const QNetworkProxy &proxy,
                 const QString &userAgent = QString(),
                 qint64 readaheadBytes = 0);
    void stop();

Q_SIGNALS:
    void upstreamSpeedChanged(qint64 bytesPerSecond);

private:
    // One contiguous run of cached bytes, keyed by absolute file offset. The
    // list is kept sorted by begin and adjacent/overlapping runs are merged.
    struct CacheBlock {
        qint64 begin = 0;
        QByteArray data;
    };

    struct ConnectionState {
        QByteArray buffer;
        bool headOnly = false;
        bool headersSent = false;
        bool finished = false; // response fully written, socket is closing

        // Pass-through mode: HEAD requests, or an upstream that ignores Range.
        bool cacheMode = false;
        QNetworkReply *reply = nullptr;
        bool upstreamFinished = false;

        // Cached mode.
        qint64 reqBegin = 0;       // absolute offset mpv asked for
        qint64 reqEnd = -1;        // inclusive; -1 = open ended (through EOF)
        qint64 needPos = 0;        // next absolute offset still to be sent
        qint64 servedFromCache = 0;
        QByteArray originalRange;
        QByteArray originalAccept;
    };

    void onNewConnection();
    void onSocketReadyRead(QTcpSocket *socket);
    void onSocketDisconnected(QTcpSocket *socket);
    void processRequest(QTcpSocket *socket, const QByteArray &requestData);

    // --- pass-through path (fallback, unchanged behaviour) ---
    void startPassThrough(QTcpSocket *socket, const QByteArray &rangeHeader,
                          const QByteArray &acceptHeader, bool headOnly);
    void sendReplyHeaders(QTcpSocket *socket);
    void pumpReplyToSocket(QTcpSocket *socket);

    // --- cached path ---
    void resetCache();
    void appendToCache(const QByteArray &data);
    void normalizeCache();
    void recountCachedBytes();
    void evictCacheIfNeeded();
    int cacheBlockContaining(qint64 pos) const;
    void pumpCacheToSocket(QTcpSocket *socket);
    void sendCacheHeaders(QTcpSocket *socket);
    void finishCacheConnection(QTcpSocket *socket);
    void broadcastCachedData();

    // --- shared upstream read ---
    bool startFetch(qint64 pos);
    void ensureFetchFrom(qint64 pos);
    void scheduleFetch(qint64 pos);
    void runScheduledFetch();
    void resumeStalledConnections();
    bool followRedirect(QNetworkReply *reply);
    QUrl effectiveUpstreamUrl() const;
    void parseFetchHeaders();
    void onFetchReadyRead();
    void onFetchFinished();
    void releaseFetch();
    void demoteToPassThrough();

    void writeError(QTcpSocket *socket, int statusCode, const QByteArray &message);
    void closeConnection(QTcpSocket *socket);
    void recordRelayedBytes(qint64 bytes);

    bool parseRangeHeader(const QByteArray &value, qint64 *begin, qint64 *end) const;
    static QByteArray reasonPhrase(int statusCode);
    static bool isHopByHopHeader(QByteArray name);

    QTcpServer *m_server = nullptr;
    QNetworkAccessManager *m_network = nullptr;
    QTimer *m_speedTimer = nullptr;
    QHash<QTcpSocket *, ConnectionState> m_connections;
    QUrl m_targetUrl;
    QString m_serverId;
    QString m_streamToken;
    QString m_upstreamUserAgent;
    // Resolved redirect target. QNetworkAccessManager's default redirect policy
    // (NoLessSafeRedirectPolicy) refuses the https -> http hop this server chain
    // needs -- Emby redirects to an OpenList direct link, which redirects again
    // to a pre-signed object-storage URL. Redirects are therefore followed by
    // hand, and the resolved target is reused for the later reads of the same
    // media (it is dropped again when it starts being rejected, since the
    // pre-signed URL expires).
    QUrl m_redirectTarget;
    int m_redirectDepth = 0;
    qint64 m_bytesRelayedSinceLastTick = 0;

    // Byte-range cache (memory only for now; see tools/relay-design.md).
    QVector<CacheBlock> m_cache;
    qint64 m_cachedBytes = 0;
    qint64 m_totalSize = -1;          // from upstream Content-Range; -1 = unknown
    QByteArray m_contentType;
    bool m_rangeUnsupported = false;  // upstream answered 200 to a Range request

    // Shared upstream read: one at a time for the whole media.
    QNetworkReply *m_fetch = nullptr;
    qint64 m_fetchPos = 0;            // next absolute offset to be appended
    qint64 m_fetchLimit = 0;          // read no further than this
    qint64 m_readaheadBytes = 0;
    qint64 m_scheduledFetchPos = -1;
    bool m_schedulePending = false;

    // Diagnostics, logged in aggregate -- never per chunk.
    qint64 m_statFetches = 0;
    qint64 m_statBytesFromCache = 0;
    qint64 m_statBytesFromUpstream = 0;
};

#endif
