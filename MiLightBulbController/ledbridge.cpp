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
    rgbwSendOnToActiveGroup();
    if (brightnessPercent < 14) {
        brightness = 0x02;
    }
    if (brightnessPercent >= 14 && brightnessPercent < 17) {
        brightness = 0x03;
    }
    if (brightnessPercent >= 17 && brightnessPercent < 21) {
        brightness = 0x04;
    }
    if (brightnessPercent >= 21 && brightnessPercent < 24) {
        brightness = 0x05;
    }
    if (brightnessPercent >= 24 && brightnessPercent < 28) {
        brightness = 0x06;
    }
    if (brightnessPercent >= 28 && brightnessPercent < 32) {
        brightness = 0x07;
    }
    if (brightnessPercent >= 32 && brightnessPercent < 35) {
        brightness = 0x08;
    }
    if (brightnessPercent >= 35 && brightnessPercent < 39) {
        brightness = 0x09;
    }
    if (brightnessPercent >= 39 && brightnessPercent < 42) {
        brightness = 0xa0;
    }
    if (brightnessPercent >= 42 && brightnessPercent < 46) {
        brightness = 0xb0;
    }
    if (brightnessPercent >= 46 && brightnessPercent < 50) {
        brightness = 0xc0;
    }
    if (brightnessPercent >= 50 && brightnessPercent < 53) {
        brightness = 0xd0;
    }
    if (brightnessPercent >= 53 && brightnessPercent < 57) {
        brightness = 0xe0;
    }
    if (brightnessPercent >= 57 && brightnessPercent < 60) {
        brightness = 0xf0;
    }
    if (brightnessPercent >= 60 && brightnessPercent < 64) {
        brightness = 0x10;
    }
    if (brightnessPercent >= 64 && brightnessPercent < 68) {
        brightness = 0x11;
    }
    if (brightnessPercent >= 68 && brightnessPercent < 71) {
        brightness = 0x12;
    }
    if (brightnessPercent >= 71 && brightnessPercent < 75) {
        brightness = 0x13;
    }
    if (brightnessPercent >= 75 && brightnessPercent < 78) {
        brightness = 0x14;
    }
    if (brightnessPercent >= 78 && brightnessPercent < 82) {
        brightness = 0x15;
    }
    if (brightnessPercent >= 82 && brightnessPercent < 86) {
        brightness = 0x16;
    }
    if (brightnessPercent >= 86 && brightnessPercent < 89) {
        brightness = 0x17;
    }
    if (brightnessPercent >= 89 && brightnessPercent < 93) {
        brightness = 0x18;
    }
    if (brightnessPercent >= 93 && brightnessPercent < 96) {
        brightness = 0x19;
    }
    if (brightnessPercent >= 96 && brightnessPercent < 100) {
        brightness = 0x1a;
    }
    if (brightnessPercent >= 96 && brightnessPercent <= 100) {
        brightness = 0x1b;
    }
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
    _client = 0;
    lastcolor = QColor("#ffffff");
    lastCommand.clear();
}

LEDBridge::LEDBridge(QString hostName, QString serviceName)
{
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
