/********************************************************************************
** Form generated from reading UI file 'personaldatadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONALDATADIALOG_H
#define UI_PERSONALDATADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_PersonalDataDialog
{
public:

    void setupUi(QDialog *PersonalDataDialog)
    {
        if (PersonalDataDialog->objectName().isEmpty())
            PersonalDataDialog->setObjectName(QStringLiteral("PersonalDataDialog"));
        PersonalDataDialog->resize(400, 300);

        retranslateUi(PersonalDataDialog);

        QMetaObject::connectSlotsByName(PersonalDataDialog);
    } // setupUi

    void retranslateUi(QDialog *PersonalDataDialog)
    {
        PersonalDataDialog->setWindowTitle(QApplication::translate("PersonalDataDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PersonalDataDialog: public Ui_PersonalDataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONALDATADIALOG_H
