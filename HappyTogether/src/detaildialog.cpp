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
    this->resize(1050,700);
    this->setWindowTitle("详细信息");
    this->setFont(GetFont());  //这个必须写在样式前面
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

    EventStruct ee_temp = client.getEventById(eventIDGlobal);

    userName->setText(QString("发布人：%1").arg(StdStringToQString(ee_temp.Publisher)));
    //userName->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(userName,0,1,1,2);

    startLabel->setText("始发地：");
    mainLayout->addWidget(startLabel,1,1,1,1);
    start->setText(StdStringToQString(ee_temp.StartSite));
    mainLayout->addWidget(start,1,2,1,1);
    timeLabel->setText("出发时间：");
    mainLayout->addWidget(timeLabel,1,3,1,1);
    time->setText(StdStringToQString(ee_temp.StartTime));
    mainLayout->addWidget(time,1,4,1,1);

    endLabel->setText("目的地：");
    mainLayout->addWidget(endLabel,2,1,1,1);
    end->setText(StdStringToQString(ee_temp.EndSite));
    mainLayout->addWidget(end,2,2,1,1);
    typeLabel->setText("玩耍方式：");
    mainLayout->addWidget(typeLabel,2,3,1,1);
    type->setText(StdStringToQString(ee_temp.EventType));
    mainLayout->addWidget(type,2,4,1,1);

    peopleNumLabel->setText("人数：");
    mainLayout->addWidget(peopleNumLabel,3,1,1,1);
    peopleNum->setText(QString::number(ee_temp.PeersNumber,10));
    mainLayout->addWidget(peopleNum,3,2,1,1);

    /*获取某个人的信息*/
    struct userStruct uinfo = client.getUserInfo((char*)ee_temp.Publisher.data());//如果用户存在
    phoneLabel->setText("联系方式：");
    mainLayout->addWidget(phoneLabel,3,3,1,1);
    phone->setText(StdStringToQString(uinfo.Phone));
    mainLayout->addWidget(phone,3,4,1,1);
    backBtn->setText("关闭");
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
//    MainWindow *mainWindow = new MainWindow;
//    mainWindow->show();
}

void DetailDialog::search()
{
    messageWidget->setColumnCount(6);

    messageWidget->setHorizontalHeaderLabels(QStringList() << tr("用户名") << tr("性别") << tr("学校")<< tr("游玩次数") << tr("电话") << tr("tag"));    // 设置列名
    messageWidget->setColumnWidth(0, 150);
    messageWidget->setColumnWidth(2, 180);
    messageWidget->setColumnWidth(4, 250);
    messageWidget->setColumnWidth(5, 180);

    messageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    vector<string> ps =client.getParticipants(eventIDGlobal);
    messageWidget->setRowCount(ps.size());   // 设置题目占的行数
    vector<string>::iterator iter3 = ps.begin();
    for (int i = 0;iter3 != ps.end() ;++iter3,i++)
    {
        string str_name = *iter3;  // *iter就是vector的每个元素
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
            item0->setText(StdStringToQString(str_name));
            item0->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 0, item0);

            /*获取某个人的信息*/
             struct userStruct uinfo = client.getUserInfo((char*)str_name.data());//如果用户存在
//             if(uinfo.UserName!="")
//                 cout<<uinfo.UserName<<" "<<uinfo.Email<<" "<<uinfo.Phone<<" "<<uinfo.UserQQ<<endl;
//             else
//                 cout<<"user not exist!\n"<<endl;

            item1 = new QTableWidgetItem;
            item1->setText(StdStringToQString(uinfo.Gender));
            item1->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 1, item1);

            item2 = new QTableWidgetItem;
            item2->setText(StdStringToQString(uinfo.University));
            item2->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 2, item2);

            item3 = new QTableWidgetItem;
            item3->setText(QString::number(uinfo.PlayTime,10));
            item3->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 3, item3);

            item4 = new QTableWidgetItem;
            item4->setText(StdStringToQString(uinfo.Phone));
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
