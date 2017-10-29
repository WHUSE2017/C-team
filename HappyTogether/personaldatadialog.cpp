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
     struct userStruct uinfo = client.getUserInfo((char*)userNameGlobal.toStdString().data());//如果用户存在
     if(uinfo.UserName!="") {
         //cout<<uinfo.UserName<<" "<<uinfo.Email<<" "<<uinfo.Phone<<" "<<uinfo.UserQQ<<endl;

        nameLabel->setText("用户名：");
        personalDataLayout->addWidget(nameLabel,0,0,1,1);
        userName->setText(QString::fromStdString(uinfo.UserName));
        personalDataLayout->addWidget(userName,0,1,1,2);

        pwdLabel->setText("密码：");
        personalDataLayout->addWidget(pwdLabel,1,0,1,1);
        userPwd->setText(QString::fromStdString(uinfo.PassWord));
        personalDataLayout->addWidget(userPwd,1,1,1,2);

        pwdLabel2->setText("再次密码：");
        personalDataLayout->addWidget(pwdLabel2,2,0,1,1);
        userPwd2->setPlaceholderText("请再次输入密码");
        personalDataLayout->addWidget(userPwd2,2,1,1,2);

        sexLabel->setText("性别：");
        personalDataLayout->addWidget(sexLabel,3,0,1,1);
        sexType->addItem("男");
        sexType->addItem("女");
        personalDataLayout->addWidget(sexType,3,1,1,2);

        phoneLabel->setText("电话：");
        personalDataLayout->addWidget(phoneLabel,4,0,1,1);
        phone->setText("4334");
        personalDataLayout->addWidget(phone,4,1,1,2);

        emailLabel->setText("邮箱：");
        personalDataLayout->addWidget(emailLabel,5,0,1,1);
        email->setText("3243433@qq.com");
        personalDataLayout->addWidget(email,5,1,1,2);
        QQLabel->setText("QQ：");
        personalDataLayout->addWidget(QQLabel,6,0,1,1);
        QQ->setText(QString::fromStdString(uinfo.UserQQ));
        personalDataLayout->addWidget(QQ,6,1,1,2);

        studentIdLabel->setText("学号：");
        personalDataLayout->addWidget(studentIdLabel,7,0,1,1);
        studentId->setText(QString::number(uinfo.StudentId,10));
        personalDataLayout->addWidget(studentId,7,1,1,2);
        universityLabel->setText("学校：");
        personalDataLayout->addWidget(universityLabel,8,0,1,1);
        university->setText(QString::fromStdString(uinfo.University));
        personalDataLayout->addWidget(university,8,1,1,2);
        locateAreaLabel->setText("地区：");
        personalDataLayout->addWidget(locateAreaLabel,9,0,1,1);
        locateArea->setText(QString::fromStdString(uinfo.LocateArea));
        personalDataLayout->addWidget(locateArea,9,1,1,2);
        imageLabel->setText("头像：");
        personalDataLayout->addWidget(imageLabel,10,0,1,1);
        imageBtn->setText("上传");
        personalDataLayout->addWidget(imageBtn,10,1,1,2);

        playTimeLabel->setText("成功游玩次数:");
        playTime->setText("12次");
        playTime->setAlignment(Qt::AlignCenter);
        personalDataLayout->addWidget(playTimeLabel,11,0,1,1);
        personalDataLayout->addWidget(playTime,11,1,1,2);

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

PersonalDataDialog::~PersonalDataDialog()
{
    delete ui;
}

void PersonalDataDialog::on_confirmBtn_clicked()
{
    this->hide();
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
