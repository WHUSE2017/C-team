#include "retrievepwddialog.h"
#include "ui_retrievepwddialog.h"
#include "globalvariable.h"

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

    security->setText("密保问题：");
    retrievePwdLayout->addWidget(security,0,0,1,1);
    securityQuestion->setText("你的爸爸叫什么？");
    retrievePwdLayout->addWidget(securityQuestion,0,1,1,2);
    securityAnswer->setPlaceholderText("请输入你的答案");
    retrievePwdLayout->addWidget(securityAnswer,1,0,1,3);
    queryBtn->setText("确认");
    retrievePwdLayout->addWidget(queryBtn,2,2,1,1);
    this->setLayout(retrievePwdLayout);
    connect(queryBtn,&QPushButton::clicked, this, &RetrievePwdDialog::QueryBtnClicked);
}

void RetrievePwdDialog::QueryBtnClicked()
{

}

RetrievePwdDialog::~RetrievePwdDialog()
{
    delete ui;
}
