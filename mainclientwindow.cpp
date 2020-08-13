#include "mainclientwindow.h"
#include "ui_mainclientwindow.h"

MainClientWindow::MainClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainClientWindow)
{
    ui->setupUi(this);

    ui->btnDisconnectFromServer->setVisible(false);
    client = new ClientSide("localhost", 6547);

    setStatus(client->getStatus());

    connect(client, &ClientSide::hasReadSome, this, &MainClientWindow::recievedSomething);
    connect(client, &ClientSide::statusChanged, this, &MainClientWindow::setStatus);
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(gotError(QAbstractSocket::SocketError)));

    connect(ui->btnSendMessage, &QPushButton::clicked, this, &MainClientWindow::on_pushButton_send_clicked);
    connect(ui->btnConnectToServer, &QPushButton::clicked, this, &MainClientWindow::on_pushButton_connect_clicked);
    connect(ui->btnDisconnectFromServer, &QPushButton::clicked, this, &MainClientWindow::on_pushButton_disconnect_clicked);

}

MainClientWindow::~MainClientWindow()
{
    delete client;
    delete ui;
}

void MainClientWindow::setStatus(bool newStatus)
{
    if(newStatus)
    {
        ui->lblStatus->setText(
                    tr("<font color=\"green\">CONNECTED</font>"));
        ui->btnConnectToServer->setVisible(false);
        ui->btnDisconnectFromServer->setVisible(true);
    }
    else
    {
        ui->lblStatus->setText(
                    tr("<font color=\"red\">DISCONNECTED</font>"));
        ui->btnConnectToServer->setVisible(true);
        ui->btnDisconnectFromServer->setVisible(false);
    }
}

void MainClientWindow::recievedSomething(QString msg)
{
    ui->txtEdit_log->append(msg);
}

void MainClientWindow::gotError(QAbstractSocket::SocketError err)
{
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
        break;
        case 1:
            strError = "Remote host closed the connection";
        break;
        case 2:
            strError = "Host address was not found";
        break;
        case 5:
            strError = "Connection timed out";
        break;
        default:
            strError = "Unknown error";
    }
    ui->txtEdit_log->append(strError);
}

void MainClientWindow::on_pushButton_connect_clicked()
{
    client->connect2host();
}
void MainClientWindow::on_pushButton_send_clicked()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint16(0) << ui->txtMessage->text();

    client->tcpSocket->write(arrBlock);
}
void MainClientWindow::on_pushButton_disconnect_clicked()
{
    client->closeConnection();
}
































