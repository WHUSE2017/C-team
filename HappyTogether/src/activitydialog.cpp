#include "activitydialog.h"
#include "ui_activitydialog.h"
#include "globalvariable.h"

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
    messageWidget->setRowCount(12);   // 设置题目占的行数
    messageWidget->setHorizontalHeaderLabels(QStringList() << tr("用户名") << tr("性别") << tr("学校")<< tr("游玩次数") << tr("电话") << tr("tag"));    // 设置列名
    messageWidget->setColumnWidth(1, 80);
    messageWidget->setColumnWidth(2, 120);
    messageWidget->setColumnWidth(4, 160);
    messageWidget->setColumnWidth(5, 160);
    messageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    vector<string> ps =client.getParticipants(eventIDGlobal);
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
        QPushButton *detailBtn = new QPushButton(this);
        detailBtn->setText("退出");
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

ActivityDialog::~ActivityDialog()
{
    delete ui;
}
