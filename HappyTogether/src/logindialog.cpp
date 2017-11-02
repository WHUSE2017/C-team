#include <QMessageBox>
#include "logindialog.h"
#include "ui_logindialog.h"

#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <cstdlib>
#include <time.h>
#include "globalvariable.h"
#include <QFontDatabase>
#include <QTextCodec>
#include "client/UserClient.h"
#include <QDesktopWidget>
#include "iniparser.h"
#include "retrievepwddialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::ForeignWindow);
//    QFont font;
//    font.setPointSize(20);
//    font.setFamily(("SentyTEA 新蒂下午茶体"));
    //中文支持
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //int font = QFontDatabase::addApplicationFont("./fonts/HiraginoSansGB-W3-Alphabetic.ttf");
    QFont fontStyle = GetFont();
    this->setFont(fontStyle);
    this->setWindowTitle("登录");
    this->setStyleSheet(GetStyle());

    CMyINI *p = new CMyINI();
    p->ReadINI("conf.ini");
 //    cout <<endl<< "原始INI文件的内容：" << endl;
 //    p->Travel();
 //    p->SetValue("setting", "ImageLenth", "1280");
 //    cout << endl << "增加节点之后的内容：" << endl;
 //    p->Travel();
//                cout << "\n修改节点之后的内容：" << endl;
    if(p->GetValue("Flag","flag") == "1")
    {
        userName->setText(StdStringToQString(p->GetValue("User","userName")));
        userPwd->setText(StdStringToQString(p->GetValue("User","userPassword")));
        rememberPwd->setChecked(true);
    }
    else
    {
        userName->setPlaceholderText("请输入用户名");
        userPwd->setPlaceholderText("请输入密码");
//        rememberPwd->setChecked(true);
//        rememberPwd->setCheckState(Qt::Checked);
    }

    nameLabel->setText("用户名:");
    loginLayout->addWidget(nameLabel,0,0,1,1);

    loginLayout->addWidget(userName,0,1,1,2);


    pwdLabel->setText("密  码:");
    loginLayout->addWidget(pwdLabel,1,0,1,1);

    userPwd->setEchoMode(QLineEdit::Password);
    loginLayout->addWidget(userPwd,1,1,1,2);

    verifyLabel->setText("验证码:");
    loginLayout->addWidget(verifyLabel,2,0,1,1);
    verifyCode->setPlaceholderText("请输入验证码");
    loginLayout->addWidget(verifyCode,2,1,1,1);

    srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
    verifyNumber = "";
    for(int i = 0; i < 4; i++) {
        int temp = rand()%10;
        verifyNumber+=QString::number(temp,10);
    }
    verifyBtn->setText(verifyNumber);
    verifyBtn->setMinimumWidth(120);
    verifyBtn->setFocusPolicy(Qt::NoFocus);
    loginLayout->addWidget(verifyBtn,2,2,1,1);

    retrievePwd->setText("找回密码");
    retrievePwd->setStyleSheet("background-color:transparent;font-size: 20px;color: rgb(0, 0, 0);font-family:'./fonts/方正宋刻本秀楷简体.TTF';");
    loginLayout->addWidget(retrievePwd,3,0,1,1);
    rememberPwd->setText("记住密码");
    loginLayout->addWidget(rememberPwd,3,2,1,1);

    registerBtn->setText("注册");
    loginLayout->addWidget(registerBtn,4,0,1,1);
    loginBtn->setText("登录");
    loginLayout->addWidget(loginBtn,4,2,1,1);
    this->setLayout(loginLayout);
    connect(loginBtn, &QPushButton::clicked, this, &LoginDialog::LoginBtnClicked);
    connect(registerBtn, &QPushButton::clicked, this, &LoginDialog::RegisterBtnClicked);
    //connect(verifyCode, SIGNAL(clicked()), this, SLOT(on_verifyCodeBtn_clicked()));
    connect(verifyBtn, &QPushButton::clicked, this, &LoginDialog::VerifyBtnClicked);
    connect(retrievePwd, &QPushButton::clicked, this, &LoginDialog::RetrievePwdClicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::RetrievePwdClicked()
{
    RetrievePwdDialog *dlg = new RetrievePwdDialog;
    dlg->show();
}

void LoginDialog::VerifyBtnClicked()
{
    srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
    verifyNumber = "";
    for(int i = 0; i < 4; i++) {
        int temp = rand()%10;
        verifyNumber+=QString::number(temp,10);
    }
    verifyBtn->setText(verifyNumber);
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *evt)
{
    Q_UNUSED(evt);
    emit clicked(this);
}

void LoginDialog::LoginBtnClicked()
{
    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框

    if(userName->text() == NULL) {
        QMessageBox::warning(this, tr("警告！"),
                    tr("用户名不能为空"),
                    QMessageBox::tr("确定"));
        return ;
    }

    if(userPwd->text() == NULL) {
        QMessageBox::warning(this, tr("警告！"),
                    tr("密码不能为空"),
                    QMessageBox::tr("确定"));
        return ;
    }
    if(verifyCode->text() == verifyNumber)
    {

        if (client.Login((char*)QStringToStdString(userName->text().trimmed()).data(),
                    (char*)QStringToStdString(userPwd->text().trimmed()).data()))
        {
           userNameGlobal = userName->text();

           CMyINI *p = new CMyINI();
           p->ReadINI("conf.ini");
           if(rememberPwd->isChecked()) {
//                printf("1%s\n\n",rememberPwd->isChecked());
//                printf("2%s\n\n",rememberPwd->checkState());
            //    cout <<endl<< "原始INI文件的内容：" << endl;
            //    p->Travel();
            //    p->SetValue("setting", "ImageLenth", "1280");
            //    cout << endl << "增加节点之后的内容：" << endl;
            //    p->Travel();
//                cout << "\n修改节点之后的内容：" << endl;
                p->SetValue("User", "userName", QStringToStdString(userName->text().trimmed()));
                p->SetValue("User", "userPassword", QStringToStdString(userPwd->text().trimmed()));
                p->SetValue("Flag", "flag", "1");
//                p->Travel();
                p->WriteINI("conf.ini");
           }
           else
           {
//               printf("3%s\n\n",rememberPwd->isChecked());
//                printf("4%s\n\n",rememberPwd->checkState());
               p->SetValue("User", "userName", QStringToStdString(userName->text().trimmed()));
               p->SetValue("User", "userPassword", QStringToStdString(userPwd->text().trimmed()));
               p->SetValue("Flag", "flag", "0");
               p->WriteINI("conf.ini");
           }
           this->hide();
           MainWindow *w = new MainWindow;
           w->show();
           w->move((this->geometry().center() - this->rect().center())/2);
           //w->move((this->geometry().width() - this->rect().width())/2,(this->geometry().height() - this->rect().height())/2);
           //w->move(QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2;
        }
        else
        {
            QMessageBox::warning(this, tr("警告！"),
                        tr("用户名或密码错误！"),
                        QMessageBox::tr("确定"));
            // 清空内容并定位光标
            userName->clear();
            userPwd->clear();
            userName->setFocus();
        }
    }
    else
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("验证码错误！"),
                    QMessageBox::tr("确定"));
    }
}

void LoginDialog::RegisterBtnClicked()
{
    this->hide();
    registerDlg->show();
}
