#ifndef SENDMESSAGEDIALOG_H
#define SENDMESSAGEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>

namespace Ui {
class SendMessageDialog;
}

class SendMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendMessageDialog(QWidget *parent = 0);
    ~SendMessageDialog();

private:
    Ui::SendMessageDialog *ui;

    QLabel *receiverLabel = new QLabel(this);
    QLineEdit *receiver = new QLineEdit(this);  //收消息的用户名称
    QPushButton *sendBtn = new QPushButton(this);//发送按钮
    QGridLayout *sendMessageLayout = new QGridLayout(this);
    QTextEdit *content = new QTextEdit(this);

private slots:
    void SendBtnClicked();
};

#endif // SENDMESSAGEDIALOG_H
