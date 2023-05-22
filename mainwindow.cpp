#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QStatusBar>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->calibrationLamp->setStyleSheet("background-color: #717171");
    ui->errorLamp->setStyleSheet("background-color: #717171");
    ui->statusLamp->setStyleSheet("background-color: #717171");
    ui->statusPower->setStyleSheet("background-color: #717171");
    ui->statusEmition->setStyleSheet("background-color: #717171");
    ui->statusEmitblock->setStyleSheet("background-color: #717171");
    ui->statusButton->setStyleSheet("background-color: #717171");


    m_timer = new QTimer();
    m_timer->setInterval(1000);
    connect(m_timer,&QTimer::timeout,this,&MainWindow::timeOut);
    //Консоль
    m_console = new Console(this);
    m_console->setMaximumHeight(250);
    ui->consoleLayout->addWidget(m_console);

    ModbusReg.resize(80);

    modbusDevice = new QModbusTcpClient(this);
    if (ui->portEdit->text().isEmpty())
        ui->portEdit->setText(QLatin1String("172.31.1.1:502"));

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
    modbus_3(CURPOS_HIGH + shifMulter*MOTOR_SHIFT,12);
}

void MainWindow::statusParse(int add){


    if( ModbusReg.at(add+2))
        ui->statusLamp->setStyleSheet("background-color: #00FF00");
    else
        ui->statusLamp->setStyleSheet("background-color: #717171");

    if( ModbusReg.at(add+3) )
        ui->errorLamp->setStyleSheet("background-color: #FF0000");
    else
        ui->errorLamp->setStyleSheet("background-color: #717171");

    if( ModbusReg.at(add+4))
        ui->calibrationLamp->setStyleSheet("background-color: #00FF00");
    else
        ui->calibrationLamp->setStyleSheet("background-color: #FF0000");


    if( ModbusReg.at(add+8))
        ui->statusEmition->setStyleSheet("background-color: #FF0000");
    else
        ui->statusEmition->setStyleSheet("background-color: #717171");
    if( ModbusReg.at(add+9))
        ui->statusPower->setStyleSheet("background-color: #00FF00");
    else
        ui->statusPower->setStyleSheet("background-color: #717171");
    if( ModbusReg.at(add+10))
        ui->statusButton->setStyleSheet("background-color: #FF0000");
    else
        ui->statusButton->setStyleSheet("background-color: #717171");
    if( ModbusReg.at(add+11))
        ui->statusEmitblock->setStyleSheet("background-color: #FF0000");
    else
        ui->statusEmitblock->setStyleSheet("background-color: #717171");




}

void MainWindow::processModbus3(){
    int add = CURPOS_HIGH + shifMulter*MOTOR_SHIFT;
    c2f.sh[0] = ModbusReg.at(add+1);
    c2f.sh[1] = ModbusReg.at(add);

    ui->positionNowLabel->setText(QString::number(c2f.f));
    statusParse(add);
}

void MainWindow::on_connectButton_clicked()
{
    if (!modbusDevice)
        return;

    ui->calibrationLamp->setStyleSheet("background-color: #717171");
    ui->errorLamp->setStyleSheet("background-color: #717171");
    ui->statusLamp->setStyleSheet("background-color: #717171");
    ui->statusPower->setStyleSheet("background-color: #717171");
    ui->statusEmition->setStyleSheet("background-color: #717171");
    ui->statusEmitblock->setStyleSheet("background-color: #717171");
    ui->statusButton->setStyleSheet("background-color: #717171");

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
        if(unit.startAddress()+unit.valueCount() <= 80){
            for (int i = 0, total = int(unit.valueCount()); i < total; ++i)
                ModbusReg[unit.startAddress()+i] = unit.value(i);
            processModbus3();
            m_console->putData(QString("  ----->  FROM " +  QString::number(ui->serverEdit->value()) + " DEV:").toUtf8());
            for (int i = 0, total = int(unit.valueCount()); i < total; ++i)
                 m_console->putData(QString::number(unit.value(i)).toUtf8());
            m_console->putData("\n");
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
            m_console->putData(QString("REQ TO " +  QString::number(ui->serverEdit->value()) + " DEV:").toUtf8());
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

void MainWindow::on_onButton_toggled(bool checked){
    modbus_6(ON_OFF + shifMulter*MOTOR_SHIFT,checked);
}
void MainWindow::on_calibrationButton_clicked(){
    modbus_6(CALIB_ON + shifMulter*MOTOR_SHIFT,1);
}
void MainWindow::on_jogPlusButton_pressed(){
   modbus_6(JOG_RIGHT + shifMulter*MOTOR_SHIFT,1);
}
void MainWindow::on_jogPlusButton_released(){
    modbus_6(JOG_RIGHT + shifMulter*MOTOR_SHIFT,0);
}
void MainWindow::on_jogMinusButton_pressed(){
    modbus_6(JOG_LEFT + shifMulter*MOTOR_SHIFT,1);
}
void MainWindow::on_jogMinusButton_released(){
    modbus_6(JOG_LEFT + shifMulter*MOTOR_SHIFT,0);
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1){
    float pos = arg1;
    c2f.f = pos;
    modbus_6(SETPOS_HIGH + shifMulter*MOTOR_SHIFT,c2f.sh[1]);
    _sleep(100);
    modbus_6(SETPOS_LOW + shifMulter*MOTOR_SHIFT,c2f.sh[0]);
}

void MainWindow::on_speedBox_valueChanged(double arg1){
    modbus_6(SPEED + shifMulter*MOTOR_SHIFT,static_cast<short>(arg1));
}
void MainWindow::on_resetButton_clicked(){
    modbus_6(RESET + shifMulter*MOTOR_SHIFT,1);
}
void MainWindow::on_goButton_clicked(){
    modbus_6(MOVETO_ABS + shifMulter*MOTOR_SHIFT,1);
}
void MainWindow::on_goRelButton_clicked(){
     modbus_6(MOVETO_REL + shifMulter*MOTOR_SHIFT,1);
}
void MainWindow::on_stopButton_clicked(){
    modbus_6(HATL + shifMulter*MOTOR_SHIFT,1);
}

void MainWindow::on_motorBox_currentIndexChanged(int index){
    shifMulter = index;
}


