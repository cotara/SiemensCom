#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QStatusBar>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->calibrationLamp->setStyleSheet("background-color: #FF0000");
    ui->errorLamp->setStyleSheet("background-color: #FF0000");
    ui->statusLamp->setStyleSheet("background-color: #FF0000");

    m_timer = new QTimer();
    m_timer->setInterval(100);
    connect(m_timer,&QTimer::timeout,this,&MainWindow::timeOut);
    //Консоль
    m_console = new Console(this);
    m_console->setMaximumHeight(250);
    ui->consoleLayout->addWidget(m_console);

    ModbusReg.resize(8);

    modbusDevice = new QModbusTcpClient(this);
    if (ui->portEdit->text().isEmpty())
        ui->portEdit->setText(QLatin1String("127.0.0.1:502"));

    connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
        statusBar()->showMessage(modbusDevice->errorString(), 5000);
    });

    if (!modbusDevice) {
        ui->connectButton->setDisabled(true);
        statusBar()->showMessage(tr("Could not create Modbus client."), 5000);
    }
    else
        connect(modbusDevice, &QModbusClient::stateChanged,this, &MainWindow::onModbusStateChanged);
}

MainWindow::~MainWindow()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;
    delete ui;
}


void MainWindow::onModbusStateChanged(int state)
{
    if (state == QModbusDevice::UnconnectedState)
        ui->connectButton->setText(tr("Connect"));
    else if (state == QModbusDevice::ConnectedState)
        ui->connectButton->setText(tr("Disconnect"));
}

void MainWindow::timeOut(){
    modbus_3(6,2);
}

void MainWindow::statusParse(){
    if( ModbusReg.at(7) & (1 << 0))
        ui->statusLamp->setStyleSheet("background-color: #00FF00");
    else
        ui->statusLamp->setStyleSheet("background-color: #FF0000");

    if( ModbusReg.at(7) & (1 << 1))
        ui->errorLamp->setStyleSheet("background-color: #00FF00");
    else
        ui->errorLamp->setStyleSheet("background-color: #FF0000");

    if( ModbusReg.at(7) & (1 << 1))
        ui->calibrationLamp->setStyleSheet("background-color: #00FF00");
    else
        ui->calibrationLamp->setStyleSheet("background-color: #FF0000");
}

void MainWindow::on_connectButton_clicked()
{
    if (!modbusDevice)
        return;

    statusBar()->clearMessage();
    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        const QUrl url = QUrl::fromUserInput(ui->portEdit->text());
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

        modbusDevice->setTimeout(1000);
        modbusDevice->setNumberOfRetries(3);
        if (!modbusDevice->connectDevice())
            statusBar()->showMessage(tr("Connect failed: ") + modbusDevice->errorString(), 5000);
        m_timer->start();
    }
    else{
        modbusDevice->disconnectDevice();
        m_timer->stop();
    }
}

//Чтение
void MainWindow::onReadReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        if(unit.startAddress()+unit.valueCount() <= 8){
            for (int i = 0, total = int(unit.valueCount()); i < total; ++i)
                ModbusReg[unit.startAddress()+i] = unit.value(i);
            ui->positionNowLabel->setText(QString::number(ModbusReg.at(6)));
            statusParse();
        }
        else{
            statusBar()->showMessage(tr("Read response error: %1 (Mobus exception: 0x%2)").
                                        arg(reply->errorString()).
                                        arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
        }
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        statusBar()->showMessage(tr("Read response error: %1 (Mobus exception: 0x%2)").
                                    arg(reply->errorString()).
                                    arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
    } else {
        statusBar()->showMessage(tr("Read response error: %1 (code: 0x%2)").
                                    arg(reply->errorString()).
                                    arg(reply->error(), -1, 16), 5000);
    }

    reply->deleteLater();
}

void MainWindow::modbus_3(int startAdd, int count)
{
    if (!modbusDevice){
        statusBar()->showMessage(tr("Connect failed: ") + modbusDevice->errorString(), 5000);
        return;
    }

    const auto table = static_cast<QModbusDataUnit::RegisterType>(QModbusDataUnit::HoldingRegisters);

    QModbusDataUnit m_unit = QModbusDataUnit(table, startAdd, count);

    if (auto *reply = modbusDevice->sendReadRequest(m_unit, ui->serverEdit->value())) {
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, &MainWindow::onReadReady);
            m_console->putData(QString("REQ TO " +  QString::number(ui->serverEdit->value()) + " DEV: ").toUtf8());
        }
        else
            delete reply; // broadcast replies return immediately
    }
    else
        statusBar()->showMessage(tr("Connect failed: ") + modbusDevice->errorString(), 5000);
}

//Запись
void MainWindow::modbus_6(int startAdd, int value)
{
    if (!modbusDevice)
        return;
    statusBar()->clearMessage();

    const auto table = static_cast<QModbusDataUnit::RegisterType>(QModbusDataUnit::HoldingRegisters);

    QModbusDataUnit writeUnit = QModbusDataUnit(table, startAdd, 1);
    writeUnit.setValue(0, value);

    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, ui->serverEdit->value())) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::ProtocolError)
                    statusBar()->showMessage(tr("Write response error: %1 (Mobus exception: 0x%2)").arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),5000);
                else if (reply->error() != QModbusDevice::NoError)
                    statusBar()->showMessage(tr("Write response error: %1 (code: 0x%2)").arg(reply->errorString()).arg(reply->error(), -1, 16), 5000);
                reply->deleteLater();
            });
        }
        else
            reply->deleteLater();
    }
    else
        statusBar()->showMessage(tr("Write error: ") + modbusDevice->errorString(), 5000);
}

void MainWindow::on_jogPlusButton_pressed(){
   modbus_6(2,1);
}

void MainWindow::on_jogPlusButton_released(){
    modbus_6(2,0);
}

void MainWindow::on_jogMinusButton_pressed(){
    modbus_6(3,1);
}

void MainWindow::on_jogMinusButton_released(){
    modbus_6(3,0);
}

void MainWindow::on_goButton_clicked(){
    modbus_6(4,ui->positionBox->value());
    modbus_6(5,1);
}

void MainWindow::on_stopButton_clicked(){
    modbus_6(5,0);
}

void MainWindow::on_backButton_clicked(){
    modbus_6(4,0);
    modbus_6(5,1);
}

void MainWindow::on_calibrationButton_clicked(){
    modbus_6(1,1);
}

void MainWindow::on_onButton_clicked(){
    modbus_6(0,1);
}

void MainWindow::on_offButton_clicked(){
    modbus_6(0,0);
}

void MainWindow::on_resetButton_clicked(){
    modbus_6(8,0);
}
