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
    QGridLayout *gridLayout_3;
    QDateEdit *endDateEdit;
    QComboBox *alcoholTypeSelection;
    QLabel *label_3;
    QLabel *label;
    QSpinBox *topNumberSelection;
    QDateEdit *startDateEdit;
    QLabel *label_4;
    QLabel *label_2;
    QSpinBox *ratingSelection;
    QTableWidget *queryResults;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *TopDrinkReportGui)
    {
        if (TopDrinkReportGui->objectName().isEmpty())
            TopDrinkReportGui->setObjectName(QString::fromUtf8("TopDrinkReportGui"));
        TopDrinkReportGui->resize(717, 525);
        gridLayout = new QGridLayout(TopDrinkReportGui);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        endDateEdit = new QDateEdit(TopDrinkReportGui);
        endDateEdit->setObjectName(QString::fromUtf8("endDateEdit"));
        endDateEdit->setMinimumSize(QSize(100, 0));
        endDateEdit->setDateTime(QDateTime(QDate(2022, 12, 20), QTime(0, 0, 0)));
        endDateEdit->setCalendarPopup(true);

        gridLayout_3->addWidget(endDateEdit, 0, 6, 1, 1);

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
        startDateEdit->setMinimumSize(QSize(100, 0));
        startDateEdit->setDateTime(QDateTime(QDate(2022, 12, 20), QTime(0, 0, 0)));
        startDateEdit->setCalendarPopup(true);

        gridLayout_3->addWidget(startDateEdit, 0, 4, 1, 1);

        label_4 = new QLabel(TopDrinkReportGui);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 7, 1, 1);

        label_2 = new QLabel(TopDrinkReportGui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 3, 1, 1);

        ratingSelection = new QSpinBox(TopDrinkReportGui);
        ratingSelection->setObjectName(QString::fromUtf8("ratingSelection"));
        ratingSelection->setMaximum(10);
        ratingSelection->setValue(7);

        gridLayout_3->addWidget(ratingSelection, 0, 8, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 1, 0, 1, 1);

        queryResults = new QTableWidget(TopDrinkReportGui);
        if (queryResults->columnCount() < 5)
            queryResults->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        queryResults->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        queryResults->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        queryResults->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        queryResults->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        queryResults->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        queryResults->setObjectName(QString::fromUtf8("queryResults"));

        gridLayout_2->addWidget(queryResults, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(TopDrinkReportGui);

        QMetaObject::connectSlotsByName(TopDrinkReportGui);
    } // setupUi

    void retranslateUi(QDialog *TopDrinkReportGui)
    {
        TopDrinkReportGui->setWindowTitle(QCoreApplication::translate("TopDrinkReportGui", "Top Drink Report", nullptr));
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
        startDateEdit->setDisplayFormat(QCoreApplication::translate("TopDrinkReportGui", "M/d/yyyy", nullptr));
        label_4->setText(QCoreApplication::translate("TopDrinkReportGui", "where rating >=", nullptr));
        label_2->setText(QCoreApplication::translate("TopDrinkReportGui", "between", nullptr));
        QTableWidgetItem *___qtablewidgetitem = queryResults->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TopDrinkReportGui", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = queryResults->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TopDrinkReportGui", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = queryResults->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TopDrinkReportGui", "Subtype", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = queryResults->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TopDrinkReportGui", "Producer", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = queryResults->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TopDrinkReportGui", "Rating", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TopDrinkReportGui: public Ui_TopDrinkReportGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRINK_REPORT_H
