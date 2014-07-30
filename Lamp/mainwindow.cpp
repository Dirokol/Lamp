#include <QAbstractSocket>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "authwin.h"

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

}
