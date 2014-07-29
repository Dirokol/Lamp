#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "authwin.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Lamp");

    AuthWin win(this);

    connect(&win, SIGNAL(hostname(QString)), this, SLOT(setHostName(QString)));
    connect(&win, SIGNAL(port(u_int16_t)), this, SLOT(setPort(u_int16_t)));

    win.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_exit_button_released()
{
    // TODO Записать завершение подключения
    exit(EXIT_SUCCESS);
}
