#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setHostName(QString hostname) { m_hostname = hostname; }
    void setPort(u_int16_t port) { m_port = port; }

private slots:
    void on_m_exit_button_released();
    void on_recv_server();
    
private:
    bool connecting();
    void disconnecting();
    bool send_to_server(const void *buf, size_t sz);

    Ui::MainWindow *ui;

    QString     m_hostname;
    u_int16_t   m_port;

    QTcpSocket  *m_tcp;
};

#endif // MAINWINDOW_H
