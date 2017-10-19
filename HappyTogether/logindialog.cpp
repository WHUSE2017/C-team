#include <QMessageBox>
#include "logindialog.h"
#include "ui_logindialog.h"

#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <cstdlib>
#include <time.h>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    QFont font;
    font.setPointSize(20);
    font.setFamily(("simsun"));
    this->setFont(font);
    this->setWindowTitle("登录");

    nameLabel->setText("用户名：");
    loginLayout->addWidget(nameLabel,0,0,1,1);
    userName->setPlaceholderText("请输入用户名");
    loginLayout->addWidget(userName,0,1,1,1);

    pwdLabel->setText("密  码：");
    loginLayout->addWidget(pwdLabel,1,0,1,1);
    userPwd->setPlaceholderText("请输入密码");
    loginLayout->addWidget(userPwd,1,1,1,1);

    verifyLabel->setText("验证码：");
    loginLayout->addWidget(verifyLabel,2,0,1,1);
    verify->setPlaceholderText("请输入下面的验证码");
    loginLayout->addWidget(verify,2,1,1,1);


    srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
    verifyNumber = (rand()+1000)%10000;
    verifyCode->setText(QString("%1").arg(verifyNumber));
    verifyCode->setAlignment(Qt::AlignCenter);
    loginLayout->addWidget(verifyCode,3,0,1,2);

    registerBtn->setText("注册");
    loginLayout->addWidget(registerBtn,4,0,1,1);
    loginBtn->setText("登录");
    loginLayout->addWidget(loginBtn,4,1,1,1);
    this->setLayout(loginLayout);
    connect(loginBtn, &QPushButton::clicked, this, &LoginDialog::on_loginBtn_clicked);
    connect(registerBtn, &QPushButton::clicked, this, &LoginDialog::on_registerBtn_clicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    if(userName->text().trimmed() == tr("123") &&
           userPwd->text() == tr("123"))
    {
       if(verify->text().trimmed() == QString::number(verifyNumber,10))
       {
           this->hide();
           w->show();
       }
       else
       {
           QMessageBox::warning(this, tr("警告！"),
                       tr("验证码错误！"),
                       QMessageBox::tr("确定"));
       }
    } else {
       QMessageBox::warning(this, tr("警告！"),
                   tr("用户名或密码错误！"),
                   QMessageBox::tr("确定"));
       // 清空内容并定位光标
       userName->clear();
       userPwd->clear();
       userName->setFocus();
    }
}

void LoginDialog::on_registerBtn_clicked()
{
    this->hide();
    registerDlg->show();
}
