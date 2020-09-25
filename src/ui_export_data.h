/********************************************************************************
** Form generated from reading UI file 'export_data.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORT_DATA_H
#define UI_EXPORT_DATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_exportDialog
{
public:
    QLineEdit *exportPathInput;
    QLabel *exportPathLabel;
    QPushButton *exportPathBrowse;
    QDialogButtonBox *exportPathButtonBox;

    void setupUi(QDialog *exportDialog)
    {
        if (exportDialog->objectName().isEmpty())
            exportDialog->setObjectName(QString::fromUtf8("exportDialog"));
        exportDialog->resize(550, 119);
        exportPathInput = new QLineEdit(exportDialog);
        exportPathInput->setObjectName(QString::fromUtf8("exportPathInput"));
        exportPathInput->setGeometry(QRect(96, 25, 341, 21));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(exportPathInput->sizePolicy().hasHeightForWidth());
        exportPathInput->setSizePolicy(sizePolicy);
        exportPathLabel = new QLabel(exportDialog);
        exportPathLabel->setObjectName(QString::fromUtf8("exportPathLabel"));
        exportPathLabel->setGeometry(QRect(12, 30, 74, 10));
        exportPathBrowse = new QPushButton(exportDialog);
        exportPathBrowse->setObjectName(QString::fromUtf8("exportPathBrowse"));
        exportPathBrowse->setGeometry(QRect(447, 21, 87, 32));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(exportPathBrowse->sizePolicy().hasHeightForWidth());
        exportPathBrowse->setSizePolicy(sizePolicy1);
        exportPathButtonBox = new QDialogButtonBox(exportDialog);
        exportPathButtonBox->setObjectName(QString::fromUtf8("exportPathButtonBox"));
        exportPathButtonBox->setGeometry(QRect(370, 70, 164, 32));
        exportPathButtonBox->setOrientation(Qt::Horizontal);
        exportPathButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(exportDialog);
        QObject::connect(exportPathButtonBox, SIGNAL(accepted()), exportDialog, SLOT(accept()));
        QObject::connect(exportPathButtonBox, SIGNAL(rejected()), exportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(exportDialog);
    } // setupUi

    void retranslateUi(QDialog *exportDialog)
    {
        exportDialog->setWindowTitle(QCoreApplication::translate("exportDialog", "Export to CSV", nullptr));
        exportPathLabel->setText(QCoreApplication::translate("exportDialog", "Export Path:", nullptr));
        exportPathBrowse->setText(QCoreApplication::translate("exportDialog", "Browse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class exportDialog: public Ui_exportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORT_DATA_H
