#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusDataUnit>
#include "console.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
private slots:
    void onModbusStateChanged(int state);
    void on_connectButton_clicked();
    void timeOut();
    void statusParse();
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
    void on_onButton_clicked();
    void on_offButton_clicked();
    void on_resetButton_clicked();
};

#endif // MAINWINDOW_H
