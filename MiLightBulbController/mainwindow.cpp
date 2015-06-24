#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./ledbridge.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MiLED::LEDBridge *br = new MiLED::LEDBridge(ui->lineEdit->text(), "8899");
    br->StrobeMode();
}
