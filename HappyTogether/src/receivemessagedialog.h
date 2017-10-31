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
class ReceiveMessageDialog;
}

class ReceiveMessageDialog : public QToolBox
{
    Q_OBJECT

public:
    explicit ReceiveMessageDialog(QWidget *parent = 0);
    ~ReceiveMessageDialog();

private:
    Ui::ReceiveMessageDialog *ui;
    QLabel *warning = new QLabel(this);
    QLabel *content = new QLabel(this);
    QGroupBox *groupBox = new QGroupBox(this);
    QVBoxLayout *messageLayout = new QVBoxLayout(this);
};

#endif // MESSAGEDIALOG_H
