#include "messagedialog.h"
#include "ui_messagedialog.h"
#include "globalvariable.h"

MessageDialog::MessageDialog(QWidget *parent)
    :QToolBox(parent)
{
    this->resize(400,500);
    this->setWindowTitle("消息/通知");
    QFont fontStyle = GetFont();
    this->setStyleSheet(GetStyle());
    this->setFont(fontStyle);

    messageNum = 3;
    /*查询发给自己的消息*/
    vector<StationMessageStruct> messages=client.getStationMessage();
    vector<StationMessageStruct>::iterator iter = messages.begin();
    for (;iter != messages.end() ;++iter)
    {
          StationMessageStruct mes = *iter;  // *iter就是vector的每个元素
         // cout<<mes.SenderName<<" "<<mes.ReceiverName<<" "<<mes.Message<<" "<<mes.Time<<endl;
        content = new QLabel(this);
        messageLayout = new QVBoxLayout(this);
        content->setMaximumWidth(350);
        content->setWordWrap(true);
        groupBox = new QGroupBox(this);
        content->setText(QString::fromStdString(mes.Message));
        messageLayout->addWidget(content);
        messageLayout->setMargin(10);
        messageLayout->setAlignment(Qt::AlignHCenter);
        messageLayout->addStretch();
        groupBox->setLayout(messageLayout);
        this->addItem((QWidget*)groupBox,QString("发送人:%1\n时间:%2").arg(QString::fromStdString(mes.SenderName)).arg(QString::fromStdString(mes.Time)));
    }
}

MessageDialog::~MessageDialog()
{
    delete ui;
}
