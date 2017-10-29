#include "detaildialog.h"
#include "ui_detaildialog.h"
#include <QMessageBox>
#include <iostream>
#include <QFileDialog>
#include <QGroupBox>
#include "globalvariable.h"
#include "mainwindow.h"

DetailDialog::DetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailDialog)
{
    ui->setupUi(this);
    this->resize(800,600);
    this->setWindowTitle("详细信息");
    QFont fontStyle = GetFont();
    this->setFont(fontStyle);
    this->setStyleSheet(GetStyle());
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 第一行布局：用户名和注销按钮
    QPixmap image; //定义一张图片
    image.load("images/avatar.png");//加载
    avatar->clear();//清空
    avatar->setPixmap(image);//加载到Label标签
    avatar->show();//显示
    avatar->setMaximumHeight(80);
    avatar->setMaximumWidth(80);
    avatar->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(avatar,0,0,3,2);
    userName->setText("发布人：C++Team");
    //userName->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(userName,0,1,1,2);

    startLabel->setText("始发地：");
    mainLayout->addWidget(startLabel,1,1,1,1);
    start->setText(startLocate);
    mainLayout->addWidget(start,1,2,1,1);
    timeLabel->setText("出发时间：");
    mainLayout->addWidget(timeLabel,1,3,1,1);
    time->setText(startDate);
    mainLayout->addWidget(time,1,4,1,1);

    endLabel->setText("目的地：");
    mainLayout->addWidget(endLabel,2,1,1,1);
    end->setText(endLocate);
    mainLayout->addWidget(end,2,2,1,1);
    typeLabel->setText("玩耍方式：");
    mainLayout->addWidget(typeLabel,2,3,1,1);
    type->setText(hiType);
    mainLayout->addWidget(type,2,4,1,1);

    peopleNumLabel->setText("人数：");
    mainLayout->addWidget(peopleNumLabel,3,1,1,1);
    peopleNum->setText("hiType");
    mainLayout->addWidget(peopleNum,3,2,1,1);
    phoneLabel->setText("联系方式：");
    mainLayout->addWidget(phoneLabel,3,3,1,1);
    phone->setText(hiType);
    mainLayout->addWidget(phone,3,4,1,1);
    backBtn->setText("返回");
    backBtn->setFocusPolicy(Qt::NoFocus);
    mainLayout->addWidget(backBtn,3,5,1,1);

    // 反馈信息
    QGroupBox *groupBox = new QGroupBox(this);
    groupBox->setTitle("团员");
    QVBoxLayout *vbox = new QVBoxLayout;
    messageWidget->setMinimumHeight(400);
    vbox->addWidget(messageWidget);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    mainLayout->addWidget(groupBox, 4, 0, 1, 6);

    this->setLayout(mainLayout);
    search();
    connect(backBtn, &QPushButton::clicked, this, &DetailDialog::BackBtnClicked);
}

void DetailDialog::BackBtnClicked()
{
    this->hide();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}

void DetailDialog::search()
{
    messageWidget->setColumnCount(6);
    messageWidget->setRowCount(12);   // 设置题目占的行数
    messageWidget->setHorizontalHeaderLabels(QStringList() << tr("用户名") << tr("性别") << tr("学校")<< tr("游玩次数") << tr("电话") << tr("tag"));    // 设置列名
    messageWidget->setColumnWidth(1, 80);
    messageWidget->setColumnWidth(2, 120);
    messageWidget->setColumnWidth(4, 160);
    messageWidget->setColumnWidth(5, 160);
    messageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    for(int i = 0; i < 10; i++)
    {
        messageWidget->setRowHeight(i,50);
        QTableWidgetItem *item0 = messageWidget->item(i,0); // 发布人
        QTableWidgetItem *item1 = messageWidget->item(i,1); // 人数
        QTableWidgetItem *item2 = messageWidget->item(i,2); // 始发地
        QTableWidgetItem *item3 = messageWidget->item(i,3); // 目的地
        QTableWidgetItem *item4 = messageWidget->item(i,4); // 出发时间
        QTableWidgetItem *item5 = messageWidget->item(i,5); // 备注

        QWidget *remark = new QWidget(this);
        QGridLayout *layout = new QGridLayout(this);
        // 创建QPushButton控件
        QPushButton *joinBtn = new QPushButton(this);
        joinBtn->setText("活泼");
        layout->addWidget(joinBtn,0,0,1,1);
        QPushButton *detailBtn = new QPushButton(this);
        detailBtn->setText("爱笑");
        layout->addWidget(detailBtn,0,1,1,1);
        remark->setLayout(layout);

        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(QString("张三%1").arg(i));
            item0->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 0, item0);

            item1 = new QTableWidgetItem;
            item1->setText(QString("男"));
            item1->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 1, item1);

            item2 = new QTableWidgetItem;
            item2->setText(QString("武汉大学"));
            item2->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 2, item2);

            item3 = new QTableWidgetItem;
            item3->setText(QString("%1次").arg(i));
            item3->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 3, item3);

            item4 = new QTableWidgetItem;
            item4->setText(QString("1871277%132").arg(i));
            item4->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 4, item4);

            item5 = new QTableWidgetItem;
            messageWidget->setCellWidget(i,5,remark);
        }
    }
    messageWidget->show();
}

DetailDialog::~DetailDialog()
{
    delete ui;
}
