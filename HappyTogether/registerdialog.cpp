#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include "logindialog.h"
#include <QFileDialog>
#include "globalvariable.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    QFont fontStyle = GetFont();
    this->setFont(fontStyle);
    this->setStyleSheet(GetStyle());
    this->setWindowTitle("注册");

    nameLabel->setText("用户名：");
    registerLayout->addWidget(nameLabel,0,0,1,1);
    userName->setPlaceholderText("请输入用户名");
    registerLayout->addWidget(userName,0,1,1,2);

    pwdLabel->setText("密码：");
    registerLayout->addWidget(pwdLabel,1,0,1,1);
    userPwd->setPlaceholderText("请输入密码");
    registerLayout->addWidget(userPwd,1,1,1,2);

    pwdLabel2->setText("再次密码：");
    registerLayout->addWidget(pwdLabel2,2,0,1,1);
    userPwd2->setPlaceholderText("请再次输入密码");
    registerLayout->addWidget(userPwd2,2,1,1,2);

    sexLabel->setText("性别：");
    registerLayout->addWidget(sexLabel,3,0,1,1);
    sex->setPlaceholderText("请输入性别");
    registerLayout->addWidget(sex,3,1,1,2);

    phoneLabel->setText("电话：");
    registerLayout->addWidget(phoneLabel,4,0,1,1);
    phone->setPlaceholderText("请输入电话");
    registerLayout->addWidget(phone,4,1,1,2);

    emailLabel->setText("邮箱：");
    registerLayout->addWidget(emailLabel,5,0,1,1);
    email->setPlaceholderText("请输入有效的邮箱");
    registerLayout->addWidget(email,5,1,1,2);
    QQLabel->setText("QQ：");
    registerLayout->addWidget(QQLabel,6,0,1,1);
    QQ->setPlaceholderText("请输入QQ号");
    registerLayout->addWidget(QQ,6,1,1,2);

    studentIdLabel->setText("学号：");
    registerLayout->addWidget(studentIdLabel,7,0,1,1);
    studentId->setPlaceholderText("请输入有效的学号");
    registerLayout->addWidget(studentId,7,1,1,2);
    universityLabel->setText("学校：");
    registerLayout->addWidget(universityLabel,8,0,1,1);
    university->setPlaceholderText("请输入学校");
    registerLayout->addWidget(university,8,1,1,2);
    locateAreaLabel->setText("地区：");
    registerLayout->addWidget(locateAreaLabel,9,0,1,1);
    locateArea->setPlaceholderText("请输入地区");
    registerLayout->addWidget(locateArea,9,1,1,2);
    imageLabel->setText("头像：");
    registerLayout->addWidget(imageLabel,10,0,1,1);
    imageBtn->setText("上传");
    registerLayout->addWidget(imageBtn,10,1,1,2);



    selfTagLabel->setText("Tag：");
    registerLayout->addWidget(selfTagLabel,11,0,1,1);

    QGridLayout *tagLayout = new QGridLayout(this);
    // 创建QPushButton控件
    QPushButton *btn1 = new QPushButton(this);
    btn1->setText("开朗");
    tagLayout->addWidget(btn1,0,0,1,1);

    QPushButton *btn2 = new QPushButton(this);
    btn2->setText("内向");
    tagLayout->addWidget(btn2,0,1,1,1);

    QPushButton *btn3 = new QPushButton(this);
    btn3->setText("爱笑");
    tagLayout->addWidget(btn3,1,0,1,1);
    QPushButton *btn4 = new QPushButton(this);
    btn4->setText("漂亮");
    tagLayout->addWidget(btn4,1,1,1,1);

    tag->setLayout(tagLayout);
    registerLayout->addWidget(tag,11,1,2,2);

    backBtn->setText("返回");
    registerLayout->addWidget(backBtn,13,0,1,1);
    confirmBtn->setText("确认");
    registerLayout->addWidget(confirmBtn,13,2,1,1);
    this->setLayout(registerLayout);
    connect(confirmBtn, &QPushButton::clicked, this, &RegisterDialog::ConfirmBtnClicked);
    connect(backBtn, &QPushButton::clicked, this, &RegisterDialog::BackBtnClicked);
    connect(imageBtn, &QPushButton::clicked, this, &RegisterDialog::OpenImage);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::ConfirmBtnClicked()
{
    QMessageBox::information(this, tr("Welcome"), tr("恭喜注册成功！"), QMessageBox::tr("确定"));
}

void RegisterDialog::BackBtnClicked()
{
    LoginDialog *loginDlg = new LoginDialog;
    this->hide();
    loginDlg->show();
}

void RegisterDialog::OpenImage()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this, tr("选择图像"), "", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filename.isEmpty())
    {
        return;
    }
    else {
        QImage* img=new QImage;
        if(! ( img->load(filename) ) ){ //加载图像  {
            QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
            delete img;
            return;
        }
        imageBtn->setText(filename.section('/',-1));
            //mainLayout->addWidget(img,0,0,1,1);
   }
}
