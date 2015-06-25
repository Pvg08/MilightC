#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    led_bridge = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

LEDBridge *MainWindow::getLedbridge()
{
    if (!led_bridge) {
        led_bridge = new LEDBridge(ui->lineEdit_host->text(), ui->lineEdit_port->text());
        led_bridge->Start();
        QObject::connect(led_bridge,SIGNAL(command_sended(QByteArray)),this,SLOT(led_command(QByteArray)));
    }
    ui->toolButton_resend->setEnabled(true);
    return led_bridge;
}


void MainWindow::on_pushButton_on_clicked()
{
    if (ui->pushButton_on->isChecked()) {
        getLedbridge()->rgbwAllOn();
    } else {
        getLedbridge()->rgbwAllOff();
    }
}

void MainWindow::on_pushButton_white_clicked()
{
    getLedbridge()->rgbwAllSetToWhite();
    if (!ui->pushButton_on->isChecked()) ui->pushButton_on->setChecked(true);
}

void MainWindow::on_horizontalSlider_brightness_sliderReleased()
{
    getLedbridge()->rgbwBrightnessPercent(ui->horizontalSlider_brightness->value());
}

void MainWindow::on_pushButton_color_clicked()
{
    QColor color = QColorDialog::getColor(getLedbridge()->getLastcolor(), this);
    if(color.isValid()) {
        if (!ui->pushButton_on->isChecked()) ui->pushButton_on->click();
        getLedbridge()->rgbwSetColor(color.name());
    }
}

void MainWindow::on_pushButton_disco_clicked()
{
    getLedbridge()->rgbwDiscoMode();
}

void MainWindow::on_pushButton_faster_clicked()
{
    getLedbridge()->rgbwDiscoFaster();
}

void MainWindow::on_pushButton_slower_clicked()
{
    getLedbridge()->rgbwDiscoSlower();
}

void MainWindow::on_lineEdit_host_editingFinished()
{
    getLedbridge()->setHostName(ui->lineEdit_host->text());
    ui->toolButton_resend->setEnabled(false);
}

void MainWindow::on_lineEdit_port_editingFinished()
{
    getLedbridge()->setServiceName(ui->lineEdit_port->text());
    ui->toolButton_resend->setEnabled(false);
}

void MainWindow::on_toolButton_resend_clicked()
{
    getLedbridge()->RepeatLastCommand();
}

void MainWindow::on_pushButton_fup_clicked()
{
    getLedbridge()->Start();
    getLedbridge()->FadeUp(400);
}

void MainWindow::on_pushButton_fdown_clicked()
{
    getLedbridge()->Start();
    getLedbridge()->FadeDown(400);
}

void MainWindow::on_pushButton_stop_clicked()
{
    getLedbridge()->Stop();
}

void MainWindow::on_pushButton_strobe_clicked()
{
    getLedbridge()->Start();
    getLedbridge()->StrobeMode(1000);
}

void MainWindow::led_command(QByteArray command)
{
    ui->statusBar->showMessage("Send "+command.toHex()+" to "+getLedbridge()->hostName()+":"+getLedbridge()->serviceName(), 5000);
}
