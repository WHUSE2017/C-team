#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include "registerdialog.h"
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

    QLabel *nameLabel = new QLabel(this);
    QLabel *pwdLabel = new QLabel(this);
    QLineEdit *userName = new QLineEdit(this);
    QLineEdit *userPwd = new QLineEdit(this);
    QLabel *verifyLabel = new QLabel(this);
    QLineEdit *verify = new QLineEdit(this);
    QLabel *verifyCode = new QLabel(this);      // 获取的验证码
    int verifyNumber;
    QPushButton *loginBtn = new QPushButton(this);
    QPushButton *registerBtn = new QPushButton(this);
    QGridLayout *loginLayout = new QGridLayout(this);

    RegisterDialog *registerDlg = new RegisterDialog;
    MainWindow *w = new MainWindow;

private slots:
    void on_loginBtn_clicked();
    void on_registerBtn_clicked();
};
#endif // LOGINDIALOG_H

