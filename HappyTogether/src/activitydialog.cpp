#include "activitydialog.h"
#include "ui_activitydialog.h"
#include "globalvariable.h"
#include "Client/UserClient.h"
#include <QSignalMapper>
#include <QMessageBox>
#include "detaildialog.h"

ActivityDialog::ActivityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivityDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("活动记录");
    this->setFont(GetFont());  //这个必须写在样式前面
    this->setStyleSheet(GetStyle());
    this->resize(1000,600);
    mainLayout->addWidget(messageWidget,0,0,4,8);
    search();
}

void ActivityDialog::search()
{
    messageWidget->setColumnCount(6);

    messageWidget->setHorizontalHeaderLabels(QStringList() << tr("发布人") << tr("人数") << tr("始发地")<< tr("目的地") << tr("出发日期") << tr("操作"));    // 设置列名
    messageWidget->setColumnWidth(1, 80);
    messageWidget->setColumnWidth(2, 180);
    messageWidget->setColumnWidth(3, 180);
    messageWidget->setColumnWidth(4, 160);
    messageWidget->setColumnWidth(5, 250);
    messageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    vector<EventStruct> act1 = client.getEventByConditions(QStringToStdString(userNameGlobal),"NULL", 1);
    vector<EventStruct> act2 = client.getEventByConditions("NULL", QStringToStdString(userNameGlobal),1);
    int num = act1.size() + act2.size();
    messageWidget->setRowCount(act2.size());   // 设置题目占的行数
    vector<EventStruct>::iterator iter3 = act2.begin();
    for (int i = 0;iter3 != act2.end();++iter3,i++)
    {
        EventStruct str_name = *iter3;  // *iter就是vector的每个元素
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
        joinBtn->setText("出行成功");
        joinBtn->setStyleSheet("font-size:18px;");
        layout->addWidget(joinBtn,0,0,1,1);
        QPushButton *exitBtn = new QPushButton(this);
        exitBtn->setText("退出");
        layout->addWidget(exitBtn,0,1,1,1);
        QPushButton *detailBtn = new QPushButton(this);
        detailBtn->setText("详情");
        layout->addWidget(detailBtn,0,2,1,1);

        QSignalMapper *signalmapper1 = new QSignalMapper(this);
        connect(exitBtn, SIGNAL(clicked()), signalmapper1,SLOT(map()));
        signalmapper1->setMapping(exitBtn,str_name.EventID);
        connect(signalmapper1,SIGNAL(mapped(int)),this,SLOT(ExitBtnClicked(int)));

        QSignalMapper *signalmapper2 = new QSignalMapper(this);
        connect(joinBtn, SIGNAL(clicked()), signalmapper2,SLOT(map()));
        signalmapper2->setMapping(joinBtn,str_name.EventID);
        connect(signalmapper2,SIGNAL(mapped(int)),this,SLOT(JoinBtnClicked(int)));

        QSignalMapper *signalmapper3 = new QSignalMapper(this);
        connect(detailBtn, SIGNAL(clicked()), signalmapper3,SLOT(map()));
        signalmapper3->setMapping(detailBtn,str_name.EventID);
        connect(signalmapper3,SIGNAL(mapped(int)),this,SLOT(DetailBtnClicked(int)));

        remark->setLayout(layout);

        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(StdStringToQString(str_name.Publisher));
            item0->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 0, item0);

            item1 = new QTableWidgetItem;
            item1->setText(QString::number(str_name.PeersNumber,10));
            item1->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 1, item1);

            item2 = new QTableWidgetItem;
            item2->setText(StdStringToQString(str_name.StartSite));
            item2->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 2, item2);

            item3 = new QTableWidgetItem;
            item3->setText(StdStringToQString(str_name.EndSite));
            item3->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 3, item3);

            item4 = new QTableWidgetItem;
            item4->setText(StdStringToQString(str_name.StartTime));
            item4->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 4, item4);

            item5 = new QTableWidgetItem;
            messageWidget->setCellWidget(i,5,remark);
        }
    }
    /*
    iter3 = act2.begin();
    for (int i = act1.size();iter3 != act2.end();++iter3,i++)
    {
        EventStruct str_name = *iter3;  // *iter就是vector的每个元素
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
        joinBtn->setText("出行成功");
        joinBtn->setStyleSheet("font-size:18px;");
        layout->addWidget(joinBtn,0,0,1,1);
        QPushButton *exitBtn = new QPushButton(this);
        exitBtn->setText("退出");
        layout->addWidget(exitBtn,0,1,1,1);
        QPushButton *detailBtn = new QPushButton(this);
        detailBtn->setText("详情");
        layout->addWidget(detailBtn,0,2,1,1);

        QSignalMapper *signalmapper1 = new QSignalMapper(this);
        connect(exitBtn, SIGNAL(clicked()), signalmapper1,SLOT(map()));
        signalmapper1->setMapping(exitBtn,str_name.EventID);
        connect(signalmapper1,SIGNAL(mapped(int)),this,SLOT(ExitBtnClicked(int)));

        QSignalMapper *signalmapper2 = new QSignalMapper(this);
        connect(joinBtn, SIGNAL(clicked()), signalmapper2,SLOT(map()));
        signalmapper2->setMapping(joinBtn,str_name.EventID);
        connect(signalmapper2,SIGNAL(mapped(int)),this,SLOT(JoinBtnClicked(int)));

        QSignalMapper *signalmapper3 = new QSignalMapper(this);
        connect(detailBtn, SIGNAL(clicked()), signalmapper3,SLOT(map()));
        signalmapper3->setMapping(detailBtn,str_name.EventID);
        connect(signalmapper3,SIGNAL(mapped(int)),this,SLOT(DetailBtnClicked(int)));

        remark->setLayout(layout);

        if(item0) {
            item0->setFlags((item0->flags()&(~Qt::ItemIsEditable)));
        }
        else {
            item0 = new QTableWidgetItem;
            item0->setText(StdStringToQString(str_name.Publisher));
            item0->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 0, item0);

            item1 = new QTableWidgetItem;
            item1->setText(QString::number(str_name.PeersNumber,10));
            item1->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 1, item1);

            item2 = new QTableWidgetItem;
            item2->setText(StdStringToQString(str_name.StartSite));
            item2->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 2, item2);

            item3 = new QTableWidgetItem;
            item3->setText(StdStringToQString(str_name.EndSite));
            item3->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 3, item3);

            item4 = new QTableWidgetItem;
            item4->setText(StdStringToQString(str_name.StartTime));
            item4->setTextAlignment(Qt::AlignCenter);
            messageWidget->setItem(i, 4, item4);

            item5 = new QTableWidgetItem;
            messageWidget->setCellWidget(i,5,remark);
        }
    }*/
    messageWidget->show();
}

/*
 * bool ExitEvent(int EventID,string username);
    退出event

bool SetEventState(int EventID,int state);
    设置event状态，state最好为正数（如1为进行中，2为完成，3为取消）

vector<EventStruct> getEventByConditions(string publisher,string participant,int state);
    publisher为发布者，participant为加入者(即查询参加的event)，publisher和 participant只能有一个为"NULL",state不能为NULL，
    */

void ActivityDialog::JoinBtnClicked(int eventID)
{
    if(client.SetEventState(eventID, 2)) {
        search();
        QMessageBox::information(this, tr(""),
                    tr("出行成功！"),
                    QMessageBox::tr("确定"));
    }
    else {

        QMessageBox::information(this, tr(""),
                    tr("出行不成功！"),
                    QMessageBox::tr("确定"));
    }
}

void ActivityDialog::DetailBtnClicked(int eventID)
{
    eventIDGlobal = eventID;
    startGlobal = eventID;
    endGlobal = eventID;
    DetailDialog *detailDlg = new DetailDialog;
    detailDlg->show();
}

void ActivityDialog::ExitBtnClicked(int eventID)
{
    if(client.ExitEvent(eventID, QStringToStdString(userNameGlobal))) {
        client.SetEventState(eventID, 3);
        search();
        QMessageBox::information(this, tr(""),
                    tr("退出成功！"),
                    QMessageBox::tr("确定"));
    }
    else {
        QMessageBox::information(this, tr(""),
                    tr("退出不成功！"),
                    QMessageBox::tr("确定"));
    }
}

ActivityDialog::~ActivityDialog()
{
    delete ui;
}
