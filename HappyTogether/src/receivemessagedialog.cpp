#include "receivemessagedialog.h"
#include "ui_messagedialog.h"
#include "globalvariable.h"

ReceiveMessageDialog::ReceiveMessageDialog(QWidget *parent)
    :QToolBox(parent)
{
    this->resize(400,500);
    this->setWindowTitle("消息/通知");
    QFont fontStyle = GetFont();
    this->setStyleSheet(GetStyle());
    this->setFont(fontStyle);

    /*查询发给自己的消息*/
    vector<StationMessageStruct> messages=client.getStationMessage();
    vector<StationMessageStruct>::iterator iter = messages.begin();
    bool flag = false;
    for (;iter != messages.end() ;++iter)
    {
        flag = true;
        StationMessageStruct mes = *iter;  // *iter就是vector的每个元素
         // cout<<mes.SenderName<<" "<<mes.ReceiverName<<" "<<mes.Message<<" "<<mes.Time<<endl;
        content = new QLabel(this);
        messageLayout = new QVBoxLayout(this);
        content->setMaximumWidth(350);
        content->setWordWrap(true);
        groupBox = new QGroupBox(this);
        content->setText(StdStringToQString(mes.Message));
        messageLayout->addWidget(content);
        messageLayout->setMargin(10);
        messageLayout->setAlignment(Qt::AlignHCenter);
        messageLayout->addStretch();
        groupBox->setLayout(messageLayout);
        this->addItem((QWidget*)groupBox,QString("发送人:%1\n时间:%2").arg(StdStringToQString(mes.SenderName)).arg(StdStringToQString(mes.Time)));
    }
    if(!flag)
        this->addItem(warning, "暂无消息");
}

ReceiveMessageDialog::~ReceiveMessageDialog()
{
    delete ui;
}
