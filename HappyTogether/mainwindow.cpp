#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <QFileDialog>

#include "logindialog.h"
#include "personaldatadialog.h"
#include "messagedialog.h"
#include "detaildialog.h"
#include <QDateEdit>
#include "globalvariable.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,600);
    this->setWindowTitle("一起High");
//    QFont font;
//    font.setPointSize(20);
//    font.setFamily(("SentyTEA 新蒂下午茶体"));
//    this->setFont(font);
    this->setFont(GetFont());  //这个必须写在样式前面
    this->setStyleSheet(GetStyle());

    // 创建注销菜单
    offAction = ui->menuBar->addAction(tr("注销(&O)"));

    // 创建资料菜单
    dataAction = ui->menuBar->addAction(tr("资料(&D)"));

    // 创建消息菜单
    messageAction = ui->menuBar->addAction(tr("消息(&M)"));

    // 创建邀请菜单
    inviteAction = ui->menuBar->addAction(tr("邀请(&I)"));

    // 创建换肤菜单
    skinMenu = ui->menuBar->addMenu(tr("换肤(&S)"));
    blackAction = skinMenu->addAction(tr("&黑色炫酷"));
    whiteAction = skinMenu->addAction(tr("&白色靓丽"));
    defaultAction = skinMenu->addAction(tr("&默认皮肤"));

    // 创建帮助菜单
    helpMenu = ui->menuBar->addMenu(tr("帮助(&H)"));
    documentAction = helpMenu->addAction(tr("&文档"));
    aboutAction = helpMenu->addAction(tr("&关于"));

    // 第一行布局：用户名和注销按钮
    QPixmap image; //定义一张图片
    image.load("images/avatar.png");//加载
    avatar->clear();//清空
    avatar->setPixmap(image);//加载到Label标签
    avatar->show();//显示
    avatar->setMaximumHeight(80);
    avatar->setMaximumWidth(80);
    mainLayout->addWidget(avatar,0,2,1,1);
    userName->setText("  西瓜");
    //userName->setAlignment(Qt::AlignCenter);
    userName->setMinimumHeight(100);
    mainLayout->addWidget(userName,0,3,1,1);

    startLabel->setText("始发地:");
    mainLayout->addWidget(startLabel,1,0,1,1);
    mainLayout->addWidget(start,1,1,1,2);
    timeLabel->setText("出发时间:");
    dateTime->setCalendarPopup(true);
    dateTime->setDateTime(QDateTime::currentDateTime());
    mainLayout->addWidget(timeLabel,1,3,1,1);
    mainLayout->addWidget(dateTime,1,4,1,2);

    endLabel->setText("目的地:");
    mainLayout->addWidget(endLabel,2,0,1,1);
    mainLayout->addWidget(end,2,1,1,2);
    typeLabel->setText("活动性质:");
    mainLayout->addWidget(typeLabel,2,3,1,1);
    type->addItem("电影");
    type->addItem("骑自行车");
    type->addItem("旅游");
    mainLayout->addWidget(type,2,4,1,2);

    searchBtn->setText("搜索");
    mainLayout->addWidget(searchBtn,3,5,1,1);
    publishBtn->setText("发布");
    mainLayout->addWidget(publishBtn,3,4,1,1);

    // 反馈信息
    messageWidget->setFont(GetFont());

    mainLayout->addWidget(messageWidget, 4, 0, 1, 6);

    ui->centralWidget->setLayout(mainLayout);

    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::SearchBtnClicked);
    connect(offAction,SIGNAL(triggered()),this,SLOT(OffActionClicked()));
    connect(dataAction,SIGNAL(triggered()),this,SLOT(DataActionClicked()));
    connect(messageAction,SIGNAL(triggered()),this,SLOT(MessageActionClicked()));
    connect(inviteAction,SIGNAL(triggered()),this,SLOT(InviteActionClicked()));
    connect(documentAction,SIGNAL(triggered()),this,SLOT(DocumentActionClicked()));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(AboutActionClicked()));
    connect(blackAction,SIGNAL(triggered()),this,SLOT(BlackActionClicked()));
    connect(whiteAction,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));
    connect(defaultAction,SIGNAL(triggered()),this,SLOT(DefaultActionClicked()));
    connect(publishBtn,&QPushButton::clicked,this,&MainWindow::PublishBtnClicked);
    connect(userName, SIGNAL(clicked()), this, SLOT(UserNameClicked()));
}

void MainWindow::BlackActionClicked()
{
    QFile qss("styles/black.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::WhiteActionClicked()
{
    QFile qss("styles/white.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::DefaultActionClicked()
{
    QFont font;
    font.setPointSize(20);
    font.setFamily(("SentyTEA 新蒂下午茶体"));
    this->setFont(font);
    this->update();
    this->repaint();
    //this->setStyleSheet(GetStyle());

    //this->setFont(GetFont());
    QFile qss("styles/default.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}

void MainWindow::UserNameClicked()
{
    QMessageBox::information(this, tr("邀请码"),
                tr("456452"),
                QMessageBox::tr("确定"));
}

void MainWindow::MouseDownEvent(QMouseEvent *evt)
{
    Q_UNUSED(evt);
    isClicked= true;
}

void MainWindow::MouseUpEvent(QMouseEvent *evt)
{
    Q_UNUSED(evt);
    if(isClicked)
    {
        emit clicked();
        isClicked = false;
    }
}

void MainWindow::MouseMoveEvent(QMouseEvent *evt)
{
    Q_UNUSED(evt);
    isClicked= false;
}

void MainWindow::MouseReleaseEvent(QMouseEvent *evt)
{
    Q_UNUSED(evt);
    emit clicked();
}

void MainWindow::InviteActionClicked()
{
    QMessageBox::information(this, tr("邀请码"),
                tr("456452"),
                QMessageBox::tr("确定"));
}

void MainWindow::PublishBtnClicked()
{
    if(JudgeEmpty() == false) return ;
    QMessageBox mb(QMessageBox::Warning, "","确定要发布当前的组团信息？");
    mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    mb.setButtonText (QMessageBox::Ok,QString("确 定"));
    mb.setButtonText (QMessageBox::Cancel,QString("取 消"));
    if(mb.exec() == QMessageBox::Ok)
    {
        QMessageBox::information(this, tr(""),
                    tr("发布成功！"),
                    QMessageBox::tr("确定"));
    }
}

void MainWindow::DetailBtnClicked()
{
    this->hide();
    DetailDialog *detailDlg = new DetailDialog;
    detailDlg->show();
}

void MainWindow::MessageActionClicked()
{
    MessageDialog *messageDlg = new MessageDialog;
    messageDlg->show();
}

void MainWindow::DataActionClicked()
{
    PersonalDataDialog *personalDataDlg = new PersonalDataDialog;
    personalDataDlg->show();
}

void MainWindow::DocumentActionClicked()
{

}

void MainWindow::AboutActionClicked()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::JudgeEmpty()
{
    if(start->text() == NULL) {
        QMessageBox::information(this, tr(""),
                    tr("出发地不能为空"),
                    QMessageBox::tr("确定"));
        return false;
    }
    if(end->text() == NULL) {
        QMessageBox::information(this, tr(""),
                    tr("目的地不能为空"),
                    QMessageBox::tr("确定"));
        return false;
    }
    if(dateTime->text() == NULL) {
        QMessageBox::information(this, tr(""),
                    tr("出发时间不能为空"),
                    QMessageBox::tr("确定"));
        return false;
    }
    return true;
}

void MainWindow::SearchBtnClicked()
{
    startLocate = start->text();
    endLocate = end->text();
    startDate = dateTime->text();
    hiType = type->currentText();
    if(JudgeEmpty() == false) return ;
    messageWidget->setColumnCount(6);
    messageWidget->setHorizontalHeaderLabels(QStringList() << tr("发布人") << tr("人数") << tr("始发地")<< tr("目的地") << tr("出发时间") << tr("备注"));    // 设置列名
    messageWidget->setColumnWidth(4, 160);
    messageWidget->setColumnWidth(5, 160);
    //获得水平方向表头的item对象
    QTableWidgetItem *columnHeaderItem = messageWidget->horizontalHeaderItem(1);
    //columnHeaderItem->setFont(QFont("Helvetica"));  //设置字体
    columnHeaderItem->setBackgroundColor(QColor(0,60,10));  //设置单元格背景颜色
    columnHeaderItem->setTextColor(QColor(200,111,30));     //设置文字颜色

    messageWidget->setRowCount(12);   // 设置题目占的行数
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
        joinBtn->setText("一起嗨");
        layout->addWidget(joinBtn,0,0,1,1);
        QPushButton *detailBtn = new QPushButton(this);
        detailBtn->setText("详情");
        layout->addWidget(detailBtn,0,1,1,1);
        remark->setLayout(layout);

        connect(joinBtn, &QPushButton::clicked, this, &MainWindow::JoinBtnClicked);
        connect(detailBtn, &QPushButton::clicked, this, &MainWindow::DetailBtnClicked);

        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(userName->text());
            item0->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 0, item0);

            item1 = new QTableWidgetItem;
            item1->setText(QString("%1人").arg(i));
            item1->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 1, item1);

            item2 = new QTableWidgetItem;
            item2->setText(start->text());
            item2->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 2, item2);

            item3 = new QTableWidgetItem;
            item3->setText(end->text());
            item3->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 3, item3);

            item4 = new QTableWidgetItem;
            item4->setText(dateTime->text());
            item4->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 4, item4);

            item5 = new QTableWidgetItem;
            messageWidget->setCellWidget(i,5,remark);
        }
    }
    messageWidget->show();
}

void MainWindow::OffActionClicked()
{
    QMessageBox mb(QMessageBox::Warning, "","确定要注销当前用户？");
    mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    mb.setButtonText (QMessageBox::Ok,QString("确 定"));
    mb.setButtonText (QMessageBox::Cancel,QString("取 消"));
    if(mb.exec() == QMessageBox::Ok)
    {
        LoginDialog *loginDlg = new LoginDialog;
        this->hide();
        loginDlg->show();
    }
}

void MainWindow::JoinBtnClicked()
{
    QMessageBox::information(this, tr(""),
                tr("恭喜加入成功！"),
                QMessageBox::tr("确定"));
}
