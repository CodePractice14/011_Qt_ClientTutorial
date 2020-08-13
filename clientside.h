#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>

class ClientSide : public QObject
{
    Q_OBJECT
public:
    ClientSide(const QString hostAdress, int portVal, QObject *parent = nullptr);

    QTcpSocket *tcpSocket;
    bool getStatus();

public slots:
    void closeConnection();
    void connect2host();

signals:
    void statusChanged(bool);
    void hasReadSome(QString msg);

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();

private:
    QString host;
    int port;
    bool status;
    quint16 m_nNextBlockSize;
    QTimer *timeoutTimer;

};

#endif // CLIENTSIDE_H
