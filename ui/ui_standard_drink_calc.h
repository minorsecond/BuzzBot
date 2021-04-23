/********************************************************************************
** Form generated from reading UI file 'standard_drink_calc.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
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

QT_BEGIN_NAMESPACE

class Ui_stdDrinkDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *abvInputLabel;
    QDoubleSpinBox *abvInput;
    QLabel *standardDrinksLabel;
    QPushButton *stdDrinkCalcOkButton;
    QDoubleSpinBox *volumeInput;
    QLabel *volumeLabel;
    QLabel *standardDrinksOutput;
    QLabel *stdDrinkLabel;
    QDoubleSpinBox *stdDrinkInput;

    void setupUi(QDialog *stdDrinkDialog)
    {
        if (stdDrinkDialog->objectName().isEmpty())
            stdDrinkDialog->setObjectName(QString::fromUtf8("stdDrinkDialog"));
        stdDrinkDialog->resize(237, 167);
        gridLayout = new QGridLayout(stdDrinkDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        abvInputLabel = new QLabel(stdDrinkDialog);
        abvInputLabel->setObjectName(QString::fromUtf8("abvInputLabel"));

        gridLayout->addWidget(abvInputLabel, 0, 0, 1, 1);

        abvInput = new QDoubleSpinBox(stdDrinkDialog);
        abvInput->setObjectName(QString::fromUtf8("abvInput"));

        gridLayout->addWidget(abvInput, 0, 1, 1, 1);

        standardDrinksLabel = new QLabel(stdDrinkDialog);
        standardDrinksLabel->setObjectName(QString::fromUtf8("standardDrinksLabel"));

        gridLayout->addWidget(standardDrinksLabel, 3, 0, 1, 1);

        stdDrinkCalcOkButton = new QPushButton(stdDrinkDialog);
        stdDrinkCalcOkButton->setObjectName(QString::fromUtf8("stdDrinkCalcOkButton"));

        gridLayout->addWidget(stdDrinkCalcOkButton, 4, 1, 1, 1);

        volumeInput = new QDoubleSpinBox(stdDrinkDialog);
        volumeInput->setObjectName(QString::fromUtf8("volumeInput"));
        volumeInput->setDecimals(1);

        gridLayout->addWidget(volumeInput, 1, 1, 1, 1);

        volumeLabel = new QLabel(stdDrinkDialog);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));

        gridLayout->addWidget(volumeLabel, 1, 0, 1, 1);

        standardDrinksOutput = new QLabel(stdDrinkDialog);
        standardDrinksOutput->setObjectName(QString::fromUtf8("standardDrinksOutput"));

        gridLayout->addWidget(standardDrinksOutput, 3, 1, 1, 1);

        stdDrinkLabel = new QLabel(stdDrinkDialog);
        stdDrinkLabel->setObjectName(QString::fromUtf8("stdDrinkLabel"));

        gridLayout->addWidget(stdDrinkLabel, 2, 0, 1, 1);

        stdDrinkInput = new QDoubleSpinBox(stdDrinkDialog);
        stdDrinkInput->setObjectName(QString::fromUtf8("stdDrinkInput"));

        gridLayout->addWidget(stdDrinkInput, 2, 1, 1, 1);


        retranslateUi(stdDrinkDialog);

        QMetaObject::connectSlotsByName(stdDrinkDialog);
    } // setupUi

    void retranslateUi(QDialog *stdDrinkDialog)
    {
        stdDrinkDialog->setWindowTitle(QCoreApplication::translate("stdDrinkDialog", "Calculate Std. Drinks", nullptr));
        abvInputLabel->setText(QCoreApplication::translate("stdDrinkDialog", "ABV:", nullptr));
        standardDrinksLabel->setText(QCoreApplication::translate("stdDrinkDialog", "Standard drinks:", nullptr));
        stdDrinkCalcOkButton->setText(QCoreApplication::translate("stdDrinkDialog", "OK", nullptr));
        volumeLabel->setText(QCoreApplication::translate("stdDrinkDialog", "Volume:", nullptr));
        standardDrinksOutput->setText(QCoreApplication::translate("stdDrinkDialog", "10", nullptr));
        stdDrinkLabel->setText(QCoreApplication::translate("stdDrinkDialog", "1 Std. Drink:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stdDrinkDialog: public Ui_stdDrinkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STANDARD_DRINK_CALC_H
