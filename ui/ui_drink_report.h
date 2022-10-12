/********************************************************************************
** Form generated from reading UI file 'drink_report.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRINK_REPORT_H
#define UI_DRINK_REPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TopDrinkReportGui
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QTableWidget *queryResults;
    QGridLayout *gridLayout_3;
    QComboBox *alcoholTypeSelection;
    QLabel *label_3;
    QLabel *label;
    QSpinBox *topNumberSelection;
    QDateEdit *startDateEdit;
    QLabel *label_2;
    QDateEdit *endDateEdit;

    void setupUi(QDialog *TopDrinkReportGui)
    {
        if (TopDrinkReportGui->objectName().isEmpty())
            TopDrinkReportGui->setObjectName(QString::fromUtf8("TopDrinkReportGui"));
        TopDrinkReportGui->resize(621, 525);
        gridLayout = new QGridLayout(TopDrinkReportGui);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton = new QPushButton(TopDrinkReportGui);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 0, 1, 1);

        queryResults = new QTableWidget(TopDrinkReportGui);
        queryResults->setObjectName(QString::fromUtf8("queryResults"));

        gridLayout_2->addWidget(queryResults, 2, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        alcoholTypeSelection = new QComboBox(TopDrinkReportGui);
        alcoholTypeSelection->addItem(QString());
        alcoholTypeSelection->addItem(QString());
        alcoholTypeSelection->addItem(QString());
        alcoholTypeSelection->addItem(QString());
        alcoholTypeSelection->setObjectName(QString::fromUtf8("alcoholTypeSelection"));
        alcoholTypeSelection->setMaxVisibleItems(9);

        gridLayout_3->addWidget(alcoholTypeSelection, 0, 2, 1, 1);

        label_3 = new QLabel(TopDrinkReportGui);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 5, 1, 1);

        label = new QLabel(TopDrinkReportGui);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        topNumberSelection = new QSpinBox(TopDrinkReportGui);
        topNumberSelection->setObjectName(QString::fromUtf8("topNumberSelection"));
        topNumberSelection->setMinimum(3);
        topNumberSelection->setValue(10);

        gridLayout_3->addWidget(topNumberSelection, 0, 1, 1, 1);

        startDateEdit = new QDateEdit(TopDrinkReportGui);
        startDateEdit->setObjectName(QString::fromUtf8("startDateEdit"));

        gridLayout_3->addWidget(startDateEdit, 0, 4, 1, 1);

        label_2 = new QLabel(TopDrinkReportGui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 3, 1, 1);

        endDateEdit = new QDateEdit(TopDrinkReportGui);
        endDateEdit->setObjectName(QString::fromUtf8("endDateEdit"));

        gridLayout_3->addWidget(endDateEdit, 0, 6, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(TopDrinkReportGui);

        QMetaObject::connectSlotsByName(TopDrinkReportGui);
    } // setupUi

    void retranslateUi(QDialog *TopDrinkReportGui)
    {
        TopDrinkReportGui->setWindowTitle(QCoreApplication::translate("TopDrinkReportGui", "Top Drink Report", nullptr));
        pushButton->setText(QCoreApplication::translate("TopDrinkReportGui", "OK", nullptr));
        alcoholTypeSelection->setItemText(0, QCoreApplication::translate("TopDrinkReportGui", "All Types", nullptr));
        alcoholTypeSelection->setItemText(1, QCoreApplication::translate("TopDrinkReportGui", "Beer", nullptr));
        alcoholTypeSelection->setItemText(2, QCoreApplication::translate("TopDrinkReportGui", "Liquor", nullptr));
        alcoholTypeSelection->setItemText(3, QCoreApplication::translate("TopDrinkReportGui", "Wine", nullptr));

#if QT_CONFIG(tooltip)
        alcoholTypeSelection->setToolTip(QCoreApplication::translate("TopDrinkReportGui", "Type of alcohol to select from", nullptr));
#endif // QT_CONFIG(tooltip)
        alcoholTypeSelection->setCurrentText(QCoreApplication::translate("TopDrinkReportGui", "All Types", nullptr));
        label_3->setText(QCoreApplication::translate("TopDrinkReportGui", "and", nullptr));
        label->setText(QCoreApplication::translate("TopDrinkReportGui", "Select top", nullptr));
#if QT_CONFIG(tooltip)
        topNumberSelection->setToolTip(QCoreApplication::translate("TopDrinkReportGui", "Number of records to select", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("TopDrinkReportGui", "between", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TopDrinkReportGui: public Ui_TopDrinkReportGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRINK_REPORT_H
