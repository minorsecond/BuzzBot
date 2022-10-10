/********************************************************************************
** Form generated from reading UI file 'user_settings.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_SETTINGS_H
#define UI_USER_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_userSettingsDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *defaultLocationRadioBtn;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *customLocationRadioBtn;
    QLineEdit *dbLocationTextInput;
    QPushButton *dbLocationBrowseButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *clearDataButton;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *sexGroup;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *maleSelection;
    QRadioButton *femaleSelection;
    QSpacerItem *horizontalSpacer;
    QGroupBox *unitsGroup;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *imperialRadioButton;
    QRadioButton *metricRadioButton;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *dateCalculationGroup;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rollingDateRadioButton;
    QRadioButton *fixedDateRadioButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *weekdayStartLabel;
    QComboBox *weekdayStartInput;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *dateCalculationGroup_2;
    QGridLayout *gridLayout_2;
    QComboBox *stdDrinkDefComboBox;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_7;
    QDoubleSpinBox *stdDrinkDefInput;
    QLabel *stdDrinkDefLabel;
    QGroupBox *dateCalculationGroup_3;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *niaaaStandardsRadioButton;
    QRadioButton *customLimitRadioButton;
    QGridLayout *gridLayout;
    QLabel *customLimitLabel;
    QSpinBox *customLimitSpinBox;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QDialogButtonBox *userSettingsButtonBox;

    void setupUi(QDialog *userSettingsDialog)
    {
        if (userSettingsDialog->objectName().isEmpty())
            userSettingsDialog->setObjectName(QString::fromUtf8("userSettingsDialog"));
        userSettingsDialog->resize(573, 629);
        userSettingsDialog->setModal(true);
        gridLayout_3 = new QGridLayout(userSettingsDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(userSettingsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        defaultLocationRadioBtn = new QRadioButton(groupBox);
        defaultLocationRadioBtn->setObjectName(QString::fromUtf8("defaultLocationRadioBtn"));
        defaultLocationRadioBtn->setChecked(true);

        verticalLayout->addWidget(defaultLocationRadioBtn);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        customLocationRadioBtn = new QRadioButton(groupBox);
        customLocationRadioBtn->setObjectName(QString::fromUtf8("customLocationRadioBtn"));

        horizontalLayout_2->addWidget(customLocationRadioBtn);

        dbLocationTextInput = new QLineEdit(groupBox);
        dbLocationTextInput->setObjectName(QString::fromUtf8("dbLocationTextInput"));
        dbLocationTextInput->setEnabled(false);
        dbLocationTextInput->setClearButtonEnabled(false);

        horizontalLayout_2->addWidget(dbLocationTextInput);

        dbLocationBrowseButton = new QPushButton(groupBox);
        dbLocationBrowseButton->setObjectName(QString::fromUtf8("dbLocationBrowseButton"));

        horizontalLayout_2->addWidget(dbLocationBrowseButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        clearDataButton = new QPushButton(groupBox);
        clearDataButton->setObjectName(QString::fromUtf8("clearDataButton"));

        horizontalLayout_3->addWidget(clearDataButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        sexGroup = new QGroupBox(userSettingsDialog);
        sexGroup->setObjectName(QString::fromUtf8("sexGroup"));
        horizontalLayout_4 = new QHBoxLayout(sexGroup);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        maleSelection = new QRadioButton(sexGroup);
        maleSelection->setObjectName(QString::fromUtf8("maleSelection"));
        maleSelection->setChecked(true);

        horizontalLayout_4->addWidget(maleSelection);

        femaleSelection = new QRadioButton(sexGroup);
        femaleSelection->setObjectName(QString::fromUtf8("femaleSelection"));

        horizontalLayout_4->addWidget(femaleSelection);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout_3->addWidget(sexGroup, 1, 0, 1, 1);

        unitsGroup = new QGroupBox(userSettingsDialog);
        unitsGroup->setObjectName(QString::fromUtf8("unitsGroup"));
        horizontalLayout_5 = new QHBoxLayout(unitsGroup);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        imperialRadioButton = new QRadioButton(unitsGroup);
        imperialRadioButton->setObjectName(QString::fromUtf8("imperialRadioButton"));
        imperialRadioButton->setChecked(true);

        horizontalLayout_5->addWidget(imperialRadioButton);

        metricRadioButton = new QRadioButton(unitsGroup);
        metricRadioButton->setObjectName(QString::fromUtf8("metricRadioButton"));

        horizontalLayout_5->addWidget(metricRadioButton);

        horizontalSpacer_2 = new QSpacerItem(266, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        gridLayout_3->addWidget(unitsGroup, 2, 0, 1, 1);

        dateCalculationGroup = new QGroupBox(userSettingsDialog);
        dateCalculationGroup->setObjectName(QString::fromUtf8("dateCalculationGroup"));
        verticalLayout_4 = new QVBoxLayout(dateCalculationGroup);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        rollingDateRadioButton = new QRadioButton(dateCalculationGroup);
        rollingDateRadioButton->setObjectName(QString::fromUtf8("rollingDateRadioButton"));
        rollingDateRadioButton->setChecked(true);

        horizontalLayout->addWidget(rollingDateRadioButton);

        fixedDateRadioButton = new QRadioButton(dateCalculationGroup);
        fixedDateRadioButton->setObjectName(QString::fromUtf8("fixedDateRadioButton"));

        horizontalLayout->addWidget(fixedDateRadioButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        weekdayStartLabel = new QLabel(dateCalculationGroup);
        weekdayStartLabel->setObjectName(QString::fromUtf8("weekdayStartLabel"));

        horizontalLayout_6->addWidget(weekdayStartLabel);

        weekdayStartInput = new QComboBox(dateCalculationGroup);
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->setObjectName(QString::fromUtf8("weekdayStartInput"));

        horizontalLayout_6->addWidget(weekdayStartInput);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_6);


        gridLayout_3->addWidget(dateCalculationGroup, 3, 0, 1, 1);

        dateCalculationGroup_2 = new QGroupBox(userSettingsDialog);
        dateCalculationGroup_2->setObjectName(QString::fromUtf8("dateCalculationGroup_2"));
        gridLayout_2 = new QGridLayout(dateCalculationGroup_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        stdDrinkDefComboBox = new QComboBox(dateCalculationGroup_2);
        stdDrinkDefComboBox->setObjectName(QString::fromUtf8("stdDrinkDefComboBox"));

        gridLayout_2->addWidget(stdDrinkDefComboBox, 0, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(317, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        stdDrinkDefInput = new QDoubleSpinBox(dateCalculationGroup_2);
        stdDrinkDefInput->setObjectName(QString::fromUtf8("stdDrinkDefInput"));

        horizontalLayout_7->addWidget(stdDrinkDefInput);

        stdDrinkDefLabel = new QLabel(dateCalculationGroup_2);
        stdDrinkDefLabel->setObjectName(QString::fromUtf8("stdDrinkDefLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stdDrinkDefLabel->sizePolicy().hasHeightForWidth());
        stdDrinkDefLabel->setSizePolicy(sizePolicy);
        stdDrinkDefLabel->setMinimumSize(QSize(70, 21));

        horizontalLayout_7->addWidget(stdDrinkDefLabel);


        gridLayout_2->addLayout(horizontalLayout_7, 1, 0, 1, 1);


        gridLayout_3->addWidget(dateCalculationGroup_2, 4, 0, 1, 1);

        dateCalculationGroup_3 = new QGroupBox(userSettingsDialog);
        dateCalculationGroup_3->setObjectName(QString::fromUtf8("dateCalculationGroup_3"));
        verticalLayout_5 = new QVBoxLayout(dateCalculationGroup_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        niaaaStandardsRadioButton = new QRadioButton(dateCalculationGroup_3);
        niaaaStandardsRadioButton->setObjectName(QString::fromUtf8("niaaaStandardsRadioButton"));
        niaaaStandardsRadioButton->setChecked(true);

        verticalLayout_5->addWidget(niaaaStandardsRadioButton);

        customLimitRadioButton = new QRadioButton(dateCalculationGroup_3);
        customLimitRadioButton->setObjectName(QString::fromUtf8("customLimitRadioButton"));

        verticalLayout_5->addWidget(customLimitRadioButton);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        customLimitLabel = new QLabel(dateCalculationGroup_3);
        customLimitLabel->setObjectName(QString::fromUtf8("customLimitLabel"));

        gridLayout->addWidget(customLimitLabel, 0, 0, 1, 1);

        customLimitSpinBox = new QSpinBox(dateCalculationGroup_3);
        customLimitSpinBox->setObjectName(QString::fromUtf8("customLimitSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(customLimitSpinBox->sizePolicy().hasHeightForWidth());
        customLimitSpinBox->setSizePolicy(sizePolicy1);
        customLimitSpinBox->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(customLimitSpinBox, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        label = new QLabel(dateCalculationGroup_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout);


        gridLayout_3->addWidget(dateCalculationGroup_3, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 23, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 6, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        userSettingsButtonBox = new QDialogButtonBox(userSettingsDialog);
        userSettingsButtonBox->setObjectName(QString::fromUtf8("userSettingsButtonBox"));
        userSettingsButtonBox->setOrientation(Qt::Vertical);
        userSettingsButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(userSettingsButtonBox);


        gridLayout_3->addLayout(verticalLayout_2, 0, 1, 7, 1);

        QWidget::setTabOrder(defaultLocationRadioBtn, customLocationRadioBtn);
        QWidget::setTabOrder(customLocationRadioBtn, dbLocationTextInput);
        QWidget::setTabOrder(dbLocationTextInput, dbLocationBrowseButton);
        QWidget::setTabOrder(dbLocationBrowseButton, clearDataButton);
        QWidget::setTabOrder(clearDataButton, maleSelection);
        QWidget::setTabOrder(maleSelection, femaleSelection);
        QWidget::setTabOrder(femaleSelection, imperialRadioButton);
        QWidget::setTabOrder(imperialRadioButton, metricRadioButton);
        QWidget::setTabOrder(metricRadioButton, rollingDateRadioButton);
        QWidget::setTabOrder(rollingDateRadioButton, fixedDateRadioButton);
        QWidget::setTabOrder(fixedDateRadioButton, weekdayStartInput);
        QWidget::setTabOrder(weekdayStartInput, stdDrinkDefComboBox);
        QWidget::setTabOrder(stdDrinkDefComboBox, stdDrinkDefInput);
        QWidget::setTabOrder(stdDrinkDefInput, niaaaStandardsRadioButton);
        QWidget::setTabOrder(niaaaStandardsRadioButton, customLimitRadioButton);
        QWidget::setTabOrder(customLimitRadioButton, customLimitSpinBox);

        retranslateUi(userSettingsDialog);
        QObject::connect(userSettingsButtonBox, &QDialogButtonBox::accepted, userSettingsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(userSettingsButtonBox, &QDialogButtonBox::rejected, userSettingsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(userSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *userSettingsDialog)
    {
        userSettingsDialog->setWindowTitle(QCoreApplication::translate("userSettingsDialog", "User Settings", nullptr));
        groupBox->setTitle(QCoreApplication::translate("userSettingsDialog", "Database Location", nullptr));
        defaultLocationRadioBtn->setText(QCoreApplication::translate("userSettingsDialog", "Default location", nullptr));
        customLocationRadioBtn->setText(QCoreApplication::translate("userSettingsDialog", "Custom location", nullptr));
        dbLocationBrowseButton->setText(QCoreApplication::translate("userSettingsDialog", "Browse...", nullptr));
        clearDataButton->setText(QCoreApplication::translate("userSettingsDialog", "Clear Data...", nullptr));
        sexGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Sex", nullptr));
        maleSelection->setText(QCoreApplication::translate("userSettingsDialog", "Male", nullptr));
        femaleSelection->setText(QCoreApplication::translate("userSettingsDialog", "Female", nullptr));
        unitsGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Units", nullptr));
        imperialRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Imperial (oz)", nullptr));
        metricRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Metric (ml)", nullptr));
        dateCalculationGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Date Calculation", nullptr));
        rollingDateRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Rolling", nullptr));
        fixedDateRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Reset on day", nullptr));
        weekdayStartLabel->setText(QCoreApplication::translate("userSettingsDialog", "Reset stats on:", nullptr));
        weekdayStartInput->setItemText(0, QCoreApplication::translate("userSettingsDialog", "Sunday", nullptr));
        weekdayStartInput->setItemText(1, QCoreApplication::translate("userSettingsDialog", "Monday", nullptr));
        weekdayStartInput->setItemText(2, QCoreApplication::translate("userSettingsDialog", "Tuesday", nullptr));
        weekdayStartInput->setItemText(3, QCoreApplication::translate("userSettingsDialog", "Wednesday", nullptr));
        weekdayStartInput->setItemText(4, QCoreApplication::translate("userSettingsDialog", "Thursday", nullptr));
        weekdayStartInput->setItemText(5, QCoreApplication::translate("userSettingsDialog", "Friday", nullptr));
        weekdayStartInput->setItemText(6, QCoreApplication::translate("userSettingsDialog", "Saturday", nullptr));

        dateCalculationGroup_2->setTitle(QCoreApplication::translate("userSettingsDialog", "Std. Drink Definition", nullptr));
        stdDrinkDefLabel->setText(QCoreApplication::translate("userSettingsDialog", "Oz. Alcohol", nullptr));
        dateCalculationGroup_3->setTitle(QCoreApplication::translate("userSettingsDialog", "Weekly Limit Standard", nullptr));
        niaaaStandardsRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "CDC/NIAAA", nullptr));
        customLimitRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Custom", nullptr));
        customLimitLabel->setText(QCoreApplication::translate("userSettingsDialog", "Custom Limit* :", nullptr));
        label->setText(QCoreApplication::translate("userSettingsDialog", "* Standard drinks", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userSettingsDialog: public Ui_userSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_SETTINGS_H
