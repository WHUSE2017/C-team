/********************************************************************************
** Form generated from reading UI file 'activitydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIVITYDIALOG_H
#define UI_ACTIVITYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ActivityDialog
{
public:

    void setupUi(QDialog *ActivityDialog)
    {
        if (ActivityDialog->objectName().isEmpty())
            ActivityDialog->setObjectName(QStringLiteral("ActivityDialog"));
        ActivityDialog->resize(400, 300);

        retranslateUi(ActivityDialog);

        QMetaObject::connectSlotsByName(ActivityDialog);
    } // setupUi

    void retranslateUi(QDialog *ActivityDialog)
    {
        ActivityDialog->setWindowTitle(QApplication::translate("ActivityDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ActivityDialog: public Ui_ActivityDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIVITYDIALOG_H
