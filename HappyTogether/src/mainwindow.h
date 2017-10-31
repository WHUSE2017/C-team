#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QDateEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    //void clicked();
    void iSignal(int b);

protected:
    void MouseDownEvent(QMouseEvent* );
    void MouseUpEvent(QMouseEvent* );
    void MouseMoveEvent(QMouseEvent* );
    void MouseReleaseEvent(QMouseEvent* );
    void iSlot();

private:
    Ui::MainWindow *ui;
    bool isClicked;

    QAction *offAction; //注销
    QAction *dataAction;//个人资料
    QMenu *messageMenu;//消息菜单
    QAction *receiveMessageAction;//收消息
    QAction *sendMessageAction;//发送消息
    //QAction *inviteAction;//邀请用户
    QMenu *helpMenu;    //帮助菜单
    QAction *documentAction;//软件操作帮助文档
    QAction *aboutAction;   //关于软件
    QMenu *skinMenu;    //换肤菜单
    QAction *blackAction;//黑色炫酷
    QAction *whiteAction;   //白色靓丽
    QAction *defaultAction;   //原生态

    //QImage *image = new QImage(this);
    QLabel *avatar = new QLabel(this);  //头像
    QLabel *userName = new QLabel(this);//用户名称
    QGridLayout *mainLayout = new QGridLayout(this);
    QLabel *startLabel = new QLabel(this);
    QLineEdit *start = new QLineEdit(this); //始发地
    QLabel *endLabel = new QLabel(this);
    QLineEdit *end = new QLineEdit(this);   //目的地
    QLabel *timeLabel = new QLabel(this);
    QDateEdit *dateTime = new QDateEdit(this);//出发日期
    QLabel *typeLabel = new QLabel(this);
    QComboBox *type = new QComboBox(this);  //活动性质

    QPushButton *searchBtn = new QPushButton(this); //搜索按钮
    QPushButton *publishBtn = new QPushButton(this);  //发布按钮
    QTableWidget *messageWidget = new QTableWidget(this);

private slots:

    void OffActionClicked();
    void DataActionClicked();
    void ReceiveMessageActionClicked();
    void SendMessageActionClicked();
    //void InviteActionClicked();
    void DocumentActionClicked();
    void AboutActionClicked();
    void BlackActionClicked();
    void WhiteActionClicked();
    void DefaultActionClicked();

    void SearchBtnClicked();
    void PublishBtnClicked();
    void JoinBtnClicked(int eventID);
    void DetailBtnClicked(int eventID);
    bool JudgeEmpty();
    //void UserNameClicked();
};

#endif // MAINWINDOW_H