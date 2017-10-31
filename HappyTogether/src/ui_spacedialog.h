/********************************************************************************
** Form generated from reading UI file 'spacedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPACEDIALOG_H
#define UI_SPACEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_SpaceDialog
{
public:

    void setupUi(QDialog *SpaceDialog)
    {
        if (SpaceDialog->objectName().isEmpty())
            SpaceDialog->setObjectName(QStringLiteral("SpaceDialog"));
        SpaceDialog->resize(400, 300);

        retranslateUi(SpaceDialog);

        QMetaObject::connectSlotsByName(SpaceDialog);
    } // setupUi

    void retranslateUi(QDialog *SpaceDialog)
    {
        SpaceDialog->setWindowTitle(QApplication::translate("SpaceDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SpaceDialog: public Ui_SpaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPACEDIALOG_H
