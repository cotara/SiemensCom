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

    //Консоль
    m_console = new Console(this);
    m_console->setMaximumHeight(250);
    ui->consoleLayout->addWidget(m_console);



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
    }
    else
        modbusDevice->disconnectDevice();
}

QModbusDataUnit MainWindow::readRequest(int startAdd, int num) const
{
    const auto table = static_cast<QModbusDataUnit::RegisterType>(QModbusDataUnit::HoldingRegisters);

    int startAddress = startAdd;

    quint16 numberOfEntries = num;
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}
void MainWindow::on_jogPlusButton_pressed()
{
    if (!modbusDevice){
        statusBar()->showMessage(tr("Connect failed: ") + modbusDevice->errorString(), 5000);
        return;
    }

    QModbusDataUnit m_unit = readRequest();
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

void MainWindow::onReadReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        for (int i = 0, total = int(unit.valueCount()); i < total; ++i) {
            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress() + i).arg(QString::number(unit.value(i), unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
            ui->readValue->addItem(entry);
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
