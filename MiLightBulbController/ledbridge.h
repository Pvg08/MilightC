#ifndef LEDBRIDGE_H
#define LEDBRIDGE_H

#include <QString>
#include <QRegExp>
#include "./ledgroups.h"
#include "./ledcolor.h"
#include "./ledcommands.h"
#include "./ledclient.h"

namespace MiLED
{
    class CancellationToken
    {
        public:
            bool CanBeCanceled = true;
            bool IsCancellationRequested = false;
    };

    class LEDBridge
    {
        private:
            QString _hostName = "";
            QString _serviceName = "";
            LEDClient *_client = 0;
            void Delay(int millisecondsTimeout);
        public:
            LEDCommands Commands;
            LEDColor Colors;
            LEDGroups Groups;

            LEDBridge();
            LEDBridge(QString hostName, QString serviceName);
            QString hostName() const;
            void setHostName(const QString &hostName);
            QString serviceName() const;
            void setServiceName(const QString &serviceName);

            void SendCommand(QByteArray buffer);
            void StrobeMode(CancellationToken *ct = 0);
    };
}

#endif // LEDBRIDGE_H
