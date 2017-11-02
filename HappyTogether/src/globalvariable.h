#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <QString>
#include <QFont>
#include "client/UserClient.h"
extern int const fontSize ;
extern int const boldSize ;
extern QString const fontName;
extern QString startLocate;
extern QString endLocate;
extern QString startDate;
extern QString hiType;
extern QString userNameGlobal;
extern int eventIDGlobal;

extern QString startGlobal;
extern QString endGlobal;

extern QFont GetFont();
extern QString GetStyle();
extern UserClient client;
extern string QStringToStdString(QString str);
extern QString StdStringToQString(string str);
extern HANDLE hProcess;
#endif // GLOBALVARIABLE_H
