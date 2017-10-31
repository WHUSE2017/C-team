#include "globalvariable.h"

#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QTextCodec>
#include <QFile>
#include "base64.h"
extern int const fontSize = 18;
extern int const boldSize = 60;
extern QString startLocate = "";
extern QString endLocate="";
extern QString startDate="";
extern QString hiType="";
extern QString userNameGlobal = "";
extern int eventIDGlobal = 0;
extern QString startGlobal="";
extern QString endGlobal="";

extern QFont GetFont()
{
    //中文支持
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    static QString font;
    int loadedFontID = QFontDatabase::addApplicationFont("./fonts/方正宋刻本秀楷简体.TTF");
    if (loadedFontID != -1)
    {
        QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
        if(!loadedFontFamilies.empty()) {
            font = loadedFontFamilies.at(0);
            //printf("%s\n",font.toStdString());
            QFont fontStyle(font, fontSize, boldSize);
            return fontStyle;
        }
    }
}

extern QString GetStyle()
{
    QFile qssFile("styles/base.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss;
    qss = qssFile.readAll();
    qssFile.close();
    return qss;
}

UserClient client("127.0.0.1",9988);

extern string QStringToStdString(QString str)
{
    std::string s = str.toStdString();
    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
    //std::string decoded = base64_decode(encoded);
    return encoded;
}

extern QString StdStringToQString(string str)
{
    std::string decoded = base64_decode(str);
    return QString::fromStdString(decoded);
}
