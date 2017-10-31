/********************************************************************************
** Form generated from reading UI file 'sendmessagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDMESSAGEDIALOG_H
#define UI_SENDMESSAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_SendMessageDialog
{
public:

    void setupUi(QDialog *SendMessageDialog)
    {
        if (SendMessageDialog->objectName().isEmpty())
            SendMessageDialog->setObjectName(QStringLiteral("SendMessageDialog"));
        SendMessageDialog->resize(400, 300);

        retranslateUi(SendMessageDialog);

        QMetaObject::connectSlotsByName(SendMessageDialog);
    } // setupUi

    void retranslateUi(QDialog *SendMessageDialog)
    {
        SendMessageDialog->setWindowTitle(QApplication::translate("SendMessageDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SendMessageDialog: public Ui_SendMessageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDMESSAGEDIALOG_H
