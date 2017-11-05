#include "activitydialog.h"
#include "ui_activitydialog.h"
#include "globalvariable.h"
#include <QSignalMapper>

ActivityDialog::ActivityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivityDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("活动记录");
    this->setFont(GetFont());  //这个必须写在样式前面
    this->setStyleSheet(GetStyle());
    this->resize(800,600);
    mainLayout->addWidget(messageWidget,0,0,4,8);
    search();
}

void ActivityDialog::search()
{
    messageWidget->setColumnCount(6);

    messageWidget->setHorizontalHeaderLabels(QStringList() << tr("发布人") << tr("人数") << tr("始发地")<< tr("目的地") << tr("出发日期") << tr("操作"));    // 设置列名
    messageWidget->setColumnWidth(1, 80);
    messageWidget->setColumnWidth(2, 120);
    messageWidget->setColumnWidth(4, 160);
    messageWidget->setColumnWidth(5, 160);
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
        joinBtn->setText("已加入");
        layout->addWidget(joinBtn,0,0,1,1);
        QPushButton *exitBtn = new QPushButton(this);
        exitBtn->setText("退出");
        layout->addWidget(exitBtn,0,1,1,1);

        QSignalMapper *signalmapper1 = new QSignalMapper(this);
        connect(exitBtn, SIGNAL(clicked()), signalmapper1,SLOT(map()));
        signalmapper1->setMapping(exitBtn,23);
        connect(signalmapper1,SIGNAL(mapped(int)),this,SLOT(ExitBtnClicked(int)));

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

void ActivityDialog::ExitBtnClicked(int eventID)
{

}

ActivityDialog::~ActivityDialog()
{
    delete ui;
}
