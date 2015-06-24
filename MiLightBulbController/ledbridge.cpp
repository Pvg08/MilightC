#include "ledbridge.h"

using namespace MiLED;

QString LEDBridge::hostName() const
{
    return _hostName;
}

void LEDBridge::setHostName(const QString &hostName)
{
    _hostName = hostName;
}

QString LEDBridge::serviceName() const
{
    return _serviceName;
}

void LEDBridge::setServiceName(const QString &serviceName)
{
    _serviceName = serviceName;
}

void LEDBridge::SendCommand(QByteArray buffer)
{
    if (_client == 0)
    {
        _client = new LEDClient(_hostName, _serviceName);
    }
    _client->SendData(buffer);
}

void LEDBridge::StrobeMode(CancellationToken *ct)
{
    QByteArray byteOff = QByteArray::fromHex(Commands.RGBWOff);
    QByteArray byteOn = QByteArray::fromHex(Commands.RGBWOn);

    while ((ct == 0) || ((ct != 0) && (ct->CanBeCanceled) && (ct->IsCancellationRequested)))
    {
        SendCommand(byteOff);
        Delay(3000);
        SendCommand(byteOn);
        Delay(3000);
    }
}

void LEDBridge::Delay(int millisecondsTimeout = 101)
{
    if (millisecondsTimeout > 0)
    {
        QTime dieTime = QTime::currentTime().addMSecs( millisecondsTimeout );
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }
}

LEDBridge::LEDBridge()
{
    _client = 0;
}

LEDBridge::LEDBridge(QString hostName, QString serviceName)
{
    _client = 0;
    _hostName = hostName;
    _serviceName = serviceName;
}

