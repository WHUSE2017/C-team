#include <QApplication>
#include "logindialog.h"
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include "globalvariable.h"
#include <QProcess>
using namespace std;

HANDLE CreateServerProcess()
{
    HANDLE ret=NULL;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    //创建一个新进程
    if(CreateProcess(
        _T("server.exe"),   //  指向一个NULL结尾的、用来指定可执行模块的宽字节字符串
        NULL, // 命令行字符串
        NULL, //    指向一个SECURITY_ATTRIBUTES结构体，这个结构体决定是否返回的句柄可以被子进程继承。
        NULL, //    如果lpProcessAttributes参数为空（NULL），那么句柄不能被继承。<同上>
        false,//    指示新进程是否从调用进程处继承了句柄。
        CREATE_NO_WINDOW,		//  指定附加的、用来控制优先类和进程的创建的标
                //  CREATE_NEW_CONSOLE  新控制台打开子进程
                //  CREATE_SUSPENDED    子进程创建后挂起，直到调用ResumeThread函数
        NULL, //    指向一个新进程的环境块。如果此参数为空，新进程使用调用进程的环境
        NULL, //    指定子进程的工作路径
        _T(&si), // 决定新进程的主窗体如何显示的STARTUPINFO结构体
        _T(&pi)  // 接收新进程的识别信息的PROCESS_INFORMATION结构体
        ))
    {
        cout << "create process success" << endl;
        ret = pi.hProcess;
        //下面两行关闭句柄，解除本进程和新进程的关系，不然有可能不小心调用TerminateProcess函数关掉子进程
//      CloseHandle(pi.hProcess);
//      CloseHandle(pi.hThread);
    }
    else{
        cout << "failed to create process" << endl;
    }
    Sleep(50);
    return ret;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    HANDLE hProcess = CreateServerProcess();

/**在程序退出的地方调用如下函数关闭server, hProcess设为全局变量***/
    //TerminateProcess(hProcess,0);



    //2.通过QProcess,阻塞调用
//    QProcess::execute("server.exe");
    //3.通过QProcess,非阻塞调用
//    QProcess *pro = new QProcess;
//    pro->start("server.exe");
    client.fisrtConnect();
    LoginDialog loginDlg;
    loginDlg.show();
    return a.exec();
}
