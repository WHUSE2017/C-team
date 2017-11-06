#include "sendmessagedialog.h"
#include "ui_sendmessagedialog.h"
#include "globalvariable.h"
#include <QMessageBox>
#include <QDateTime>
#include "Client/UserClient.h"

SendMessageDialog::SendMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendMessageDialog)
{
    ui->setupUi(this);
    this->setFont(GetFont());
    this->setWindowTitle("发消息");
    this->setStyleSheet(GetStyle());

    //receiverLabel->setText("发送给:");
    receiver->setPlaceholderText("请输入收消息的用户名称");
    sendBtn->setText("发送");
    checkBtn->setText("检测");
    sendMessageLayout->addWidget(receiver,0,0,1,3);
    sendMessageLayout->addWidget(checkBtn,0,3,1,1);
    sendMessageLayout->addWidget(sendBtn,0,4,1,1);
    sendMessageLayout->addWidget(content,1,0,4,5);
    this->setLayout(sendMessageLayout);
    connect(checkBtn, &QPushButton::clicked, this, &SendMessageDialog::CheckBtnClicked);
    connect(sendBtn, &QPushButton::clicked, this, &SendMessageDialog::SendBtnClicked);
}

void SendMessageDialog::CheckBtnClicked()
{
    if(receiver->text() == NULL) {
        QMessageBox::warning(this, tr(""),
                tr("请输入收消息的用户名称！"),
                QMessageBox::tr("确定"));
        return ;
    }
    userStruct user = client.getUserInfo((char*) QStringToStdString(receiver->text()).data());
    if(user.UserName == (char*) QStringToStdString(receiver->text()).data()) {
        QMessageBox::warning(this, tr(""),
                tr("用户存在，可以发送消息。"),
                QMessageBox::tr("确定"));
    }
    else {
        QMessageBox::warning(this, tr(""),
                tr("用户不存在，请输入有效的用户名！"),
                QMessageBox::tr("确定"));
    }
    return ;
}

void SendMessageDialog::SendBtnClicked()
{
    if(receiver->text() == NULL) {
        QMessageBox::warning(this, tr(""),
                tr("请输入收消息的用户名称！"),
                QMessageBox::tr("确定"));
        return ;
    }
    if(receiver->text() == userNameGlobal) {
        QMessageBox::warning(this, tr(""),
                tr("不能给自己发消息！"),
                QMessageBox::tr("确定"));
        return ;
    }
    /*发消息
    1.不能发给自己
    2.接收者必须存在
    以上两种情况返回false
    */
    StationMessageStruct mes;
    mes.Message=QStringToStdString(content->toPlainText());
    mes.ReceiverName =QStringToStdString(receiver->text());
    mes.SenderName=QStringToStdString(userNameGlobal);
    QDateTime current_date_time = QDateTime::currentDateTime();
//    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz ddd");
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm");
    mes.Time=QStringToStdString(current_date);
    if (client.sendMessage(mes))
        QMessageBox::warning(this, tr(""),
                    tr("发送成功"),
                    QMessageBox::tr("确定"));
    else
        QMessageBox::warning(this, tr(""),
                    tr("发送失败"),
                    QMessageBox::tr("确定"));
}

SendMessageDialog::~SendMessageDialog()
{
    delete ui;
}
