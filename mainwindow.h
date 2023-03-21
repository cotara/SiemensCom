#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusDataUnit>
#include <console.h>

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
private slots:
    void onModbusStateChanged(int state);
    void on_connectButton_clicked();
    QModbusDataUnit readRequest(int startAdd, int num) const;
    void on_jogPlusButton_pressed();
    void onReadReady();
};

#endif // MAINWINDOW_H
