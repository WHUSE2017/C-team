#include "retrievepwddialog.h"
#include "ui_retrievepwddialog.h"
#include "globalvariable.h"
#include "Client/UserClient.h"
#include <QMessageBox>

RetrievePwdDialog::RetrievePwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RetrievePwdDialog)
{
    ui->setupUi(this);
    this->resize(300,100);
    QFont fontStyle = GetFont();
    this->setFont(fontStyle);
    this->setWindowTitle("密码找回");
    this->setStyleSheet(GetStyle());

    userName->setPlaceholderText("用户名");
    retrievePwdLayout->addWidget(userName,0,0,1,1);
    getBtn->setText("获取密保");
    getBtn->setStyleSheet("font-size:20px;");
    retrievePwdLayout->addWidget(getBtn,0,1,1,2);
    security->setText("密保问题：");
    retrievePwdLayout->addWidget(security,1,0,1,1);

    retrievePwdLayout->addWidget(securityQuestion,1,1,1,2);
    securityAnswer->setPlaceholderText("请输入你的答案");
    retrievePwdLayout->addWidget(securityAnswer,2,0,1,3);
    queryBtn->setText("确认");
    retrievePwdLayout->addWidget(queryBtn,3,2,1,1);
    this->setLayout(retrievePwdLayout);
    connect(queryBtn,&QPushButton::clicked, this, &RetrievePwdDialog::QueryBtnClicked);
    connect(getBtn,&QPushButton::clicked, this, &RetrievePwdDialog::GetBtnClicked);
}

void RetrievePwdDialog::QueryBtnClicked()
{
    if(securityQuestion->text() == NULL) {
        QMessageBox::information(this, tr("提示"), tr("请输入用户名获取密保问题！"), QMessageBox::tr("确定"));
        return ;
    }
    string answer = client.CheckSecurity(QStringToStdString(userName->text()), QStringToStdString(securityQuestion->text()),QStringToStdString(securityAnswer->text()));
    if(answer != "")
    {
        QMessageBox::information(this, tr("密码"), StdStringToQString(answer), QMessageBox::tr("确定"));
    }
    else {
        QMessageBox::information(this, tr("提示"), tr("答案错误！"), QMessageBox::tr("确定"));
    }
}

void RetrievePwdDialog::GetBtnClicked()
{
    if(userName->text() == NULL) {
        QMessageBox::information(this, tr("提示"), tr("请输入用户名！"), QMessageBox::tr("确定"));
        return ;
    }
    string str = client.GetSecurity(QStringToStdString(userName->text()));
//    QMessageBox::information(this, tr("提示"), StdStringToQString(str), QMessageBox::tr("确定"));
    securityQuestion->setText(StdStringToQString(str));
}

RetrievePwdDialog::~RetrievePwdDialog()
{
    delete ui;
}
