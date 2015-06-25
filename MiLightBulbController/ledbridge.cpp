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
    lastCommand = buffer;
    _client->SendData(buffer);
}

void LEDBridge::RepeatLastCommand()
{
    if (_client) _client->SendData(lastCommand);
}

void LEDBridge::rgbwAllOn()
{
    SendCommand(QByteArray::fromHex(Commands.RGBWOn));
}

void LEDBridge::rgbwAllOff()
{
    SendCommand(QByteArray::fromHex(Commands.RGBWOff));
}

void LEDBridge::whiteAllOn()
{
    SendCommand(QByteArray::fromHex(Commands.AllOn));
}

void LEDBridge::whiteAllOff()
{
    SendCommand(QByteArray::fromHex(Commands.AllOff));
}

void LEDBridge::rgbwSendOnToActiveGroup()
{
    if (rgbwActiveGroup > 0) {
        switch(rgbwActiveGroup) {
            case 1: SendCommand(QByteArray::fromHex(Commands.RGBWGroup1AllOn)); break;
            case 2: SendCommand(QByteArray::fromHex(Commands.RGBWGroup2AllOn)); break;
            case 3: SendCommand(QByteArray::fromHex(Commands.RGBWGroup3AllOn)); break;
            case 4: SendCommand(QByteArray::fromHex(Commands.RGBWGroup4AllOn)); break;
        }
        return;
    }
    rgbwAllOn();
    return;
}

void LEDBridge::rgbwSendOffToActiveGroup()
{
    if (rgbwActiveGroup > 0) {
        switch(rgbwActiveGroup) {
            case 1: SendCommand(QByteArray::fromHex(Commands.RGBWGroup1AllOff)); break;
            case 2: SendCommand(QByteArray::fromHex(Commands.RGBWGroup2AllOff)); break;
            case 3: SendCommand(QByteArray::fromHex(Commands.RGBWGroup3AllOff)); break;
            case 4: SendCommand(QByteArray::fromHex(Commands.RGBWGroup4AllOff)); break;
        }
        return;
    }
    rgbwAllOff();
    return;
}

void LEDBridge::whiteSendOnToActiveGroup()
{
    if (rgbwActiveGroup > 0) {
        switch(rgbwActiveGroup) {
            case 1: SendCommand(QByteArray::fromHex(Commands.SetColorToWhiteGroup1)); break;
            case 2: SendCommand(QByteArray::fromHex(Commands.SetColorToWhiteGroup2)); break;
            case 3: SendCommand(QByteArray::fromHex(Commands.SetColorToWhiteGroup3)); break;
            case 4: SendCommand(QByteArray::fromHex(Commands.SetColorToWhiteGroup4)); break;
        }
        return;
    }
    rgbwAllOn();
    return;
}

void LEDBridge::rgbwBrightnessPercent(quint8 brightnessPercent)
{
    quint8 brightness = 0x02;
    if (!fadeMode) rgbwSendOnToActiveGroup();
    if (brightnessPercent>100) brightnessPercent = 100;
    brightness = 0x02 + qRound(brightnessPercent * (0x1b - 0x02) / 100.0);
    QByteArray command = QByteArray::fromHex(Commands.RGBWBrightness);
    command[1] = brightness;
    SendCommand(command);
}

void LEDBridge::rgbwSetColor(quint8 colorID)
{
    QByteArray command = QByteArray::fromHex(Commands.RGBWColor);
    command[1] = colorID;
    SendCommand(command);
}

void LEDBridge::rgbwSetColor(QString hexColor)
{
    rgbwSetColor(hexToMilightColor(hexColor));
}

void LEDBridge::rgbwAllSetToWhite()
{
    SendCommand(QByteArray::fromHex(Commands.SetColorToWhite));
}

void LEDBridge::StrobeMode(quint16 interval = 1000)
{
    QByteArray byteOff = QByteArray::fromHex(Commands.RGBWOff);
    QByteArray byteOn = QByteArray::fromHex(Commands.RGBWOn);

    while ((ct == 0) || ((ct != 0) && (ct->CanBeCanceled) && (ct->IsCancellationRequested)))
    {
        SendCommand(byteOff);
        Delay(interval);
        SendCommand(byteOn);
        Delay(interval);
    }
}

void LEDBridge::FadeDown(quint16 delay = 100)
{
    for (int i = 100; i >= 4; i-=4)
    {
        if ((ct) && (ct->CanBeCanceled) && (ct->IsCancellationRequested)) break;
        rgbwBrightnessPercent(i);
        Delay(delay);
        fadeMode = true;
    }
    rgbwBrightnessPercent(0);
    fadeMode = false;
}

void LEDBridge::FadeUp(quint16 delay = 100)
{
    rgbwBrightnessPercent(0);
    for (int i = 2; i < 100; i+=4)
    {
        if ((ct) && (ct->CanBeCanceled) && (ct->IsCancellationRequested)) break;
        Delay(delay);
        fadeMode = true;
        rgbwBrightnessPercent(i);
    }
    fadeMode = false;
}

void LEDBridge::rgbwDiscoMode()
{
    rgbwSendOnToActiveGroup();
    SendCommand(QByteArray::fromHex(Commands.RGBWDiscoMode));
}

void LEDBridge::rgbwDiscoSlower()
{
    rgbwSendOnToActiveGroup();
    SendCommand(QByteArray::fromHex(Commands.RGBWDiscoSpeedSlower));
}

void LEDBridge::rgbwDiscoFaster()
{
    rgbwSendOnToActiveGroup();
    SendCommand(QByteArray::fromHex(Commands.RGBWDiscoSpeedFaster));
}

void LEDBridge::Stop()
{
    if (ct == 0) {
        ct = new CancellationToken();
    }
    ct->setIsCancellationRequested(true);
}


QColor LEDBridge::getLastcolor() const
{
    return lastcolor;
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

quint8 LEDBridge::hexToMilightColor(QString hexColor)
{
    QColor col = QColor(hexColor);
    lastcolor = col;
    col = col.toHsl();
    quint8 color = (256 + 176 - (int)(col.hslHue() / 360.0 * 255.0)) % 256;
    return (color + 0xfa) % 256;
}

LEDBridge::LEDBridge()
{
    ct = 0;
    _client = 0;
    lastcolor = QColor("#ffffff");
    lastCommand.clear();
}

LEDBridge::LEDBridge(QString hostName, QString serviceName)
{
    ct = 0;
    _client = 0;
    _hostName = hostName;
    _serviceName = serviceName;
    lastcolor = QColor("#ffffff");
    lastCommand.clear();
}


bool CancellationToken::getIsCancellationRequested() const
{
    return IsCancellationRequested;
}

void CancellationToken::setIsCancellationRequested(bool value)
{
    IsCancellationRequested = value;
}
bool CancellationToken::getCanBeCanceled() const
{
    return CanBeCanceled;
}

void CancellationToken::setCanBeCanceled(bool value)
{
    CanBeCanceled = value;
}
