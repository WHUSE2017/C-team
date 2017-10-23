#include "messagedialog.h"
#include "ui_messagedialog.h"
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>

MessageDialog::MessageDialog(QWidget *parent)
    :QToolBox(parent)
{
    this->resize(400,600);
    this->setWindowTitle("消息/通知");
    QFont font;
    font.setPointSize(20);
    font.setFamily(("simsun"));
    this->setFont(font);
    //***************初始化我的好友*****************
        toolBtn1_1=new QToolButton;
        toolBtn1_1->setText(tr("张三"));
        toolBtn1_1->setIcon(QPixmap("res/11.bmp"));
        toolBtn1_1->setIconSize(QPixmap("res/11.bmp").size());
        toolBtn1_1->setAutoRaise(true);
        toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        toolBtn1_2=new QToolButton;
        toolBtn1_2->setText(tr("李四"));
        toolBtn1_2->setIcon(QPixmap("res/12.bmp"));
        toolBtn1_2->setIconSize(QPixmap("res/12.bmp").size());
        toolBtn1_2->setAutoRaise(true);
        toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        toolBtn1_3=new QToolButton;
        toolBtn1_3->setText(tr("王五"));
        toolBtn1_3->setIcon(QPixmap("res/13.bmp"));
        toolBtn1_3->setIconSize(QPixmap("res/13.bmp").size());
        toolBtn1_3->setAutoRaise(true);
        toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        toolBtn1_4=new QToolButton;
        toolBtn1_4->setText(tr("小赵"));
        toolBtn1_4->setIcon(QPixmap("res/14.bmp"));
        toolBtn1_4->setIconSize(QPixmap("res/14.bmp").size());
        toolBtn1_4->setAutoRaise(true);
        toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        toolBtn1_5=new QToolButton;
        toolBtn1_5->setText(tr("小孙"));
        toolBtn1_5->setIcon(QPixmap("res/15.bmp"));
        toolBtn1_5->setIconSize(QPixmap("res/15.bmp").size());
        toolBtn1_5->setAutoRaise(true);
        toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //***************添加我的好友*****************
        QGroupBox *groupBox1=new QGroupBox;
        QVBoxLayout *layout1=new QVBoxLayout(groupBox1);
        layout1->setMargin(10);
        layout1->setAlignment(Qt::AlignHCenter);
        layout1->addWidget(toolBtn1_1);
        layout1->addWidget(toolBtn1_2);
        layout1->addWidget(toolBtn1_3);
        layout1->addWidget(toolBtn1_4);
        layout1->addWidget(toolBtn1_5);
        layout1->addStretch();
    //***************陌生人*********************
        toolBtn2_1=new QToolButton;
        toolBtn2_1->setText(tr("小王"));
        toolBtn2_1->setIcon(QPixmap("res/21.bmp"));
        toolBtn2_1->setIconSize(QPixmap("res/21.bmp").size());
        toolBtn2_1->setAutoRaise(true);
        toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        toolBtn2_2=new QToolButton;
        toolBtn2_2->setText(tr("小张"));
        toolBtn2_2->setIcon(QPixmap("res/22.bmp"));
        toolBtn2_2->setIconSize(QPixmap("res/22.bmp").size());
        toolBtn2_2->setAutoRaise(true);
        toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //***************添加陌生人*****************
        QGroupBox *groupBox2=new QGroupBox;
        QVBoxLayout *layout2=new QVBoxLayout(groupBox2);
        layout2->setMargin(10);
        layout2->setAlignment(Qt::AlignHCenter);
        layout2->addWidget(toolBtn2_1);
        layout2->addWidget(toolBtn2_2);
        layout2->addStretch();
    //***************黑名单*********************
        toolBtn3_1=new QToolButton;
        toolBtn3_1->setText(tr("小王"));
        toolBtn3_1->setIcon(QPixmap("res/31.bmp"));
        toolBtn3_1->setIconSize(QPixmap("res/31.bmp").size());
        toolBtn3_1->setAutoRaise(true);
        toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        toolBtn3_2=new QToolButton;
        toolBtn3_2->setText(tr("小张"));
        toolBtn3_2->setIcon(QPixmap("res/32.bmp"));
        toolBtn3_2->setIconSize(QPixmap("res/32.bmp").size());
        toolBtn3_2->setAutoRaise(true);
        toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //***************添加黑名单*****************
        QGroupBox *groupBox3=new QGroupBox;
        QVBoxLayout *layout3=new QVBoxLayout(groupBox3);
        layout3->setMargin(10);
        layout3->setAlignment(Qt::AlignHCenter);
        layout3->addWidget(toolBtn3_1);
        layout3->addWidget(toolBtn3_2);
        layout3->addStretch();
    //***************添加至主窗口*****************

        this->addItem((QWidget*)groupBox1,tr("我的好友"));
        this->addItem((QWidget*)groupBox2,tr("陌生人"));
        this->addItem((QWidget*)groupBox3,tr("黑名单"));
}

MessageDialog::~MessageDialog()
{
    delete ui;
}
