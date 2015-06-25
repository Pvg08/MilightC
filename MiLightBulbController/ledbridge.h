#ifndef LEDBRIDGE_H
#define LEDBRIDGE_H

#include <QString>
#include <QColor>
#include "./ledcolor.h"
#include "./ledcommands.h"
#include "./ledclient.h"

class CancellationToken
{
    private:
        bool CanBeCanceled = true;
        bool IsCancellationRequested = false;
    public:
        bool getCanBeCanceled() const;
        void setCanBeCanceled(bool value);
        bool getIsCancellationRequested() const;
        void setIsCancellationRequested(bool value);
};

class LEDBridge : public QObject
{
    Q_OBJECT
    private:
        CancellationToken *ct;
        QString _hostName = "";

        bool fadeMode = false;
        QColor lastcolor;
        QByteArray lastCommand;
        QString _serviceName = "";
        LEDClient *_client = 0;
        quint8 rgbwActiveGroup = 0;
        void Delay(int millisecondsTimeout);

        quint8 hexToMilightColor(QString hexColor);
    public:
        LEDCommands Commands;
        LEDColor Colors;

        LEDBridge();
        LEDBridge(QString hostName, QString serviceName);
        QString hostName() const;
        void setHostName(const QString &hostName);
        QString serviceName() const;
        void setServiceName(const QString &serviceName);

        void SendCommand(QByteArray buffer);
        void RepeatLastCommand();

        void rgbwAllOn();
        void rgbwAllOff();
        void whiteAllOn();
        void whiteAllOff();
        void rgbwSendOnToActiveGroup();
        void rgbwSendOffToActiveGroup();
        void whiteSendOnToActiveGroup();
        void rgbwBrightnessPercent(quint8 brightnessPercent);
        void rgbwSetColor(quint8 colorID);
        void rgbwSetColor(QString hexColor);

        void rgbwAllSetToWhite();
        void StrobeMode(quint16 interval);
        void FadeDown(quint16 delay);
        void FadeUp(quint16 delay);
        void rgbwDiscoMode();
        void rgbwDiscoSlower();
        void rgbwDiscoFaster();

        void Start();
        void Stop();

        QColor getLastcolor() const;
        quint8 getRgbwActiveGroup() const;
        void setRgbwActiveGroup(const quint8 &value);
    signals:
        void command_sended(QByteArray command);
};


#endif // LEDBRIDGE_H
