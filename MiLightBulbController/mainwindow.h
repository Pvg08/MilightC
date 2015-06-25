#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "./ledbridge.h"

namespace Ui {
class MainWindow;
}

using namespace MiLED;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    LEDBridge *getLedbridge();

private slots:
    void on_pushButton_on_clicked();

    void on_pushButton_white_clicked();

    void on_horizontalSlider_brightness_sliderReleased();

    void on_pushButton_color_clicked();

    void on_pushButton_disco_clicked();

    void on_pushButton_faster_clicked();

    void on_pushButton_slower_clicked();

    void on_lineEdit_host_editingFinished();

    void on_lineEdit_port_editingFinished();

    void on_toolButton_resend_clicked();

private:
    Ui::MainWindow *ui;
    LEDBridge *led_bridge;
};

#endif // MAINWINDOW_H
