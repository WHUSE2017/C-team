#include "messagedialog.h"
#include "ui_messagedialog.h"
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>

MessageDialog::MessageDialog(QWidget *parent)
    :QToolBox(parent)
{
    this->resize(400,500);
    this->setWindowTitle("消息/通知");
    QFont font;
    font.setPointSize(20);
    font.setFamily(("simsun"));
    this->setFont(font);

    int messageNum = 3;
    QString sender[3] = {"张三","李四","王五"};

    for(int i = 0; i < messageNum; i++) {
        QLabel *message = new QLabel(this);
        message->setMaximumWidth(350);
        message->setWordWrap(true);
        message->setText("既然不是网络侧问题，就是PC侧出了问题，怀疑是浏览器的配置原因，如兼容模式等，所以解决办法是尝试下载一个第三方浏览器或者重装一下浏览，更改兼容模式，发现也是徒劳的");
        QGroupBox *groupBox=new QGroupBox;
        QVBoxLayout *layout=new QVBoxLayout(groupBox);
        layout->setMargin(10);
        layout->setAlignment(Qt::AlignHCenter);
        layout->addWidget(message);
        layout->addStretch();
        this->addItem((QWidget*)groupBox,QString("发送人:%1\n时间:2017102%2").arg(sender[i]).arg(i));
    }
}

MessageDialog::~MessageDialog()
{
    delete ui;
}
