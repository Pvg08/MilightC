#include "ledclient.h"

using namespace MiLED;

const QString LEDClient::DefaultOutHost = "192.168.1.255";
const QString LEDClient::DefaultOutService = "8899";

LEDClient::LEDClient(QString outHost = DefaultOutHost, QString outService = DefaultOutService)
{
    _outHost = QHostAddress(outHost);
    _outService = outService.toLong();
    _inHost = QHostAddress::LocalHost;
    _inService = _outService;
}

LEDClient::LEDClient(QString outHost, QString outService, QString inHost, QString inService)
{
    _outHost = QHostAddress(outHost);
    _outService = outService.toLong();
    _inHost = QHostAddress(inHost);
    _inService = inService.toLong();
}

void LEDClient::SendData(QByteArray data)
{
    /*QTextStream console(stdout);
    console << data.size() << " ";
    console << data.toHex() << " - ";
    console <<  QHostAddress(_outHost).toString() << " " << _outService.toLong() << endl;*/

    QByteArray msg;
    msg.append(data);

    QUdpSocket *_client;
    _client = new QUdpSocket(QApplication::instance());
    _client->writeDatagram(msg, _outHost, _outService);
    _client->close();
    delete _client;
}

void LEDClient::Delay(long int duration)
{
    if (duration > 0)
    {
        QTime dieTime = QTime::currentTime().addMSecs( duration );
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }
}

