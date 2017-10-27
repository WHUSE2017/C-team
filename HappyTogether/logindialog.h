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
#include <QCheckBox>
#include <string>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void clicked(LoginDialog* clicked);

protected:
    void mouseReleaseEvent(QMouseEvent* );

private:
    Ui::LoginDialog *ui;

    QLabel *nameLabel = new QLabel(this);
    QLabel *pwdLabel = new QLabel(this);
    QLineEdit *userName = new QLineEdit(this);  //用户名称
    QLineEdit *userPwd = new QLineEdit(this);   //登陆密码
    QLabel *verifyLabel = new QLabel(this);
    QLineEdit *verifyCode = new QLineEdit(this);    //验证码
    QPushButton *verifyBtn = new QPushButton(this);      //系统生成的验证码
    int verifyNumber;
    QCheckBox *rememberPwd = new QCheckBox(this);
    QPushButton *loginBtn = new QPushButton(this);  //登录按钮
    QPushButton *registerBtn = new QPushButton(this);//注册按钮
    QGridLayout *loginLayout = new QGridLayout(this);

    RegisterDialog *registerDlg = new RegisterDialog;
    MainWindow *w = new MainWindow;

private slots:
    void LoginBtnClicked();
    void RegisterBtnClicked();
    void VerifyBtnClicked();
};
#endif // LOGINDIALOG_H

