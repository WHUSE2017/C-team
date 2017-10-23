#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>

#include "logindialog.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,600);
    this->setWindowTitle("一起Happy");
    QFont font;
    font.setPointSize(20);
    font.setFamily(("simsun"));
    this->setFont(font);

    // 创建注销菜单
    QAction *menu_O = ui->menuBar->addAction(tr("注销(&O)"));

    // 创建资料菜单
    QAction *menu_D = ui->menuBar->addAction(tr("资料(&D)"));

    // 创建消息菜单
    QAction *menu_M = ui->menuBar->addAction(tr("消息(&M)"));

    // 创建邀请菜单
    QAction *menu_I = ui->menuBar->addAction(tr("邀请(&I)"));

    // 创建帮助菜单
    QMenu *menu_H = ui->menuBar->addMenu(tr("帮助(&H)"));
    QAction *parameterAction = new QAction(tr("&文档"), this);
    menu_H->addAction(parameterAction);
    QAction *aboutAction = new QAction(tr("&关于"), this);
    menu_H->addAction(aboutAction);

    // 第一行布局：用户名和注销按钮
    userName->setText("C++Team");
    userName->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(userName,0,0,1,4);

    startLabel->setText("始发地：");
    mainLayout->addWidget(startLabel,1,0,1,1);
    mainLayout->addWidget(start,1,1,1,1);
    timeLabel->setText("出发时间：");
    mainLayout->addWidget(timeLabel,1,2,1,1);
    mainLayout->addWidget(time,1,3,1,1);

    endLabel->setText("目的地：");
    mainLayout->addWidget(endLabel,2,0,1,1);
    mainLayout->addWidget(end,2,1,1,1);
    typeLabel->setText("玩耍方式：");
    mainLayout->addWidget(typeLabel,2,2,1,1);
    type->addItem("电影");
    type->addItem("骑自行车");
    type->addItem("旅游");
    mainLayout->addWidget(type,2,3,1,1);

    searchBtn->setText("搜索");
    mainLayout->addWidget(searchBtn,3,3,1,1);
    publishBtn->setText("发布");
    mainLayout->addWidget(publishBtn,3,2,1,1);

    // 反馈信息
    mainLayout->addWidget(messageWidget, 4, 0, 1, 4);

    ui->centralWidget->setLayout(mainLayout);

    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::search);
    connect(menu_O,SIGNAL(triggered()),this,SLOT(off()));
    connect(menu_D,SIGNAL(triggered()),this,SLOT(off()));
    connect(menu_M,SIGNAL(triggered()),this,SLOT(off()));
    connect(menu_I,SIGNAL(triggered()),this,SLOT(off()));
}

void MainWindow::personal()
{
    LoginDialog *loginDlg = new LoginDialog;
    this->hide();
    loginDlg->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search()
{
    messageWidget->setColumnCount(6);
    messageWidget->setRowCount(12);   // 设置题目占的行数
    messageWidget->setHorizontalHeaderLabels(QStringList() << tr("发布人") << tr("人数") << tr("始发地")<< tr("目的地") << tr("出发时间") << tr("备注"));    // 设置列名
    messageWidget->setColumnWidth(4, 160);
    messageWidget->setColumnWidth(5, 160);
    messageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    for(int i = 0; i < 12; i++)
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
        joinBtn->setText("加入");
        layout->addWidget(joinBtn,0,0,1,1);
        QPushButton *detailBtn = new QPushButton(this);
        detailBtn->setText("详情");
        layout->addWidget(detailBtn,0,1,1,1);
        remark->setLayout(layout);

        connect(joinBtn, &QPushButton::clicked, this, &MainWindow::join);


        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(QString("张三%1").arg(i));
            item0->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 0, item0);

            item1 = new QTableWidgetItem;
            item1->setText(QString("%1人").arg(i));
            item1->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 1, item1);

            item2 = new QTableWidgetItem;
            item2->setText(QString("武汉%1").arg(i));
            item2->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 2, item2);

            item3 = new QTableWidgetItem;
            item3->setText(QString("重庆%1").arg(i));
            item3->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 3, item3);

            item4 = new QTableWidgetItem;
            item4->setText(QString("2017/10/1%1").arg(i));
            item4->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 4, item4);

            item5 = new QTableWidgetItem;
            messageWidget->setCellWidget(i,5,remark);
        }
    }
    messageWidget->show();
}

void MainWindow::off()
{
    LoginDialog *loginDlg = new LoginDialog;
    this->hide();
    loginDlg->show();
}

void MainWindow::join()
{
    QMessageBox::information(this, tr(""),
                tr("恭喜加入成功！"),
                QMessageBox::tr("确定"));
}