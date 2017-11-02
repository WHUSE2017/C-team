#include "personaldatadialog.h"
#include "ui_personaldatadialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include "globalvariable.h"

PersonalDataDialog::PersonalDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalDataDialog)
{
    ui->setupUi(this);
    QFont fontStyle = GetFont();
    this->setFont(fontStyle);
    this->setStyleSheet(GetStyle());
    this->setWindowTitle("个人资料");

    /*获取某个人的信息*/
     struct userStruct uinfo = client.getUserInfo((char*)QStringToStdString(userNameGlobal).data());//如果用户存在
     if(uinfo.UserName!="") {
         //cout<<uinfo.UserName<<" "<<uinfo.Email<<" "<<uinfo.Phone<<" "<<uinfo.UserQQ<<endl;

        nameLabel->setText("用户名：");
        personalDataLayout->addWidget(nameLabel,0,0,1,1);
        userName->setText(StdStringToQString(uinfo.UserName));
        //userName->setEnabled(false);
        personalDataLayout->addWidget(userName,0,1,1,2);

        pwdLabel->setText("原密码(*)：");
        personalDataLayout->addWidget(pwdLabel,1,0,1,1);
        //userPwd->setText(QString::fromStdString(uinfo.PassWord));
        userPwd->setPlaceholderText("修改资料请输入原密码");
        userPwd->setEchoMode(QLineEdit::Password);
        personalDataLayout->addWidget(userPwd,1,1,1,2);

        pwdLabel2->setText("修改密码(可选):");
        personalDataLayout->addWidget(pwdLabel2,2,0,1,1);
        userPwd2->setPlaceholderText("请输入新密码");
        userPwd2->setEchoMode(QLineEdit::Password);
        personalDataLayout->addWidget(userPwd2,2,1,1,2);

        sexLabel->setText("性别：");
        personalDataLayout->addWidget(sexLabel,3,0,1,1);
        sexType->addItem("男");
        sexType->addItem("女");
        if(StdStringToQString(uinfo.Gender) == "女")
            sexType->setCurrentIndex(1);
        personalDataLayout->addWidget(sexType,3,1,1,2);

        phoneLabel->setText("电话：");
        personalDataLayout->addWidget(phoneLabel,4,0,1,1);
        phone->setText(StdStringToQString(uinfo.Phone));
        personalDataLayout->addWidget(phone,4,1,1,2);

        emailLabel->setText("邮箱：");
        personalDataLayout->addWidget(emailLabel,5,0,1,1);
        email->setText(StdStringToQString(uinfo.Email));
        personalDataLayout->addWidget(email,5,1,1,2);
        QQLabel->setText("QQ：");
        personalDataLayout->addWidget(QQLabel,6,0,1,1);
        QQ->setText(StdStringToQString(uinfo.UserQQ));
        personalDataLayout->addWidget(QQ,6,1,1,2);

        studentIdLabel->setText("学号：");
        personalDataLayout->addWidget(studentIdLabel,7,0,1,1);
        studentId->setText(StdStringToQString(uinfo.StudentId));
        personalDataLayout->addWidget(studentId,7,1,1,2);
        universityLabel->setText("学校：");
        personalDataLayout->addWidget(universityLabel,8,0,1,1);
        university->setText(StdStringToQString(uinfo.University));
        personalDataLayout->addWidget(university,8,1,1,2);
        locateAreaLabel->setText("地区：");
        personalDataLayout->addWidget(locateAreaLabel,9,0,1,1);
        locateArea->setText(StdStringToQString(uinfo.LocateArea));
        personalDataLayout->addWidget(locateArea,9,1,1,2);
        imageLabel->setText("头像：");
        personalDataLayout->addWidget(imageLabel,10,0,1,1);
        imageBtn->setText("上传");
        personalDataLayout->addWidget(imageBtn,10,1,1,2);


        playTimeLabel->setText("成功游玩次数:");
        playTime->setText(QString::number(uinfo.PlayTime,10));
        playTime->setAlignment(Qt::AlignCenter);
        personalDataLayout->addWidget(playTimeLabel,11,0,1,1);
        personalDataLayout->addWidget(playTime,11,1,1,2);
/*
        selfTagLabel->setText("Tag：");
        personalDataLayout->addWidget(selfTagLabel,12,0,1,1);

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
        personalDataLayout->addWidget(tag,12,1,2,2);


        */
        signatureLabel->setText("个性签名:");
        personalDataLayout->addWidget(signatureLabel,12,0,1,1);
        signature->setText(StdStringToQString(uinfo.SelfTag));

        personalDataLayout->addWidget(signature,12,1,2,2);

        changeBtn->setText("修改");
        personalDataLayout->addWidget(changeBtn,14,0,1,1);
        confirmBtn->setText("确认");
        personalDataLayout->addWidget(confirmBtn,14,2,1,1);
        this->setLayout(personalDataLayout);
    }
    connect(confirmBtn, &QPushButton::clicked, this, &PersonalDataDialog::on_confirmBtn_clicked);
    connect(changeBtn, &QPushButton::clicked, this, &PersonalDataDialog::on_changeBtn_clicked);
    connect(imageBtn, &QPushButton::clicked, this, &PersonalDataDialog::OpenImage);
}

/***
  *判断一个字符串是否为纯数字
  */
bool PersonalDataDialog::isNotDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
     const char *s = ba.data();

    while(*s && (*s<'0' || *s>'9')) s++;

    if (*s)
    { //含有数字
        return false;
    }
    else
    { //不含数字
        return true;
    }
}

bool PersonalDataDialog::isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
     const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        return false;
    }
    else
    { //纯数字
        return true;
    }
}

bool PersonalDataDialog::JudgeEmpty()
{
    if(userName->text() == NULL) {
        QMessageBox::warning(this, tr("提示"), tr("用户名不能为空！"), QMessageBox::tr("确定"));
        return false;
    }
    if(userPwd->text() == NULL) {
        QMessageBox::warning(this, tr("提示"), tr("密码不能为空！"), QMessageBox::tr("确定"));
        return false;
    }
    if(userPwd2->text() == NULL) {
        QMessageBox::warning(this, tr("提示"), tr("请再次输入密码！"), QMessageBox::tr("确定"));
        return false;
    }
    if(userPwd2->text() != userPwd->text()) {
        QMessageBox::warning(this, tr("提示"), tr("前后密码不一致！"), QMessageBox::tr("确定"));
        return false;
    }
    if(phone->text().length() == NULL || phone->text().size() != 11) {
        QMessageBox::warning(this, tr("提示"), tr("请输入有效的电话！"), QMessageBox::tr("确定"));
        return false;
    }
    if(email->text() == NULL) {
        QMessageBox::warning(this, tr("提示"), tr("请输入邮箱！"), QMessageBox::tr("确定"));
        return false;
    }
    if(email->text() != NULL) {
        QString str = email->text().right(4);

        if(str != ".com") {
            QMessageBox::warning(this, tr("提示"), tr("请输入有效的邮箱！"), QMessageBox::tr("确定"));
            return false;
        }
        if(email->text().indexOf("@") == -1) {
            QMessageBox::warning(this, tr("提示"), tr("请输入有效的邮箱！"), QMessageBox::tr("确定"));
            return false;
        }
    }
    if(QQ->text() == NULL || !isDigitStr(QQ->text())) {
        QMessageBox::warning(this, tr("提示"), tr("请输入有效的QQ号！"), QMessageBox::tr("确定"));
        return false;
    }
    if(studentId->text() == NULL || !isDigitStr(studentId->text())) {
        QMessageBox::warning(this, tr("提示"), tr("请输入有效的学号！"), QMessageBox::tr("确定"));
        return false;
    }
    if(university->text() == NULL || !isNotDigitStr(university->text())) {
        QMessageBox::warning(this, tr("提示"), tr("请输入有效的学校！"), QMessageBox::tr("确定"));
        return false;
    }
    if(locateArea->text() == NULL || !isNotDigitStr(locateArea->text())) {
        QMessageBox::warning(this, tr("提示"), tr("请输入有效的地区！"), QMessageBox::tr("确定"));
        return false;
    }

    return true;
}

PersonalDataDialog::~PersonalDataDialog()
{
    delete ui;
}

void PersonalDataDialog::on_confirmBtn_clicked()
{
    if(JudgeEmpty()) {
        this->hide();
    }
}

void PersonalDataDialog::on_changeBtn_clicked()
{
    this->hide();
}

void PersonalDataDialog::OpenImage()
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
