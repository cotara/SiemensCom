#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusDataUnit>
#include "console.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// commands
const char ON_OFF           = 0x00;
const char CALIB_ON         = 0x01;
const char JOG_RIGHT        = 0x02;
const char JOG_LEFT         = 0x03;
const char SETPOS_HIGH      = 0x04;
const char SETPOS_LOW       = 0x05;
const char SPEED            = 0x06;
const char RESET            = 0x07;
const char CURPOS_HIGH      = 0x00;
const char CURPOS_LOW       = 0x09;
const char SATUS            = 0x0A;
const char ERROR            = 0x0B;
const char CALIBED          = 0x0C;
const char HATL             = 0x0D;
const char MOVETO_ABS       = 0x0E;
const char MOVETO_REL       = 0x0F;

//смещение на 20 с каждым мотором
const char MOTOR_SHIFT       = 0x14;

class QModbusClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QModbusClient *modbusDevice = nullptr;
    Console *m_console;
    QVector <unsigned short> ModbusReg;
    QTimer *m_timer;
    int shifMulter=0;
private slots:
    void onModbusStateChanged(int state);
    void on_connectButton_clicked();
    void timeOut();
    void statusParse();
    void processModbus3();
    void modbus_3(int startAdd, int count);
    void modbus_6(int startAdd, int value);
    void onReadReady();
    void on_jogPlusButton_pressed();
    void on_jogPlusButton_released();

    void on_jogMinusButton_pressed();
    void on_jogMinusButton_released();
    void on_goButton_clicked();
    void on_stopButton_clicked();
    void on_backButton_clicked();
    void on_calibrationButton_clicked();
    void on_resetButton_clicked();
    void on_onButton_toggled(bool checked);
    void on_speedSilder_valueChanged(int value);
    void on_speedSilder_sliderReleased();
    void on_positionBox_valueChanged(int arg1);
    void on_goRelButton_clicked();
    void on_motorBox_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
