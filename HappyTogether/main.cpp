#include <QApplication>
#include "logindialog.h"
#include <windows.h>
#include "globalvariable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    LoginDialog loginDlg;
    loginDlg.show();
    return a.exec();
}
