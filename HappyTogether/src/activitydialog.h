#ifndef ACTIVITYDIALOG_H
#define ACTIVITYDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QTableWidget>

namespace Ui {
class ActivityDialog;
}

class ActivityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActivityDialog(QWidget *parent = 0);
    ~ActivityDialog();

private:
    Ui::ActivityDialog *ui;
    QTableWidget *messageWidget = new QTableWidget(this);
    QGridLayout *mainLayout = new QGridLayout(this);
    void search();
};

#endif // ACTIVITYDIALOG_H
