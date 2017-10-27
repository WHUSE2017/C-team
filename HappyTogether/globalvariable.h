#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <QString>
#include <QFont>

extern int const fontSize ;
extern int const boldSize ;
extern QString const fontName;
extern QString startLocate;
extern QString endLocate;
extern QString startDate;
extern QString hiType;

extern QFont GetFont();
extern QString GetStyle();

#endif // GLOBALVARIABLE_H
