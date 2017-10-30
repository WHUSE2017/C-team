#include <QMessageBox>
#include "logindialog.h"
#include "ui_logindialog.h"

#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <cstdlib>
#include <time.h>
#include "globalvariable.h"
#include <QFontDatabase>
#include <QTextCodec>
#include "client/UserClient.h"
#include <QDesktopWidget>
#include "iniparser.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
//    QFont font;
//    font.setPointSize(20);
//    font.setFamily(("SentyTEA 新蒂下午茶体"));
    //中文支持
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //int font = QFontDatabase::addApplicationFont("./fonts/HiraginoSansGB-W3-Alphabetic.ttf");
    QFont fontStyle = GetFont();
    this->setFont(fontStyle);
    this->setWindowTitle("登录");
    this->setStyleSheet(GetStyle());



    nameLabel->setText("用户名:");
    loginLayout->addWidget(nameLabel,0,0,1,1);
    userName->setPlaceholderText("请输入用户名");
    loginLayout->addWidget(userName,0,1,1,2);


    pwdLabel->setText("密  码:");
    loginLayout->addWidget(pwdLabel,1,0,1,1);
    userPwd->setPlaceholderText("请输入密码");
    userPwd->setEchoMode(QLineEdit::Password);
    loginLayout->addWidget(userPwd,1,1,1,2);

    verifyLabel->setText("验证码:");
    loginLayout->addWidget(verifyLabel,2,0,1,1);
    verifyCode->setPlaceholderText("请输入验证码");
    loginLayout->addWidget(verifyCode,2,1,1,1);

    srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
    int temp = rand()%10 + 1;
    verifyNumber = ((rand()+10000)*temp)%10000;
    if(verifyNumber < 1000) verifyNumber *= 10;
    verifyBtn->setText(QString("%1").arg(verifyNumber));
    verifyBtn->setMinimumWidth(120);
    verifyBtn->setFocusPolicy(Qt::NoFocus);
    loginLayout->addWidget(verifyBtn,2,2,1,1);

    rememberPwd->setText("记住密码");
    loginLayout->addWidget(rememberPwd,3,0,1,1);

    registerBtn->setText("注册");
    loginLayout->addWidget(registerBtn,4,0,1,1);
    loginBtn->setText("登录");
    loginLayout->addWidget(loginBtn,4,2,1,1);
    this->setLayout(loginLayout);
    connect(loginBtn, &QPushButton::clicked, this, &LoginDialog::LoginBtnClicked);
    connect(registerBtn, &QPushButton::clicked, this, &LoginDialog::RegisterBtnClicked);
    //connect(verifyCode, SIGNAL(clicked()), this, SLOT(on_verifyCodeBtn_clicked()));
    connect(verifyBtn, &QPushButton::clicked, this, &LoginDialog::VerifyBtnClicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::VerifyBtnClicked()
{
    srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
    int temp = rand()%10 + 1;
    verifyNumber = ((rand()+10000)*temp)%10000;
    if(verifyNumber < 1000) verifyNumber *= 10;
    verifyBtn->setText(QString("%1").arg(verifyNumber));
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *evt)
{
    Q_UNUSED(evt);
    emit clicked(this);
}

void LoginDialog::LoginBtnClicked()
{
    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    userNameGlobal = userName->text();
    if(userName->text() == NULL) {
        QMessageBox::warning(this, tr("警告！"),
                    tr("用户名不能为空"),
                    QMessageBox::tr("确定"));
        return ;
    }

    if(userPwd->text() == NULL) {
        QMessageBox::warning(this, tr("警告！"),
                    tr("密码不能为空"),
                    QMessageBox::tr("确定"));
        return ;
    }
    if(verifyCode->text().trimmed() == QString::number(verifyNumber,10))
    {

        if (client.Login((char*)QStringToStdString(userName->text().trimmed()).data(),
                    (char*)QStringToStdString(userPwd->text().trimmed()).data()))
        {
           this->hide();
           w->show();
           w->move((this->geometry().center() - this->rect().center())/2);
           //w->move((this->geometry().width() - this->rect().width())/2,(this->geometry().height() - this->rect().height())/2);
           //w->move(QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2;
        }
        else
        {
            QMessageBox::warning(this, tr("警告！"),
                        tr("用户名或密码错误！"),
                        QMessageBox::tr("确定"));
            // 清空内容并定位光标
            userName->clear();
            userPwd->clear();
            userName->setFocus();
        }
    }
    else
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("验证码错误！"),
                    QMessageBox::tr("确定"));
    }
}

void LoginDialog::RegisterBtnClicked()
{
    this->hide();
    registerDlg->show();
}
