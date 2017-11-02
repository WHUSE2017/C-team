#ifndef RETRIEVEPWDDIALOG_H
#define RETRIEVEPWDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>

namespace Ui {
class RetrievePwdDialog;
}

class RetrievePwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RetrievePwdDialog(QWidget *parent = 0);
    ~RetrievePwdDialog();

private:
    Ui::RetrievePwdDialog *ui;
    QLabel *security = new QLabel(this);
    QLabel *securityQuestion = new QLabel(this);    //密保问题
    QLineEdit *securityAnswer = new QLineEdit(this);
    QPushButton *queryBtn = new QPushButton(this);
    QGridLayout *retrievePwdLayout = new QGridLayout(this);

private slots:
    void QueryBtnClicked();
};

#endif // RETRIEVEPWDDIALOG_H
