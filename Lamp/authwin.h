#ifndef AUTHWIN_H
#define AUTHWIN_H

#include <QDialog>

namespace Ui {
class AuthWin;
}

class AuthWin : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWin(QWidget *parent = 0);
    ~AuthWin();

signals:
    void hostname(QString);
    void port(u_int16_t);

private slots:
    void on_m_ok_button_released();

    void on_m_quit_button_released();

private:
    Ui::AuthWin *ui;
};

#endif // AUTHWIN_H
