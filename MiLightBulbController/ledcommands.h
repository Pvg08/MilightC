#ifndef LEDCOMMANDS
#define LEDCOMMANDS

class LEDCommands
{
    public:
         // White LEDs
         const QByteArray AllOn = "350055";

         const QByteArray AllOff = "390055";
         const QByteArray BrightnessUp = "3C0055";
         const QByteArray BrightnessDown = "340055";
         const QByteArray ColorTempDown = "3F0055";
         const QByteArray Group1On = "380055";
         const QByteArray Group1Off = "3B0055";
         const QByteArray Group2On = "3D0055";
         const QByteArray Group2Off = "330055";
         const QByteArray Group3On = "370055";
         const QByteArray Group3Off = "3A0055";
         const QByteArray Group4On = "320055";
         const QByteArray Group4Off = "360055";
         const QByteArray AllFull = "B50055";
         const QByteArray Group1Full = "B80055";
         const QByteArray Group2Full = "BD0055";
         const QByteArray Group3Full = "B70055";
         const QByteArray Group4Full = "B20055";
         const QByteArray AllNight = "B90055";
         const QByteArray Group1Night = "BB0055";
         const QByteArray Group2Night = "B30055";
         const QByteArray Group3Night = "BA0055";
         const QByteArray Group4Night = "B60055";
         const QByteArray ColorTempUp = "3E0055";
        // RGB LEDs
         const QByteArray RGBOn = "220055";
         const QByteArray RGBOff = "210055";
         const QByteArray RGBBrightnessUp = "230055";
         const QByteArray RGBBrightnessDown = "240055";
         const QByteArray RGBSpeedUp = "250055";
         const QByteArray RGBSpeedDown = "260055";
         const QByteArray RGBDiscoNext = "270055";
         const QByteArray RGBDiscoLast = "280055";
         const QByteArray RGBColour = "200055";
        //RGBW LEDs
         const QByteArray RGBWOff = "410055";
         const QByteArray RGBWOn = "420055";
         const QByteArray RGBWDiscoSpeedSlower = "430055";
         const QByteArray RGBWDiscoSpeedFaster = "440055";
         const QByteArray RGBWGroup1AllOn = "450055";
         const QByteArray RGBWGroup1AllOff = "460055";
         const QByteArray RGBWGroup2AllOn = "470055";
         const QByteArray RGBWGroup2AllOff = "480055";
         const QByteArray RGBWGroup3AllOn = "490055";
         const QByteArray RGBWGroup3AllOff = "4A0055";
         const QByteArray RGBWGroup4AllOn = "4B0055";
         const QByteArray RGBWGroup4AllOff = "4C0055";
         const QByteArray RGBWDiscoMode = "4D0055";
         const QByteArray SetColorToWhite = "C20055";
         const QByteArray SetColorToWhiteGroup1 = "C50055";
         const QByteArray SetColorToWhiteGroup2 = "C70055";
         const QByteArray SetColorToWhiteGroup3 = "C90055";
         const QByteArray SetColorToWhiteGroup4 = "CB0055";
         const QByteArray RGBWBrightness = "4E0055";
         const QByteArray RGBWColor = "400055";
};

#endif // LEDCOMMANDS
