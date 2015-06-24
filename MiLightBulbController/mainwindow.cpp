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
    }
    return led_bridge;
}


void MainWindow::on_pushButton_on_clicked()
{
    getLedbridge()->rgbwAllOn();
}

void MainWindow::on_pushButton_off_clicked()
{
    getLedbridge()->rgbwAllOff();
}

void MainWindow::on_pushButton_white_clicked()
{
    getLedbridge()->rgbwAllSetToWhite();
}

void MainWindow::on_horizontalSlider_brightness_sliderReleased()
{
    getLedbridge()->rgbwBrightnessPercent(ui->horizontalSlider_brightness->value());
}

void MainWindow::on_pushButton_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this);
    if(color.isValid()) {
        getLedbridge()->rgbwSetColor(color.name());
    }
}
