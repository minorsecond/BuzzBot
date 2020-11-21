/********************************************************************************
** Form generated from reading UI file 'standard_drink_calc.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STANDARD_DRINK_CALC_H
#define UI_STANDARD_DRINK_CALC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_stdDrinkDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *volumeLabel;
    QLabel *abvInputLabel;
    QLabel *standardDrinksLabel;
    QDoubleSpinBox *abvInput;
    QLabel *standardDrinksOutput;
    QSpinBox *volumeInput;
    QPushButton *stdDrinkCalcOkButton;

    void setupUi(QDialog *stdDrinkDialog)
    {
        if (stdDrinkDialog->objectName().isEmpty())
            stdDrinkDialog->setObjectName(QString::fromUtf8("stdDrinkDialog"));
        stdDrinkDialog->resize(237, 142);
        gridLayout = new QGridLayout(stdDrinkDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        volumeLabel = new QLabel(stdDrinkDialog);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));

        gridLayout->addWidget(volumeLabel, 1, 0, 1, 1);

        abvInputLabel = new QLabel(stdDrinkDialog);
        abvInputLabel->setObjectName(QString::fromUtf8("abvInputLabel"));

        gridLayout->addWidget(abvInputLabel, 0, 0, 1, 1);

        standardDrinksLabel = new QLabel(stdDrinkDialog);
        standardDrinksLabel->setObjectName(QString::fromUtf8("standardDrinksLabel"));

        gridLayout->addWidget(standardDrinksLabel, 2, 0, 1, 1);

        abvInput = new QDoubleSpinBox(stdDrinkDialog);
        abvInput->setObjectName(QString::fromUtf8("abvInput"));

        gridLayout->addWidget(abvInput, 0, 1, 1, 1);

        standardDrinksOutput = new QLabel(stdDrinkDialog);
        standardDrinksOutput->setObjectName(QString::fromUtf8("standardDrinksOutput"));

        gridLayout->addWidget(standardDrinksOutput, 2, 1, 1, 1);

        volumeInput = new QSpinBox(stdDrinkDialog);
        volumeInput->setObjectName(QString::fromUtf8("volumeInput"));

        gridLayout->addWidget(volumeInput, 1, 1, 1, 1);

        stdDrinkCalcOkButton = new QPushButton(stdDrinkDialog);
        stdDrinkCalcOkButton->setObjectName(QString::fromUtf8("stdDrinkCalcOkButton"));

        gridLayout->addWidget(stdDrinkCalcOkButton, 3, 1, 1, 1);


        retranslateUi(stdDrinkDialog);

        QMetaObject::connectSlotsByName(stdDrinkDialog);
    } // setupUi

    void retranslateUi(QDialog *stdDrinkDialog)
    {
        stdDrinkDialog->setWindowTitle(QCoreApplication::translate("stdDrinkDialog", "Calculate Std. Drinks", nullptr));
        volumeLabel->setText(QCoreApplication::translate("stdDrinkDialog", "Volume:", nullptr));
        abvInputLabel->setText(QCoreApplication::translate("stdDrinkDialog", "ABV:", nullptr));
        standardDrinksLabel->setText(QCoreApplication::translate("stdDrinkDialog", "Standard drinks:", nullptr));
        standardDrinksOutput->setText(QCoreApplication::translate("stdDrinkDialog", "10", nullptr));
        stdDrinkCalcOkButton->setText(QCoreApplication::translate("stdDrinkDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stdDrinkDialog: public Ui_stdDrinkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STANDARD_DRINK_CALC_H
