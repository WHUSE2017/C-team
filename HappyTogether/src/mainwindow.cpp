#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <QFileDialog>

#include "logindialog.h"
#include "personaldatadialog.h"
#include "receivemessagedialog.h"
#include "detaildialog.h"
#include <QDateEdit>
#include "globalvariable.h"
#include"client/UserClient.h"
#include <QSignalMapper>
#include "sendmessagedialog.h"
#include "iniparser.h"
#include "activitydialog.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1200,800);
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
    if(0)
        messageMenu = ui->menuBar->addMenu(tr("消息(23)"));
    else
        messageMenu = ui->menuBar->addMenu(tr("消息(&M)"));
//    messageMenu->setStyleSheet("background-color: rgb(0, 0, 0);");
    receiveMessageAction = messageMenu->addAction("短消息");
    sendMessageAction = messageMenu->addAction("发消息");

    // 创建活动菜单
    activityMenu = ui->menuBar->addMenu(tr("活动(&A)"));
    publishAction = activityMenu->addAction("已发布的活动");
    joinAction = activityMenu->addAction("已参加的活动");
    recordAction = activityMenu->addAction("活动记录");

    // 创建邀请菜单
    //inviteAction = ui->menuBar->addAction(tr("邀请(&I)"));

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
    mainLayout->addWidget(avatar,0,3,1,1);
//    userName->setText(userNameGlobal);
    userName->setAlignment(Qt::AlignCenter);
    CMyINI *p = new CMyINI();
    p->ReadINI("conf.ini");
    userName->setText(StdStringToQString(p->GetValue("User","userName")));
    userName->setMinimumHeight(100);
    mainLayout->addWidget(userName,0,4,1,1);

    startLabel->setText("始发地:");
    mainLayout->addWidget(startLabel,1,0,1,1);
    mainLayout->addWidget(start,1,1,1,3);
    timeLabel->setText("出发日期:");
    dateTime->setCalendarPopup(true);
    dateTime->setDateTime(QDateTime::currentDateTime());
    mainLayout->addWidget(timeLabel,1,4,1,1);
    mainLayout->addWidget(dateTime,1,5,1,3);

    endLabel->setText("目的地:");
    mainLayout->addWidget(endLabel,2,0,1,1);
    mainLayout->addWidget(end,2,1,1,3);
    typeLabel->setText("活动项目:");
    mainLayout->addWidget(typeLabel,2,4,1,1);
    type->addItem("电影");
    type->addItem("骑自行车");
    type->addItem("旅游");
    type->addItem("打球");
    type->addItem("下棋");
    type->addItem("打牌");
    type->addItem("露营");
    mainLayout->addWidget(type,2,5,1,3);

    searchBtn->setText("搜索");
    mainLayout->addWidget(searchBtn,3,7,1,1);
    publishBtn->setText("发布");
    mainLayout->addWidget(publishBtn,3,6,1,1);

    // 反馈信息
    messageWidget->setFont(GetFont());

    mainLayout->addWidget(messageWidget, 4, 0, 1, 8);

    ui->centralWidget->setLayout(mainLayout);

    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::SearchBtnClicked);
    connect(offAction,SIGNAL(triggered()),this,SLOT(OffActionClicked()));
    connect(dataAction,SIGNAL(triggered()),this,SLOT(DataActionClicked()));
    connect(receiveMessageAction,SIGNAL(triggered()),this,SLOT(ReceiveMessageActionClicked()));
    connect(sendMessageAction,SIGNAL(triggered()),this,SLOT(SendMessageActionClicked()));
    //connect(inviteAction,SIGNAL(triggered()),this,SLOT(InviteActionClicked()));
    connect(documentAction,SIGNAL(triggered()),this,SLOT(DocumentActionClicked()));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(AboutActionClicked()));
    connect(blackAction,SIGNAL(triggered()),this,SLOT(BlackActionClicked()));
    connect(whiteAction,SIGNAL(triggered()),this,SLOT(WhiteActionClicked()));
    connect(defaultAction,SIGNAL(triggered()),this,SLOT(DefaultActionClicked()));
    connect(publishBtn,&QPushButton::clicked,this,&MainWindow::PublishBtnClicked);
    connect(userName, SIGNAL(clicked()), this, SLOT(UserNameClicked()));

    connect(publishAction,SIGNAL(triggered()),this,SLOT(PublishActionClicked()));
    connect(joinAction,SIGNAL(triggered()),this,SLOT(JoinActionClicked()));
    connect(recordAction,SIGNAL(triggered()),this,SLOT(RecordActionClicked()));
}

void MainWindow::PublishActionClicked()
{
    ActivityDialog *dlg = new ActivityDialog;
    dlg->show();
}

void MainWindow::JoinActionClicked()
{
    ActivityDialog *dlg = new ActivityDialog;
    dlg->show();
}

void MainWindow::RecordActionClicked()
{
    ActivityDialog *dlg = new ActivityDialog;
    dlg->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox mb(QMessageBox::Warning, "","确定要退出？");
    mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    mb.setButtonText (QMessageBox::Ok,QString("确 定"));
    mb.setButtonText (QMessageBox::Cancel,QString("取 消"));
    if(mb.exec() == QMessageBox::Ok)
    {
        TerminateProcess(hProcess, 0);
        event->accept();
    }
    else
    {
        event->ignore();
    }
    return ;
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
    QFile qss("styles/base.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
}
/*
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
*/
//void MainWindow::InviteActionClicked()
//{
//    QMessageBox::information(this, tr("邀请码"),
//                tr("456452"),
//                QMessageBox::tr("确定"));
//}

void MainWindow::PublishBtnClicked()
{
    if(JudgeEmpty() == false) return ;
    QMessageBox mb(QMessageBox::Warning, "","确定要发布当前的组团信息？");
    mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    mb.setButtonText (QMessageBox::Ok,QString("确 定"));
    mb.setButtonText (QMessageBox::Cancel,QString("取 消"));
    if(mb.exec() == QMessageBox::Ok)
    {
        /*添加event*/
        EventStruct ev;
        ev.Arrival=QStringToStdString(end->text());
        ev.EndSite=QStringToStdString(end->text());
        ev.EventType=QStringToStdString(type->currentText());
        ev.PeersNumber=1;
        ev.PlaySite=QStringToStdString(type->currentText());
        ev.Publisher=QStringToStdString(userNameGlobal);
        ev.StartSite=QStringToStdString(start->text());
        ev.StartTime=QStringToStdString(dateTime->text());
        ev.State=1;
        ev.UserId=1;

        if (client.addEvent(ev))
        {
            QMessageBox::information(this, tr(""),
                    tr("发布成功！"),
                    QMessageBox::tr("确定"));
        }
    }
}

void MainWindow::ReceiveMessageActionClicked()
{
    ReceiveMessageDialog *receiveMessageDlg = new ReceiveMessageDialog;
    receiveMessageDlg->show();
}

void MainWindow::SendMessageActionClicked()
{
    SendMessageDialog *messageDlg = new SendMessageDialog;
    messageDlg->show();
}

void MainWindow::DataActionClicked()
{
    PersonalDataDialog *personalDataDlg = new PersonalDataDialog;
    personalDataDlg->show();
}

void MainWindow::DocumentActionClicked()
{
    QMessageBox::information(this, tr("文档"),
                tr("用户可以输入始发地、目的地、选择出发类型与活动性质，点击搜索即可查看当前"
                   "行程的群组信息。选择有意愿的群组，点击“一起high”，即可加入。也可点击详情按钮，查看当前群组的人员信息。"
                   "如果当前没有该活动的群组，系统会提示您，是否发布行程。在没有具体地点或者其他打算时，用户也可以选择输入几"
                   "个条件中的一种或者几种，来查找相同行程的群组。\n关于此页面其他按钮说明：\n注销：点击后返回登录界面，用户"
                   "登录状态转换为非登录状态；\n资料：点击后显示用户当前个人资料，并且可以对资料进行修改；\n消息：点击后查看"
                   "站内消息；\n活动：可以查看已发布的活动和参加的活动，还可以看活动记录；\n换肤：根据自己风格，选择界面颜色；"
                   "\n帮助：包含软件使用文档及相关说明。"),
                QMessageBox::tr("确定"));
}

void MainWindow::AboutActionClicked()
{
    QMessageBox::information(this, tr("关于软件"),
                tr("该PC端APP，是一个同行者的信息搜索平台，旨在为喜欢游玩，但是身边同学朋友时间冲突，想找人结伴的年轻人提供"
                   "一个检索平台，让他们尽量能够快速便捷的寻找合适同行者。该APP有登录、注册、主页面（发布行程、搜索）、群组详"
                   "情、个人资料修改等功能。\n版本1.0"),
                QMessageBox::tr("确定"));
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

int resultNum = 0;

void iSignal(int b);

void MainWindow::iSlot()
{
    emit iSignal(5);
    printf("sdadasdasd\n");
}

void MainWindow::SearchBtnClicked()
{
    startLocate = start->text();
    endLocate = end->text();
    startDate = dateTime->text();
    hiType = type->currentText();
    //if(JudgeEmpty() == false) return ;
    messageWidget->setColumnCount(9);
    messageWidget->setHorizontalHeaderLabels(QStringList() << tr("发布人")
                << tr("人数") << tr("始发地")<< tr("目的地") << tr("出发日期")
                << tr("活动项目") << tr("状态") << tr("备注") << tr("eventID"));    // 设置列名
//    for(int i = 0; i < 7; i++)
//        messageWidget->setColumnWidth(i, 200);
    messageWidget->setColumnWidth(2, 180);
    messageWidget->setColumnWidth(3, 180);
    messageWidget->setColumnWidth(4, 250);
    messageWidget->setColumnWidth(5, 150);
    messageWidget->setColumnWidth(7, 180);

    messageWidget->setColumnHidden(6,true);
    messageWidget->setColumnHidden(8,true);
    //获得水平方向表头的item对象
    QTableWidgetItem *columnHeaderItem = messageWidget->horizontalHeaderItem(1);
    //columnHeaderItem->setFont(QFont("Helvetica"));  //设置字体
    columnHeaderItem->setBackgroundColor(QColor(0,60,10));  //设置单元格背景颜色
    columnHeaderItem->setTextColor(QColor(200,111,30));     //设置文字颜色

    messageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //按条件进行搜索：始发地，目的地，出发日期，活动项目
    string startString = "NULL";
    if(start->text() != NULL && startLabel->isChecked()) startString = QStringToStdString(start->text());
    string endString = "NULL";
    if(end->text() != NULL && endLabel->isChecked()) endString = QStringToStdString(end->text());
    string timeString = "NULL";
    if(dateTime->text() != NULL && timeLabel->isChecked()) timeString = QStringToStdString(dateTime->text());
    string typeString = "NULL";
    if(type->currentText() != NULL && typeLabel->isChecked()) typeString = QStringToStdString(type->currentText());
    vector<EventStruct>  es = client.getEvent(startString,endString,timeString,typeString);
    vector<EventStruct>::iterator iter2 = es.begin();
    if(es.size() == 0) {
        QMessageBox::information(this, tr(""),
                tr("未搜索到结果！"),
                QMessageBox::tr("确定"));
        messageWidget->clearContents();
        return ;
    }
    messageWidget->setRowCount(es.size());   // 设置结果占的行数
//    if(es.size() <= resultNum) {
        messageWidget->clearContents();
//    }
    resultNum = es.size();
    //for(int i = 0; i < 12; i++)
    for (int i=0;iter2 != es.end() ;++iter2,i++)
    {
        EventStruct ee = *iter2;
        messageWidget->setRowHeight(i,50);
        QTableWidgetItem *item0 = messageWidget->item(i,0); // 发布人
        QTableWidgetItem *item1 = messageWidget->item(i,1); // 人数
        QTableWidgetItem *item2 = messageWidget->item(i,2); // 始发地
        QTableWidgetItem *item3 = messageWidget->item(i,3); // 目的地
        QTableWidgetItem *item4 = messageWidget->item(i,4); // 出发日期
        QTableWidgetItem *item5 = messageWidget->item(i,5); // 活动项目
        QTableWidgetItem *item6 = messageWidget->item(i,6); // 状态
        //QTableWidgetItem *item7 = messageWidget->item(i,7); // 备注
        QTableWidgetItem *item8 = messageWidget->item(i,8); // eventID

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

        //connect(joinBtn, &QPushButton::clicked, this,&MainWindow::iSlot);
        //connect(this, SIGNAL(iSignal(int)), this, SLOT(JoinBtnClicked(int)));
        QSignalMapper *signalmapper1 = new QSignalMapper(this);
        connect(joinBtn, SIGNAL(clicked()), signalmapper1,SLOT(map()));
        signalmapper1->setMapping(joinBtn,ee.EventID);
        connect(signalmapper1,SIGNAL(mapped(int)),this,SLOT(JoinBtnClicked(int)));

        QSignalMapper *signalmapper = new QSignalMapper(this);
        connect(detailBtn, SIGNAL(clicked()), signalmapper,SLOT(map()));
        signalmapper->setMapping(detailBtn,ee.EventID);
        connect(signalmapper,SIGNAL(mapped(int)),this,SLOT(DetailBtnClicked(int)));

        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(StdStringToQString(ee.Publisher));
            item0->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 0, item0);

            item1 = new QTableWidgetItem;
            item1->setText(QString("%1人").arg(ee.PeersNumber));
            item1->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 1, item1);

            item2 = new QTableWidgetItem;
            item2->setText(StdStringToQString(ee.StartSite));
            item2->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 2, item2);

            item3 = new QTableWidgetItem;
            item3->setText(StdStringToQString(ee.EndSite));
            item3->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 3, item3);

            item4 = new QTableWidgetItem;
            item4->setText(StdStringToQString(ee.StartTime));
            item4->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 4, item4);

            item5 = new QTableWidgetItem;
            item5->setText(StdStringToQString(ee.EventType));
            item5->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 5, item5);

            item6 = new QTableWidgetItem;
            item6->setText(StdStringToQString("未加入"));
            item6->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 6, item6);

            //item7 = new QTableWidgetItem;
            messageWidget->setCellWidget(i,7,remark);

            item8 = new QTableWidgetItem;
            item8->setText(QString::number(ee.EventID,10));
            messageWidget->setItem(i, 8, item8);
        }
    }
    messageWidget->show();
    //messageWidget->clearContents();
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

void MainWindow::DetailBtnClicked(int eventID)
{
//    printf("%d\n",eventID);
//    this->hide();
//    QString str = QString::number(eventID,10);
//    QMessageBox::information(this, tr(""),
//            str,
//            QMessageBox::tr("确定"));
    eventIDGlobal = eventID;
    startGlobal = eventID;
    endGlobal = eventID;
    DetailDialog *detailDlg = new DetailDialog;
    detailDlg->show();
}

void MainWindow::JoinBtnClicked(int eventID)
{
//    QString str = QString::number(eventID,10);
//    QMessageBox::information(this, tr(""),
//            str,
//            QMessageBox::tr("确定"));
//    printf("%d\n",eventID);
    QMessageBox mb(QMessageBox::Warning, "","确定要一起嗨？");
    mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    mb.setButtonText (QMessageBox::Ok,QString("确 定"));
    mb.setButtonText (QMessageBox::Cancel,QString("取 消"));
    if(mb.exec() == QMessageBox::Ok)
    {

        if (client.joinEvent(eventID,QStringToStdString(userNameGlobal)))
            QMessageBox::information(this, tr(""),
                    tr("恭喜加入成功！"),
                    QMessageBox::tr("确定"));
        else
        {
            QMessageBox::information(this, tr(""),
                    tr("对不起，你已经加入过这个团队！"),
                    QMessageBox::tr("确定"));
        }
    }
}
