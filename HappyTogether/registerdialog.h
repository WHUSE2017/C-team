#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>

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
    QLineEdit *userName = new QLineEdit(this);
    QLineEdit *userPwd = new QLineEdit(this);
    QLineEdit *userPwd2 = new QLineEdit(this);
    QLabel *sexLabel = new QLabel(this);
    QLabel *emailLabel = new QLabel(this);
    QLabel *phoneLabel = new QLabel(this);
    QLineEdit *sex = new QLineEdit(this);
    QLineEdit *email = new QLineEdit(this);
    QLineEdit *phone = new QLineEdit(this);
    QLabel *selfTagLabel = new QLabel(this);
    QWidget *tag = new QWidget(this);

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

    QPushButton *confirmBtn = new QPushButton(this);
    QPushButton *backBtn = new QPushButton(this);
    QGridLayout *registerLayout = new QGridLayout(this);

private slots:
    void on_confirmBtn_clicked();
    void on_backBtn_clicked();
    void OpenImage();
};
#endif // REGISTERDIALOG_H
