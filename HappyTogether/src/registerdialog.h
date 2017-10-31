#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

private:
    Ui::RegisterDialog *ui;
    QLabel *nameLabel = new QLabel(this);
    QLabel *pwdLabel = new QLabel(this);
    QLabel *pwdLabel2 = new QLabel(this);
    QLineEdit *userName = new QLineEdit(this);  //用户名称
    QLineEdit *userPwd = new QLineEdit(this);   //登录密码
    QLineEdit *userPwd2 = new QLineEdit(this);  //再次确认输入密码
    QLabel *sexLabel = new QLabel(this);
    QLabel *emailLabel = new QLabel(this);
    QLabel *phoneLabel = new QLabel(this);
//    QLineEdit *sex = new QLineEdit(this);   //性别
    QComboBox *sexType = new QComboBox(this);
    QLineEdit *phone = new QLineEdit(this); //电话
    QLineEdit *email = new QLineEdit(this); //邮箱
    QLabel *QQLabel = new QLabel(this);
    QLineEdit *QQ = new QLineEdit(this);    //QQ号
    QLabel *studentIdLabel = new QLabel(this);
    QLineEdit *studentId = new QLineEdit(this); //学号
    QLabel *universityLabel = new QLabel(this);
    QLineEdit *university = new QLineEdit(this);    //学校
    QLabel *locateAreaLabel = new QLabel(this);
    QLineEdit *locateArea = new QLineEdit(this);    //地区
    QLabel *imageLabel = new QLabel(this);
    QPushButton *imageBtn = new QPushButton(this);  //头像上传
//    QLabel *selfTagLabel = new QLabel(this);
//    QWidget *tag = new QWidget(this);       //自我标签
    QLabel *signatureLabel = new QLabel(this); //个性签名
    QTextEdit *signature = new QTextEdit(this);

    QPushButton *confirmBtn = new QPushButton(this);    //确认
    QPushButton *backBtn = new QPushButton(this);   //返回
    QGridLayout *registerLayout = new QGridLayout(this);    //布局

private slots:
    void ConfirmBtnClicked();
    void BackBtnClicked();
    void OpenImage();
    bool JudgeEmpty();
};
#endif // REGISTERDIALOG_H
