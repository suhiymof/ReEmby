<p align="center">
  <img src="src/qEmbyApp/resources/svg/qemby_logo.svg" width="120" alt="ReEmby Logo"/>
</p>

<h1 align="center">ReEmby</h1>

<p align="center">
  <b>A modern desktop client for Emby & Jellyfin media servers</b><br/>
  <b>Emby & Jellyfin 媒体服务器的现代桌面客户端</b>
</p>

<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT"/></a>
  <a href="https://github.com/suhiymof/ReEmby/releases/latest"><img src="https://img.shields.io/github/v/release/suhiymof/ReEmby?include_prereleases&label=Download" alt="Release"/></a>
  <img src="https://img.shields.io/badge/Qt-6.x-green.svg" alt="Qt 6"/>
  <img src="https://img.shields.io/badge/C%2B%2B-20-orange.svg" alt="C++20"/>
  <img src="https://img.shields.io/badge/Platform-Windows%20|%20Linux%20|%20macOS-lightgrey.svg" alt="Platform: Windows | Linux | macOS"/>
</p>

<p align="center">
  <a href="#中文">中文</a> | <a href="#english">English</a>
</p>

---

> **ReEmby 是 [qEmby](https://github.com/AlanHJ/qEmby) 的 fork**，基于上游 MIT 许可代码持续开发。
> 原始项目版权归 [AlanHJ](https://github.com/AlanHJ) 所有；本 fork 的改动见下方「Fork 改动」。

<a id="中文"></a>

## 📸 应用截图

<p align="center">
  <img src="screenshots/2.png" width="45%" alt="首页"/>
  <img src="screenshots/5.png" width="45%" alt="影片详情"/>
</p>
<p align="center">
  <img src="screenshots/3.png" width="45%" alt="设置"/>
  <img src="screenshots/4.png" width="45%" alt="管理仪表盘"/>
</p>

## 📥 下载

前往 [Releases](https://github.com/suhiymof/ReEmby/releases/latest) 下载最新版本。

| 安装包 | 说明 |
|---|---|
| `ReEmby-<版本>-win-x64-Setup.exe` | Windows 10/11 x64 安装包 |
| `ReEmby-<版本>-win-x64.7z` | Windows 10/11 x64 绿色便携版（7z 解压即用） |

> 绿色版解压后即可运行，数据（配置 / 缓存 / 日志）默认保存在程序目录下的 `config` 文件夹，拷走整个文件夹即可迁移；
> 安装版因无程序目录写权限，会自动改用 `%LOCALAPPDATA%\suh\ReEmby`。

## 🚀 Fork 改动（相比上游 qEmby）

- 🎬 **杜比视界（Dolby Vision）片源自动切换独立播放窗口** —— 内嵌渲染无法正确处理 DV 色彩空间（发绿），检测到纯 DV 片源时自动改走独立窗口播放
- 📝 **副字幕（第二字幕轨）支持** —— 独立的轨道选择 / 位置 / 缩放 / 延迟，可与主字幕、弹幕同时显示
- 🖥️ **独立播放窗口的透明 HUD 覆盖层** —— 播放控制、弹幕、字幕菜单等覆盖层与内嵌模式体验一致，且不遮挡画面
- 📦 **绿色便携数据目录** —— 数据统一存放在程序目录下的 `config` 文件夹（旧版为系统 AppData 目录）
- 🔧 上游之后的大量修复与打磨：字幕轨道选中同步、弹幕渲染与菜单、内存与日志、中文翻译补全等

## ✨ 功能特性

- 🎬 浏览和管理你的 Emby / Jellyfin 媒体库
- ▶️ 内置 **libmpv** 驱动的视频播放器（内嵌 / 独立窗口双形态，DV 片源自动适配）
- 💬 弹幕播放，支持弹弹Play与 LogVar / danmu_api、搜索、匹配、缓存和原生覆盖层渲染
- 📝 主副双字幕、ASS 样式配置、位置拖拽等字幕能力
- 🧩 支持元数据编辑、媒体识别、图片更新和播放列表管理
- 📥 下载管理器
- 🔄 自动检查更新和 Windows 应用内升级
- 🖥️ 可选单例应用模式
- 🌗 深色 / 浅色主题切换
- 🌐 国际化支持（中文 / 英文 / 法语）
- 🔍 支持搜索历史的媒体搜索
- 📺 当前支持电视剧、电影媒体类型
- 📦 提供 Windows 安装包 / 绿色版（7z），Linux / macOS 构建脚本保留
- ⚡ 基于 C++20 协程的异步操作（QCoro）
- 🪟 原生风格的自定义窗口边框（QWindowKit）

## 💻 平台支持

| 平台 | 状态 |
|---|---|
| Windows 10/11 x64 | ✅ 已适配（主要平台） |
| Linux x64 | 🛠️ 构建脚本保留，未验证 |
| macOS (Apple Silicon) | 🛠️ 构建脚本保留，未验证 |

## 📋 开发路线图

- [x] Emby / Jellyfin 媒体库浏览
- [x] 内置视频播放器（libmpv）
- [x] 深色 / 浅色主题
- [x] 国际化支持（中文 / 英文）
- [x] 媒体搜索与搜索历史
- [x] 电视剧、电影支持
- [x] 服务器管理仪表盘
- [x] 支持添加到播放列表和从播放列表中移除
- [x] 支持识别来更新元数据
- [x] 支持修改元数据和图片
- [x] 弹幕系统（搜索、匹配、设置、渲染）
- [x] 下载管理器
- [x] 自动检查更新和 Windows 应用内升级
- [x] 单例应用模式
- [x] 多弹幕源支持（弹弹Play / danmu_api）
- [x] 副字幕（双字幕）支持
- [x] 杜比视界片源自动适配独立窗口
- [ ] AI 字幕生成

> 本项目为个人兴趣开发，欢迎贡献和反馈！

## 🛠️ 技术栈

| 组件 | 技术 |
|---|---|
| 框架 | Qt 6.x (Widgets) |
| 语言 | C++20 |
| 视频播放 | libmpv |
| 异步 | QCoro (Qt C++20 协程) |
| 日志 | spdlog |
| 窗口框架 | QWindowKit |
| 构建系统 | CMake |

## 📦 环境要求

- **Qt 6.x**（包含 Widgets、Core、Network、Concurrent、OpenGLWidgets、WebSockets、WebEngineWidgets、WebChannel、Positioning 模块）
- **CMake** ≥ 3.16
- 支持 **C++20** 的编译器（推荐 MSVC 2022）
- **libmpv** 开发文件（见下方说明）
- **Git**（用于克隆子模块）

## 🚀 构建指南

### 1. 克隆仓库

```bash
git clone --recursive https://github.com/suhiymof/ReEmby.git
cd ReEmby
```

### 2. 获取 libmpv

下载 libmpv 开发包，并放置到 `libs/libmpv/` 目录下，结构如下：

```
libs/libmpv/
├── bin/
│   └── libmpv-2.dll
├── include/
│   └── mpv/
│       ├── client.h
│       └── render.h (等)
└── lib/
    └── libmpv.dll.a
```

libmpv 获取方式：
- [shinchiro/mpv-winbuild-cmake](https://github.com/shinchiro/mpv-winbuild-cmake/releases)（Windows 预编译版本）
- [mpv-player/mpv](https://github.com/mpv-player/mpv)（从源码编译）

### 3. 配置和构建

```bash
cmake -B build -DCMAKE_PREFIX_PATH="/path/to/Qt6/lib/cmake"
cmake --build build --config Release
```

> **提示：** 在 Windows 上使用 MSVC 时，也可以直接在 Qt Creator 或 Visual Studio 中打开 CMake 项目。
> 构建后的 `build/bin/Release` 即完整绿色包（windeployqt 会自动部署 Qt 依赖）。

## 📁 项目结构

```
ReEmby/
├── CMakeLists.txt              # 根 CMake 配置
├── libs/
│   ├── libmpv/                 # libmpv SDK（未纳入版本控制，见构建指南）
│   └── qwindowkit/             # QWindowKit（git 子模块）
└── src/
    ├── qEmbyCore/              # 核心库（API、模型、服务；内部命名沿用 qEmby）
    │   ├── api/                # Emby/Jellyfin API 客户端
    │   ├── config/             # 配置管理
    │   ├── models/             # 数据模型
    │   └── services/           # 业务逻辑服务
    └── qEmbyApp/               # 桌面应用
        ├── components/         # 可复用 UI 组件
        ├── managers/           # 应用管理器
        ├── resources/          # 图标、主题、翻译
        ├── utils/              # 工具类
        └── views/              # 应用视图
```

## 🐛 反馈

> **注意：** 本项目为个人兴趣开发，测试覆盖不全，敬请谅解。如有问题请通过 [GitHub Issues](https://github.com/suhiymof/ReEmby/issues) 反馈。

## 📄 许可证

本项目基于 [MIT 许可证](LICENSE) 开源。原始项目 [qEmby](https://github.com/AlanHJ/qEmby) 版权归 AlanHJ 所有。

## 🙏 致谢

- [qEmby](https://github.com/AlanHJ/qEmby) — 本 fork 的上游项目
- [Qt](https://www.qt.io/) — 应用框架 (LGPL v3)
- [mpv](https://mpv.io/) — 媒体播放引擎 (LGPL v2.1+)
- [QWindowKit](https://github.com/stdware/qwindowkit) — 自定义窗口框架 (Apache-2.0)
- [QCoro](https://github.com/danvratil/qcoro) — Qt C++20 协程库 (MIT)
- [spdlog](https://github.com/gabime/spdlog) — 高性能日志库 (MIT)

---

<a id="english"></a>

## 📸 Screenshots

<p align="center">
  <img src="screenshots/2.png" width="45%" alt="Home"/>
  <img src="screenshots/5.png" width="45%" alt="Detail"/>
</p>
<p align="center">
  <img src="screenshots/3.png" width="45%" alt="Settings"/>
  <img src="screenshots/4.png" width="45%" alt="Admin Dashboard"/>
</p>

## 📥 Download

Grab the latest build from the [Releases](https://github.com/suhiymof/ReEmby/releases/latest) page.

| Package | Description |
|---|---|
| `ReEmby-<version>-win-x64-Setup.exe` | Windows 10/11 x64 installer |
| `ReEmby-<version>-win-x64.7z` | Windows 10/11 x64 portable package (7z) |

> The portable build keeps all data (config / cache / logs) in a `config` folder next to the executable — move the whole folder to migrate.
> The installer falls back to `%LOCALAPPDATA%\suh\ReEmby` since the install directory is not writable.

## 🚀 Fork Changes (vs. upstream qEmby)

- 🎬 **Dolby Vision sources automatically switch to the independent player window** — the embedded renderer cannot handle DV color (green tint), so pure-DV sources are routed to the detached window
- 📝 **Secondary subtitle support** — separate track / position / scale / delay, shown alongside the primary subtitle and danmaku
- 🖥️ **Translucent HUD overlay for the independent window** — playback controls, danmaku and subtitle menus behave the same as embedded, without covering the video
- 📦 **Portable data directory** — data lives in a `config` folder next to the executable (previously under the system AppData directory)
- 🌐 **Genuine ReEmby client identity** — no more masquerading as a third-party player UA; servers list the client as `ReEmby`
- 🔧 Many fixes and polish since upstream: subtitle track selection sync, danmaku rendering and menus, memory/logging, translation completeness

## ✨ Features

- 🎬 Browse and manage your Emby / Jellyfin media library
- ▶️ Built-in video player powered by **libmpv** (embedded / independent window, DV-aware)
- 💬 Danmaku playback with DandanPlay and LogVar / danmu_api, search, matching, cache and native overlay rendering
- 📝 Primary + secondary subtitles, ASS styling and drag-to-position
- 🧩 Metadata editing, media identification, image updates and playlist tools
- 📥 Download manager
- 🔄 Automatic update checks and in-app Windows updates
- 🖥️ Optional single-application mode
- 🌗 Dark and Light theme support
- 🌐 Internationalization support (Chinese / English / French)
- 🔍 Media search with history
- 📺 TV series and movies media types
- 📦 Windows installer / portable packages (7z); Linux & macOS build scripts kept
- ⚡ Asynchronous operations with C++20 coroutines (QCoro)
- 🪟 Custom window frame with native look (QWindowKit)

## 💻 Platform Support

| Platform | Status |
|---|---|
| Windows 10/11 x64 | ✅ Supported (primary platform) |
| Linux x64 | 🛠️ Build scripts kept, unverified |
| macOS (Apple Silicon) | 🛠️ Build scripts kept, unverified |

## 📋 Roadmap

- [x] Emby / Jellyfin media library browsing
- [x] Built-in video player (libmpv)
- [x] Dark / Light theme
- [x] Internationalization (Chinese / English)
- [x] Media search with history
- [x] TV series & movies support
- [x] Server administration dashboard
- [x] Playlist support (add/remove items)
- [x] Media identification & metadata refresh
- [x] Metadata and image editing
- [x] Danmaku (bullet comments) system
- [x] Download manager
- [x] Automatic update checks and in-app Windows updates
- [x] Single-application mode
- [x] Multiple danmaku providers (DandanPlay / danmu_api)
- [x] Secondary (dual) subtitle support
- [x] Automatic independent-window routing for Dolby Vision sources
- [ ] AI-powered subtitle generation

> This is a personal hobby project, developed out of interest. Contributions and feedback are welcome!

## 🛠️ Tech Stack

| Component | Technology |
|---|---|
| Framework | Qt 6.x (Widgets) |
| Language | C++20 |
| Video Player | libmpv |
| Async | QCoro (C++20 Coroutines for Qt) |
| Logging | spdlog |
| Window Kit | QWindowKit |
| Build System | CMake |

## 📦 Prerequisites

- **Qt 6.x** (with Widgets, Core, Network, Concurrent, OpenGLWidgets, WebSockets, WebEngineWidgets, WebChannel, Positioning)
- **CMake** ≥ 3.16
- **C++20** compatible compiler (MSVC 2022 recommended)
- **libmpv** development files (see below)
- **Git** (for cloning submodules)

## 🚀 Build

### 1. Clone the repository

```bash
git clone --recursive https://github.com/suhiymof/ReEmby.git
cd ReEmby
```

### 2. Get libmpv

Download the libmpv development package and place it in `libs/libmpv/` with the following structure:

```
libs/libmpv/
├── bin/
│   └── libmpv-2.dll
├── include/
│   └── mpv/
│       ├── client.h
│       └── render.h (etc.)
└── lib/
    └── libmpv.dll.a
```

You can get libmpv from:
- [shinchiro/mpv-winbuild-cmake](https://github.com/shinchiro/mpv-winbuild-cmake/releases) (Windows builds)
- [mpv-player/mpv](https://github.com/mpv-player/mpv) (build from source)

### 3. Configure and build

```bash
cmake -B build -DCMAKE_PREFIX_PATH="/path/to/Qt6/lib/cmake"
cmake --build build --config Release
```

> **Tip:** On Windows with MSVC, you can also open the project in Qt Creator or Visual Studio with CMake support.
> `build/bin/Release` after the build is a complete portable package (windeployqt deploys the Qt dependencies automatically).

## 📁 Project Structure

```
ReEmby/
├── CMakeLists.txt              # Root CMake configuration
├── libs/
│   ├── libmpv/                 # libmpv SDK (not tracked, see Build section)
│   └── qwindowkit/             # QWindowKit (git submodule)
└── src/
    ├── qEmbyCore/              # Core library (API, models, services; internal naming kept)
    │   ├── api/                # Emby/Jellyfin API client
    │   ├── config/             # Configuration management
    │   ├── models/             # Data models
    │   └── services/           # Business logic services
    └── qEmbyApp/               # Desktop application
        ├── components/         # Reusable UI components
        ├── managers/           # Application managers
        ├── resources/          # Icons, themes, translations
        ├── utils/              # Utility classes
        └── views/              # Application views
```

## 🐛 Feedback

> **Note:** This is a passion project with limited testing. Your understanding is appreciated. Please report any issues via [GitHub Issues](https://github.com/suhiymof/ReEmby/issues).

## 📄 License

This project is licensed under the [MIT License](LICENSE). The original project [qEmby](https://github.com/AlanHJ/qEmby) is copyright AlanHJ.

## 🙏 Acknowledgements

- [qEmby](https://github.com/AlanHJ/qEmby) — the upstream project this fork is based on
- [Qt](https://www.qt.io/) — Application framework (LGPL v3)
- [mpv](https://mpv.io/) — Media player engine (LGPL v2.1+)
- [QWindowKit](https://github.com/stdware/qwindowkit) — Custom window frame (Apache-2.0)
- [QCoro](https://github.com/danvratil/qcoro) — C++20 Coroutines for Qt (MIT)
- [spdlog](https://github.com/gabime/spdlog) — Fast logging library (MIT)
