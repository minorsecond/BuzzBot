/********************************************************************************
** Form generated from reading UI file 'standard_drink_calc.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_stdDrinkDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QDoubleSpinBox *abvInput;
    QDoubleSpinBox *volumeInput;
    QLabel *standardDrinksLabel;
    QLabel *standardDrinksOutput;
    QLabel *abvInputLabel;
    QLabel *volumeLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *stdDrinkCalcOkButton;

    void setupUi(QDialog *stdDrinkDialog)
    {
        if (stdDrinkDialog->objectName().isEmpty())
            stdDrinkDialog->setObjectName(QString::fromUtf8("stdDrinkDialog"));
        stdDrinkDialog->resize(320, 169);
        verticalLayout = new QVBoxLayout(stdDrinkDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        abvInput = new QDoubleSpinBox(stdDrinkDialog);
        abvInput->setObjectName(QString::fromUtf8("abvInput"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(abvInput->sizePolicy().hasHeightForWidth());
        abvInput->setSizePolicy(sizePolicy);

        gridLayout->addWidget(abvInput, 0, 2, 1, 1);

        volumeInput = new QDoubleSpinBox(stdDrinkDialog);
        volumeInput->setObjectName(QString::fromUtf8("volumeInput"));
        sizePolicy.setHeightForWidth(volumeInput->sizePolicy().hasHeightForWidth());
        volumeInput->setSizePolicy(sizePolicy);
        volumeInput->setDecimals(1);

        gridLayout->addWidget(volumeInput, 1, 2, 1, 1);

        standardDrinksLabel = new QLabel(stdDrinkDialog);
        standardDrinksLabel->setObjectName(QString::fromUtf8("standardDrinksLabel"));

        gridLayout->addWidget(standardDrinksLabel, 2, 0, 1, 2);

        standardDrinksOutput = new QLabel(stdDrinkDialog);
        standardDrinksOutput->setObjectName(QString::fromUtf8("standardDrinksOutput"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(standardDrinksOutput->sizePolicy().hasHeightForWidth());
        standardDrinksOutput->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(standardDrinksOutput, 2, 2, 1, 1);

        abvInputLabel = new QLabel(stdDrinkDialog);
        abvInputLabel->setObjectName(QString::fromUtf8("abvInputLabel"));

        gridLayout->addWidget(abvInputLabel, 0, 0, 1, 2);

        volumeLabel = new QLabel(stdDrinkDialog);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));

        gridLayout->addWidget(volumeLabel, 1, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 138, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(188, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        stdDrinkCalcOkButton = new QPushButton(stdDrinkDialog);
        stdDrinkCalcOkButton->setObjectName(QString::fromUtf8("stdDrinkCalcOkButton"));

        horizontalLayout->addWidget(stdDrinkCalcOkButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(stdDrinkDialog);

        QMetaObject::connectSlotsByName(stdDrinkDialog);
    } // setupUi

    void retranslateUi(QDialog *stdDrinkDialog)
    {
        stdDrinkDialog->setWindowTitle(QCoreApplication::translate("stdDrinkDialog", "Calculate Std. Drinks", nullptr));
        standardDrinksLabel->setText(QCoreApplication::translate("stdDrinkDialog", "Standard drinks:", nullptr));
        standardDrinksOutput->setText(QCoreApplication::translate("stdDrinkDialog", "10", nullptr));
        abvInputLabel->setText(QCoreApplication::translate("stdDrinkDialog", "ABV:", nullptr));
        volumeLabel->setText(QCoreApplication::translate("stdDrinkDialog", "Volume:", nullptr));
        stdDrinkCalcOkButton->setText(QCoreApplication::translate("stdDrinkDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stdDrinkDialog: public Ui_stdDrinkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STANDARD_DRINK_CALC_H
