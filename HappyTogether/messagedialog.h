#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QToolBox>

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
    QToolButton *toolBtn1_1;
    QToolButton *toolBtn1_2;
    QToolButton *toolBtn1_3;
    QToolButton *toolBtn1_4;
    QToolButton *toolBtn1_5;
    QToolButton *toolBtn2_1;
    QToolButton *toolBtn2_2;
    QToolButton *toolBtn3_1;
    QToolButton *toolBtn3_2;
};

#endif // MESSAGEDIALOG_H
