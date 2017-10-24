#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QDateEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGridLayout *mainLayout = new QGridLayout(this);
    QLabel *startLabel = new QLabel(this);
    QLineEdit *start = new QLineEdit(this);
    QLabel *endLabel = new QLabel(this);
    QLineEdit *end = new QLineEdit(this);
    QLabel *timeLabel = new QLabel(this);
    QDateEdit *dateTime = new QDateEdit(this);
    QLabel *typeLabel = new QLabel(this);
    QComboBox *type = new QComboBox(this);

    QPushButton *searchBtn = new QPushButton(this);
    QPushButton *publishBtn = new QPushButton(this);

    //QImage *image = new QImage(this);
    QLabel *avatar = new QLabel(this);
    QLabel *userName = new QLabel(this);

    QTableWidget *messageWidget = new QTableWidget(this);

private slots:
    void search();
    void off();
    void personal();
    void join();
    void PersonalData();
    void on_messageBtn_clicked();
    void on_detailBtn_clicked();
    void on_publishBtn_clicked();
    void on_inviteBtn_clicked();
    bool judge();
};

#endif // MAINWINDOW_H
