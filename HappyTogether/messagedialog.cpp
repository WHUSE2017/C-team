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

    for(int i = 0; i < messageNum; i++) {
        content = new QLabel(this);
        messageLayout = new QVBoxLayout(this);
        content->setMaximumWidth(350);
        content->setWordWrap(true);
        groupBox = new QGroupBox(this);
        content->setText("既然不是网络侧问题，就是PC侧出了问题，怀疑是浏览器的配置原因，如兼容模式等，所以解决办法是尝试下载一个第三方浏览器或者重装一下浏览，更改兼容模式，发现也是徒劳的");
        messageLayout->addWidget(content);
        messageLayout->setMargin(10);
        messageLayout->setAlignment(Qt::AlignHCenter);
        messageLayout->addStretch();
        groupBox->setLayout(messageLayout);
        this->addItem((QWidget*)groupBox,QString("发送人:%1\n时间:2017102%2").arg(sender[i]).arg(i));
    }
}

MessageDialog::~MessageDialog()
{
    delete ui;
}
