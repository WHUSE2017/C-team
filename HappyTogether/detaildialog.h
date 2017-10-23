#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QTableWidget>

namespace Ui {
class DetailDialog;
}

class DetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetailDialog(QWidget *parent = 0);
    ~DetailDialog();

private:
    Ui::DetailDialog *ui;
    QGridLayout *mainLayout = new QGridLayout(this);
    QLabel *startLabel = new QLabel(this);
    QLineEdit *start = new QLineEdit(this);
    QLabel *endLabel = new QLabel(this);
    QLineEdit *end = new QLineEdit(this);
    QLabel *timeLabel = new QLabel(this);
    QLineEdit *time = new QLineEdit(this);
    QLabel *typeLabel = new QLabel(this);
    QComboBox *type = new QComboBox(this);

    //QImage *image = new QImage(this);
    QLabel *avatar = new QLabel(this);
    QLabel *userName = new QLabel(this);

    QTableWidget *messageWidget = new QTableWidget(this);

private slots:
    void search();
};

#endif // DETAILDIALOG_H
