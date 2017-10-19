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
    QLineEdit *time = new QLineEdit(this);
    QLabel *typeLabel = new QLabel(this);
    QComboBox *type = new QComboBox(this);

    QPushButton *searchBtn = new QPushButton(this);
    QPushButton *publishBtn = new QPushButton(this);

    QLabel *userName = new QLabel(this);

    QTableWidget *messageWidget = new QTableWidget(this);

private slots:
    void search();
    void off();
    void personal();
    void join();
};

#endif // MAINWINDOW_H
