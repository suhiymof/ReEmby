#ifndef SERVERPROFILE_H
#define SERVERPROFILE_H

#include "proxyconfig.h"
#include <QString>
#include <QUuid>
#include <config/config_keys.h>
#include <config/configstore.h>
#include <utils/securesecretbox.h>

struct ServerProfile {
    enum ServerType { Emby, Jellyfin };

    QString id = QUuid::createUuid().toString();
    QString name;
    QString url;
    ServerType type = Emby;
    bool ignoreSslVerification = false;

    QString userId;
    QString userName;
    QString accessToken;
    QString deviceId;
    bool isAdmin = false;
    bool canDownloadMedia = false;

    // Login password encrypted with SecureSecretBox::encryptLocalSecret
    // (AES+HMAC, local machine key), base64-encoded. Kept so the settings
    // account page can satisfy the server's CurrentPw check on self-service
    // password changes. Empty = not stored (profiles created before this
    // feature, or storage failed).
    QString storedPassword;

    void setStoredPassword(const QString &plainPassword) {
        storedPassword.clear();
        if (plainPassword.isEmpty())
            return;
        QByteArray pwBytes = plainPassword.toUtf8();
        const QByteArray cipher = SecureSecretBox::encryptLocalSecret(pwBytes);
        SecureSecretBox::secureZero(pwBytes);
        if (!cipher.isEmpty())
            storedPassword = QString::fromLatin1(cipher.toBase64());
    }

    // Returns the plaintext password, or empty if none was stored / the
    // cipher cannot be decrypted (e.g. local key regenerated).
    QString storedPasswordPlain() const {
        if (storedPassword.isEmpty())
            return QString();
        const QByteArray cipher = QByteArray::fromBase64(storedPassword.toLatin1());
        if (cipher.isEmpty())
            return QString();
        const auto plain = SecureSecretBox::decryptLocalSecret(cipher);
        if (!plain.has_value())
            return QString();
        return QString::fromUtf8(plain.value());
    }

    QString iconBase64;




    bool useGlobalProxy = false;
    ProxyConfig proxy;

    // Optional per-server User-Agent override. Some Emby servers run strict
    // UA whitelists and hang connections from unrecognized clients; setting
    // this makes qEmby present the given UA (and a matching X-Emby-Authorization
    // identity) for API and streaming requests to this server.
    QString customUserAgent;

    bool isValid() const { return !accessToken.isEmpty(); }

    // Built-in default client identity: a widely used third-party player.
    // Qt's implicit default varies by network backend and libmpv announces
    // itself as "libmpv", which some servers treat as unknown clients.
    static QString defaultUserAgent() {
        return QStringLiteral(
            "RodelPlayer/2.2607.7.0 (Windows NT 10.0.26100; x64)");
    }

    // Resolution order: per-server customUserAgent -> global
    // ConfigKeys::CustomUserAgent -> built-in default.
    QString effectiveUserAgent() const {
        const QString perServer = customUserAgent.trimmed();
        if (!perServer.isEmpty()) {
            return perServer;
        }
        const QString global = ConfigStore::instance()
                ->get<QString>(ConfigKeys::CustomUserAgent, QString());
        const QString trimmed = global.trimmed();
        if (!trimmed.isEmpty()) {
            return trimmed;
        }
        return defaultUserAgent();
    }
};
#endif
