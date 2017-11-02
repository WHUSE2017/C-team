/********************************************************************************
** Form generated from reading UI file 'retrievepwddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETRIEVEPWDDIALOG_H
#define UI_RETRIEVEPWDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_RetrievePwdDialog
{
public:

    void setupUi(QDialog *RetrievePwdDialog)
    {
        if (RetrievePwdDialog->objectName().isEmpty())
            RetrievePwdDialog->setObjectName(QStringLiteral("RetrievePwdDialog"));
        RetrievePwdDialog->resize(400, 300);

        retranslateUi(RetrievePwdDialog);

        QMetaObject::connectSlotsByName(RetrievePwdDialog);
    } // setupUi

    void retranslateUi(QDialog *RetrievePwdDialog)
    {
        RetrievePwdDialog->setWindowTitle(QApplication::translate("RetrievePwdDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RetrievePwdDialog: public Ui_RetrievePwdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETRIEVEPWDDIALOG_H
