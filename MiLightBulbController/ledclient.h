#ifndef LEDCLIENT_H
#define LEDCLIENT_H

#include <QString>
#include <QStringList>
#include <QApplication>
#include <QTime>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QUdpSocket>

class LEDClient
{
    private:
        QHostAddress _inHost;
        QHostAddress _outHost;
        quint16 _inService;
        quint16 _outService;
    public:
        static const QString DefaultOutHost;
        static const QString DefaultOutService;

        LEDClient(QString outHost, QString outService);
        LEDClient(QString outHost, QString outService, QString inHost, QString inService);
        void SendData(QByteArray data);
        void Delay(long int duration);
};

#endif // LEDCLIENT_H
