#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    QString     m_hostname;
    u_int16_t   m_port;
};

#endif // MAINWINDOW_H
