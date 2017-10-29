#include <QApplication>
#include "logindialog.h"
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    //WinExec("./server/x64/Debug/server.exe",SW_SHOWMAXIMIZED);
    LoginDialog loginDlg;
    loginDlg.show();
    return a.exec();
}
