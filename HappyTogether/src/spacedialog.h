#ifndef SPACEDIALOG_H
#define SPACEDIALOG_H

#include <QDialog>

namespace Ui {
class SpaceDialog;
}

class SpaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpaceDialog(QWidget *parent = 0);
    ~SpaceDialog();

private:
    Ui::SpaceDialog *ui;
};

#endif // SPACEDIALOG_H
