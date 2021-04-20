/********************************************************************************
** Form generated from reading UI file 'delete_confirm.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETE_CONFIRM_H
#define UI_DELETE_CONFIRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_confirmationDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *actionConfirmationLabel;
    QDialogButtonBox *confirmationButtonBox;

    void setupUi(QDialog *confirmationDialog)
    {
        if (confirmationDialog->objectName().isEmpty())
            confirmationDialog->setObjectName(QString::fromUtf8("confirmationDialog"));
        confirmationDialog->resize(400, 88);
        gridLayout = new QGridLayout(confirmationDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        actionConfirmationLabel = new QLabel(confirmationDialog);
        actionConfirmationLabel->setObjectName(QString::fromUtf8("actionConfirmationLabel"));

        gridLayout->addWidget(actionConfirmationLabel, 0, 0, 1, 1);

        confirmationButtonBox = new QDialogButtonBox(confirmationDialog);
        confirmationButtonBox->setObjectName(QString::fromUtf8("confirmationButtonBox"));
        confirmationButtonBox->setOrientation(Qt::Horizontal);
        confirmationButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(confirmationButtonBox, 1, 0, 1, 1);


        retranslateUi(confirmationDialog);
        QObject::connect(confirmationButtonBox, &QDialogButtonBox::accepted, confirmationDialog, &QDialog::accept);
        QObject::connect(confirmationButtonBox, &QDialogButtonBox::rejected, confirmationDialog, &QDialog::reject);

        QMetaObject::connectSlotsByName(confirmationDialog);
    } // setupUi

    void retranslateUi(QDialog *confirmationDialog)
    {
        confirmationDialog->setWindowTitle(QCoreApplication::translate("confirmationDialog", "Confirmation", nullptr));
        actionConfirmationLabel->setText(QCoreApplication::translate("confirmationDialog", "You are attempting to delete a row. Click OK to confirm.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class confirmationDialog: public Ui_confirmationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETE_CONFIRM_H
