#include "authwin.h"
#include "ui_authwin.h"

AuthWin::AuthWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthWin)
{
    ui->setupUi(this);
}

AuthWin::~AuthWin()
{
    delete ui;
}

void AuthWin::on_m_ok_button_released()
{
    emit(hostname(ui->m_host_lineEdit->text()));
    emit(port(ui->m_port_lineEdit->text().toInt()));

    this->accept();
}

void AuthWin::on_m_quit_button_released()
{
    exit(EXIT_SUCCESS);
}
