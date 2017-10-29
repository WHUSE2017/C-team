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

extern QFont GetFont();
extern QString GetStyle();
extern UserClient client;
#endif // GLOBALVARIABLE_H
