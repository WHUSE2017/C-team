#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QToolBox>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class MessageDialog;
}

class MessageDialog : public QToolBox
{
    Q_OBJECT

public:
    explicit MessageDialog(QWidget *parent = 0);
    ~MessageDialog();

private:
    Ui::MessageDialog *ui;

    int messageNum;
    QString sender[3] = {"张三","李四","王五"};
    QString sendTime;
    QLabel *content = new QLabel(this);
    QGroupBox *groupBox = new QGroupBox(this);
    QVBoxLayout *messageLayout = new QVBoxLayout(this);
};

#endif // MESSAGEDIALOG_H
