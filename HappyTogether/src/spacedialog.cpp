#include "spacedialog.h"
#include "ui_spacedialog.h"

SpaceDialog::SpaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpaceDialog)
{
    ui->setupUi(this);
}

SpaceDialog::~SpaceDialog()
{
    delete ui;
}
