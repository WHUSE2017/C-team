#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include "logindialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    QFont font;
    font.setPointSize(20);
    font.setFamily(("simsun"));
    this->setFont(font);
    this->setWindowTitle("注册");

    nameLabel->setText("用户名：");
    registerLayout->addWidget(nameLabel,0,0,1,1);
    userName->setPlaceholderText("请输入用户名");
    registerLayout->addWidget(userName,0,1,1,1);

    pwdLabel->setText("密码：");
    registerLayout->addWidget(pwdLabel,1,0,1,1);
    userPwd->setPlaceholderText("请输入密码");
    registerLayout->addWidget(userPwd,1,1,1,1);

    pwdLabel2->setText("再次密码：");
    registerLayout->addWidget(pwdLabel2,2,0,1,1);
    userPwd2->setPlaceholderText("请再次输入密码");
    registerLayout->addWidget(userPwd2,2,1,1,1);

    sexLabel->setText("性别：");
    registerLayout->addWidget(sexLabel,3,0,1,1);
    sex->setPlaceholderText("请输入性别");
    registerLayout->addWidget(sex,3,1,1,1);

    phoneLabel->setText("电话：");
    registerLayout->addWidget(phoneLabel,4,0,1,1);
    phone->setPlaceholderText("请输入电话");
    registerLayout->addWidget(phone,4,1,1,1);

    emailLabel->setText("邮箱：");
    registerLayout->addWidget(emailLabel,5,0,1,1);
    email->setPlaceholderText("请输入有效的邮箱");
    registerLayout->addWidget(email,5,1,1,1);

    introductionLabel->setText("描述：");
    registerLayout->addWidget(introductionLabel,6,0,1,1);
    introduction->setPlaceholderText("介绍一下自己");
    registerLayout->addWidget(introduction,6,1,3,1);

    backBtn->setText("返回");
    registerLayout->addWidget(backBtn,9,0,1,1);
    confirmBtn->setText("确认");
    registerLayout->addWidget(confirmBtn,9,1,1,1);
    this->setLayout(registerLayout);
    connect(confirmBtn, &QPushButton::clicked, this, &RegisterDialog::on_confirmBtn_clicked);
    connect(backBtn, &QPushButton::clicked, this, &RegisterDialog::on_backBtn_clicked);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_confirmBtn_clicked()
{
    QMessageBox::information(this, tr("Welcome"), tr("恭喜注册成功！"), QMessageBox::tr("确定"));
}

void RegisterDialog::on_backBtn_clicked()
{
    LoginDialog *loginDlg = new LoginDialog;
    this->hide();
    loginDlg->show();
}
