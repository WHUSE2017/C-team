#ifndef PERSONALDATADIALOG_H
#define PERSONALDATADIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>


namespace Ui {
class PersonalDataDialog;
}

class PersonalDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalDataDialog(QWidget *parent = 0);
    ~PersonalDataDialog();

private:
    Ui::PersonalDataDialog *ui;
    QLabel *nameLabel = new QLabel(this);
    QLabel *pwdLabel = new QLabel(this);
    QLabel *pwdLabel2 = new QLabel(this);
    QLabel *userName = new QLabel(this);
    QLineEdit *userPwd = new QLineEdit(this);
    QLineEdit *userPwd2 = new QLineEdit(this);
    QLabel *sexLabel = new QLabel(this);
    QLabel *emailLabel = new QLabel(this);
    QLabel *phoneLabel = new QLabel(this);
    QLineEdit *email = new QLineEdit(this);
    QLineEdit *phone = new QLineEdit(this);
    //    QLabel *selfTagLabel = new QLabel(this);
    //    QWidget *tag = new QWidget(this);       //自我标签
        QLabel *signatureLabel = new QLabel(this); //个性签名
        QTextEdit *signature = new QTextEdit(this);

    QLabel *studentIdLabel = new QLabel(this);
    QLineEdit *studentId = new QLineEdit(this);
    QLabel *QQLabel = new QLabel(this);
    QLineEdit *QQ = new QLineEdit(this);
    QLabel *imageLabel = new QLabel(this);
    QPushButton *imageBtn = new QPushButton(this);
    QLabel *universityLabel = new QLabel(this);
    QLineEdit *university = new QLineEdit(this);
    QLabel *locateAreaLabel = new QLabel(this);
    QLineEdit *locateArea = new QLineEdit(this);
    QComboBox *sexType = new QComboBox(this);
    QLabel *playTimeLabel = new QLabel(this);
    QLabel *playTime = new QLabel(this);

    QPushButton *confirmBtn = new QPushButton(this);    //确认
    QPushButton *changeBtn = new QPushButton(this);     //修改资料
    QGridLayout *personalDataLayout = new QGridLayout(this);

private slots:
    void on_confirmBtn_clicked();
    void on_changeBtn_clicked();
    void OpenImage();
};

#endif // PERSONALDATADIALOG_H
