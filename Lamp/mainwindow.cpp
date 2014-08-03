#include <QAbstractSocket>

#include <iostream>

#include <QtNetwork>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "authwin.h"
#include "structs.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Lamp");

    m_hostname = "";
    m_port = 0;

    AuthWin win(this);

    connect(&win, SIGNAL(hostname(QString)), this, SLOT(setHostName(QString)));
    connect(&win, SIGNAL(port(u_int16_t)), this, SLOT(setPort(u_int16_t)));

    win.exec();

    if (!connecting())
        exit(EXIT_FAILURE);

    connect(m_tcp, SIGNAL(readyRead()), this, SLOT(on_recv_server()));

 //   ui->textBrowser->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_exit_button_released()
{
    disconnecting();
    exit(EXIT_SUCCESS);
}

bool MainWindow::connecting()
{
    m_tcp = new QTcpSocket(this);

    m_tcp->connectToHost(m_hostname, m_port);
    m_tcp->waitForConnected();

    if (m_tcp->state() != QAbstractSocket::ConnectedState)
    {
        delete m_tcp;
        m_tcp = NULL;

        return false;
    }

    return true;
}

void MainWindow::disconnecting()
{
    static char cmd_bye[] = "bye";

    send_to_server(cmd_bye, strlen(cmd_bye));

    if (m_tcp && m_tcp->state() != QAbstractSocket::UnconnectedState)
    {
        m_tcp->disconnect();
        m_tcp->waitForDisconnected();
    }
    delete m_tcp;
    m_tcp = NULL;
}

bool MainWindow::send_to_server(const void *buf, size_t sz)
{
    if (m_tcp && m_tcp->state() == QAbstractSocket::ConnectedState)
    {
        size_t len = sz;
        char *dst = (char *)buf;

        while (len > 0)
        {
            ssize_t sent = m_tcp->write(dst, len);
            m_tcp->flush();

            if (sent < 0)
                return false;

            len -= sent;
            dst += sent;
        }
        return true;
    }
    return false;
}

void MainWindow::on_recv_server()
{
    char recvbuf[1024];
    memset(recvbuf, 0, sizeof(recvbuf));
    uint lrecv = m_tcp->read(recvbuf, sizeof(recvbuf));
    Head *head = (Head *)recvbuf;
    requestColor *req;

    switch (head->ts)
    {
    case 0x12:
        on_off_lamp(true);
        break;
    case 0x13:
        on_off_lamp(false);
        break;
    case 0x20:
        req = (requestColor *)recvbuf;
        set_lamp_color(req->m_red, req->m_green, req->m_blue);
        break;
    default:
        std::cerr << "Unknown type of package" << std::endl;
        break;
    }
}

void MainWindow::on_off_lamp(bool flag)
{
    ui->textBrowser->setVisible(flag);
}

void MainWindow::set_lamp_color(uint8_t red, uint8_t green, uint8_t blue)
{
    ui->textBrowser->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(red).arg(green).arg(blue));
}
