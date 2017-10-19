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
    QLabel *introductionLabel = new QLabel(this);
    QTextEdit *introduction = new QTextEdit(this);

    QPushButton *confirmBtn = new QPushButton(this);
    QPushButton *backBtn = new QPushButton(this);
    QGridLayout *registerLayout = new QGridLayout(this);

private slots:
    void on_confirmBtn_clicked();
    void on_backBtn_clicked();
};
#endif // REGISTERDIALOG_H
