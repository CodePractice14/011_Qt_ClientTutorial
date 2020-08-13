#ifndef MAINCLIENTWINDOW_H
#define MAINCLIENTWINDOW_H

#include <QMainWindow>
#include "clientside.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainClientWindow; }
QT_END_NAMESPACE

class MainClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainClientWindow(QWidget *parent = nullptr);
    ~MainClientWindow();

public slots:
    void setStatus(bool newStatus);
    void recievedSomething(QString msg);
    void gotError(QAbstractSocket::SocketError err);

private slots:
    void on_pushButton_send_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();

private:
    Ui::MainClientWindow *ui;
    ClientSide *client;
};
#endif // MAINCLIENTWINDOW_H
