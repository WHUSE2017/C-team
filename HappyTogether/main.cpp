#include <QApplication>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog loginDlg;
    loginDlg.show();
    return a.exec();
}
