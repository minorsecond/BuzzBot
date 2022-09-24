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
#include <QtWidgets/QFrame>
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
    QGridLayout *gridLayout_2;
    QFrame *frame_3;
    QGridLayout *gridLayout_8;
    QPushButton *clearDataButton;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QGroupBox *sexGroup;
    QGridLayout *gridLayout_4;
    QRadioButton *maleSelection;
    QRadioButton *femaleSelection;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QGroupBox *dateCalculationGroup;
    QGridLayout *gridLayout;
    QLabel *weekdayStartLabel;
    QComboBox *weekdayStartInput;
    QRadioButton *rollingDateRadioButton;
    QRadioButton *fixedDateRadioButton;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_5;
    QGridLayout *gridLayout_11;
    QLabel *stdDrinkDefTitle;
    QDoubleSpinBox *stdDrinkDefInput;
    QLabel *stdDrinkDefLabel;
    QComboBox *stdDrinkDefComboBox;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout_5;
    QFrame *weeklyLimitFrame;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QGroupBox *weeklyLimitGroup;
    QGridLayout *gridLayout_6;
    QRadioButton *niaaaStandardsRadioButton;
    QLabel *customLimitLabel;
    QSpinBox *customLimitSpinBox;
    QRadioButton *customLimitRadioButton;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_6;
    QFrame *frame_4;
    QGridLayout *gridLayout_9;
    QGroupBox *unitsGroup;
    QGridLayout *gridLayout_10;
    QRadioButton *metricRadioButton;
    QRadioButton *imperialRadioButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_12;
    QLineEdit *dbLocationTextInput;
    QPushButton *dbLocationBrowseButton;
    QRadioButton *defaultLocationRadioBtn;
    QRadioButton *customLocationRadioBtn;
    QVBoxLayout *verticalLayout_2;
    QDialogButtonBox *userSettingsButtonBox;

    void setupUi(QDialog *userSettingsDialog)
    {
        if (userSettingsDialog->objectName().isEmpty())
            userSettingsDialog->setObjectName(QString::fromUtf8("userSettingsDialog"));
        userSettingsDialog->resize(1010, 807);
        userSettingsDialog->setModal(true);
        gridLayout_2 = new QGridLayout(userSettingsDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        frame_3 = new QFrame(userSettingsDialog);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(frame_3);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        clearDataButton = new QPushButton(frame_3);
        clearDataButton->setObjectName(QString::fromUtf8("clearDataButton"));

        gridLayout_8->addWidget(clearDataButton, 0, 1, 1, 1);


        gridLayout_2->addWidget(frame_3, 4, 0, 1, 1);

        frame = new QFrame(userSettingsDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        sexGroup = new QGroupBox(frame);
        sexGroup->setObjectName(QString::fromUtf8("sexGroup"));
        sexGroup->setAlignment(Qt::AlignCenter);
        sexGroup->setFlat(true);
        gridLayout_4 = new QGridLayout(sexGroup);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        maleSelection = new QRadioButton(sexGroup);
        maleSelection->setObjectName(QString::fromUtf8("maleSelection"));
        maleSelection->setChecked(true);

        gridLayout_4->addWidget(maleSelection, 1, 0, 1, 1);

        femaleSelection = new QRadioButton(sexGroup);
        femaleSelection->setObjectName(QString::fromUtf8("femaleSelection"));

        gridLayout_4->addWidget(femaleSelection, 2, 0, 1, 1);


        gridLayout_5->addWidget(sexGroup, 1, 0, 1, 1);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(userSettingsDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        dateCalculationGroup = new QGroupBox(frame_2);
        dateCalculationGroup->setObjectName(QString::fromUtf8("dateCalculationGroup"));
        dateCalculationGroup->setAlignment(Qt::AlignCenter);
        dateCalculationGroup->setFlat(true);
        gridLayout = new QGridLayout(dateCalculationGroup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        weekdayStartLabel = new QLabel(dateCalculationGroup);
        weekdayStartLabel->setObjectName(QString::fromUtf8("weekdayStartLabel"));

        gridLayout->addWidget(weekdayStartLabel, 4, 0, 1, 1);

        weekdayStartInput = new QComboBox(dateCalculationGroup);
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->setObjectName(QString::fromUtf8("weekdayStartInput"));

        gridLayout->addWidget(weekdayStartInput, 5, 0, 1, 1);

        rollingDateRadioButton = new QRadioButton(dateCalculationGroup);
        rollingDateRadioButton->setObjectName(QString::fromUtf8("rollingDateRadioButton"));
        rollingDateRadioButton->setChecked(true);

        gridLayout->addWidget(rollingDateRadioButton, 0, 0, 1, 1);

        fixedDateRadioButton = new QRadioButton(dateCalculationGroup);
        fixedDateRadioButton->setObjectName(QString::fromUtf8("fixedDateRadioButton"));

        gridLayout->addWidget(fixedDateRadioButton, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);


        gridLayout_3->addWidget(dateCalculationGroup, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_2);

        frame_5 = new QFrame(userSettingsDialog);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_11 = new QGridLayout(frame_5);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        stdDrinkDefTitle = new QLabel(frame_5);
        stdDrinkDefTitle->setObjectName(QString::fromUtf8("stdDrinkDefTitle"));
        stdDrinkDefTitle->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(stdDrinkDefTitle, 0, 0, 1, 2);

        stdDrinkDefInput = new QDoubleSpinBox(frame_5);
        stdDrinkDefInput->setObjectName(QString::fromUtf8("stdDrinkDefInput"));

        gridLayout_11->addWidget(stdDrinkDefInput, 2, 0, 1, 1);

        stdDrinkDefLabel = new QLabel(frame_5);
        stdDrinkDefLabel->setObjectName(QString::fromUtf8("stdDrinkDefLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stdDrinkDefLabel->sizePolicy().hasHeightForWidth());
        stdDrinkDefLabel->setSizePolicy(sizePolicy);
        stdDrinkDefLabel->setMinimumSize(QSize(70, 21));

        gridLayout_11->addWidget(stdDrinkDefLabel, 2, 1, 1, 1);

        stdDrinkDefComboBox = new QComboBox(frame_5);
        stdDrinkDefComboBox->setObjectName(QString::fromUtf8("stdDrinkDefComboBox"));

        gridLayout_11->addWidget(stdDrinkDefComboBox, 1, 0, 1, 2);


        verticalLayout->addWidget(frame_5);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        weeklyLimitFrame = new QFrame(userSettingsDialog);
        weeklyLimitFrame->setObjectName(QString::fromUtf8("weeklyLimitFrame"));
        weeklyLimitFrame->setFrameShape(QFrame::StyledPanel);
        weeklyLimitFrame->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(weeklyLimitFrame);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label = new QLabel(weeklyLimitFrame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label, 1, 0, 1, 1);

        weeklyLimitGroup = new QGroupBox(weeklyLimitFrame);
        weeklyLimitGroup->setObjectName(QString::fromUtf8("weeklyLimitGroup"));
        weeklyLimitGroup->setToolTipDuration(-1);
        weeklyLimitGroup->setAlignment(Qt::AlignCenter);
        weeklyLimitGroup->setFlat(true);
        gridLayout_6 = new QGridLayout(weeklyLimitGroup);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        niaaaStandardsRadioButton = new QRadioButton(weeklyLimitGroup);
        niaaaStandardsRadioButton->setObjectName(QString::fromUtf8("niaaaStandardsRadioButton"));

        gridLayout_6->addWidget(niaaaStandardsRadioButton, 1, 0, 1, 1);

        customLimitLabel = new QLabel(weeklyLimitGroup);
        customLimitLabel->setObjectName(QString::fromUtf8("customLimitLabel"));

        gridLayout_6->addWidget(customLimitLabel, 7, 0, 1, 1);

        customLimitSpinBox = new QSpinBox(weeklyLimitGroup);
        customLimitSpinBox->setObjectName(QString::fromUtf8("customLimitSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(customLimitSpinBox->sizePolicy().hasHeightForWidth());
        customLimitSpinBox->setSizePolicy(sizePolicy1);
        customLimitSpinBox->setMinimumSize(QSize(0, 25));

        gridLayout_6->addWidget(customLimitSpinBox, 8, 0, 1, 1);

        customLimitRadioButton = new QRadioButton(weeklyLimitGroup);
        customLimitRadioButton->setObjectName(QString::fromUtf8("customLimitRadioButton"));

        gridLayout_6->addWidget(customLimitRadioButton, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_3, 6, 0, 1, 1);


        gridLayout_7->addWidget(weeklyLimitGroup, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 55, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer, 2, 0, 1, 1);


        verticalLayout_5->addWidget(weeklyLimitFrame);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);


        horizontalLayout->addLayout(verticalLayout_5);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 5, 1);

        frame_4 = new QFrame(userSettingsDialog);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_9 = new QGridLayout(frame_4);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        unitsGroup = new QGroupBox(frame_4);
        unitsGroup->setObjectName(QString::fromUtf8("unitsGroup"));
        unitsGroup->setAlignment(Qt::AlignCenter);
        unitsGroup->setFlat(true);
        gridLayout_10 = new QGridLayout(unitsGroup);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        metricRadioButton = new QRadioButton(unitsGroup);
        metricRadioButton->setObjectName(QString::fromUtf8("metricRadioButton"));

        gridLayout_10->addWidget(metricRadioButton, 1, 0, 1, 1);

        imperialRadioButton = new QRadioButton(unitsGroup);
        imperialRadioButton->setObjectName(QString::fromUtf8("imperialRadioButton"));
        imperialRadioButton->setChecked(true);

        gridLayout_10->addWidget(imperialRadioButton, 0, 0, 1, 1);


        gridLayout_9->addWidget(unitsGroup, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_4, 3, 0, 1, 1);

        groupBox = new QGroupBox(userSettingsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayout_12 = new QGridLayout(groupBox);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        dbLocationTextInput = new QLineEdit(groupBox);
        dbLocationTextInput->setObjectName(QString::fromUtf8("dbLocationTextInput"));
        dbLocationTextInput->setEnabled(false);
        dbLocationTextInput->setClearButtonEnabled(false);

        gridLayout_12->addWidget(dbLocationTextInput, 2, 1, 1, 1);

        dbLocationBrowseButton = new QPushButton(groupBox);
        dbLocationBrowseButton->setObjectName(QString::fromUtf8("dbLocationBrowseButton"));

        gridLayout_12->addWidget(dbLocationBrowseButton, 2, 2, 1, 1);

        defaultLocationRadioBtn = new QRadioButton(groupBox);
        defaultLocationRadioBtn->setObjectName(QString::fromUtf8("defaultLocationRadioBtn"));
        defaultLocationRadioBtn->setChecked(true);

        gridLayout_12->addWidget(defaultLocationRadioBtn, 0, 1, 1, 1);

        customLocationRadioBtn = new QRadioButton(groupBox);
        customLocationRadioBtn->setObjectName(QString::fromUtf8("customLocationRadioBtn"));

        gridLayout_12->addWidget(customLocationRadioBtn, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        gridLayout_12->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 2);

        userSettingsButtonBox = new QDialogButtonBox(userSettingsDialog);
        userSettingsButtonBox->setObjectName(QString::fromUtf8("userSettingsButtonBox"));
        userSettingsButtonBox->setOrientation(Qt::Vertical);
        userSettingsButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(userSettingsButtonBox, 0, 2, 1, 1);


        retranslateUi(userSettingsDialog);
        QObject::connect(userSettingsButtonBox, &QDialogButtonBox::accepted, userSettingsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(userSettingsButtonBox, &QDialogButtonBox::rejected, userSettingsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(userSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *userSettingsDialog)
    {
        userSettingsDialog->setWindowTitle(QCoreApplication::translate("userSettingsDialog", "User Settings", nullptr));
        clearDataButton->setText(QCoreApplication::translate("userSettingsDialog", "Clear Data", nullptr));
        sexGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Sex", nullptr));
        maleSelection->setText(QCoreApplication::translate("userSettingsDialog", "Male", nullptr));
        femaleSelection->setText(QCoreApplication::translate("userSettingsDialog", "Female", nullptr));
        dateCalculationGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Date Calculation", nullptr));
        weekdayStartLabel->setText(QCoreApplication::translate("userSettingsDialog", "Reset stats on:", nullptr));
        weekdayStartInput->setItemText(0, QCoreApplication::translate("userSettingsDialog", "Sunday", nullptr));
        weekdayStartInput->setItemText(1, QCoreApplication::translate("userSettingsDialog", "Monday", nullptr));
        weekdayStartInput->setItemText(2, QCoreApplication::translate("userSettingsDialog", "Tuesday", nullptr));
        weekdayStartInput->setItemText(3, QCoreApplication::translate("userSettingsDialog", "Wednesday", nullptr));
        weekdayStartInput->setItemText(4, QCoreApplication::translate("userSettingsDialog", "Thursday", nullptr));
        weekdayStartInput->setItemText(5, QCoreApplication::translate("userSettingsDialog", "Friday", nullptr));
        weekdayStartInput->setItemText(6, QCoreApplication::translate("userSettingsDialog", "Saturday", nullptr));

        rollingDateRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Rolling", nullptr));
        fixedDateRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Reset on day", nullptr));
        stdDrinkDefTitle->setText(QCoreApplication::translate("userSettingsDialog", "Std. Drink Definition:", nullptr));
        stdDrinkDefLabel->setText(QCoreApplication::translate("userSettingsDialog", "Oz. Alcohol", nullptr));
        label->setText(QCoreApplication::translate("userSettingsDialog", "* Standard drinks", nullptr));
        weeklyLimitGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Weekly Limit Standard", nullptr));
        niaaaStandardsRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "CDC/NIAAA", nullptr));
        customLimitLabel->setText(QCoreApplication::translate("userSettingsDialog", "Custom Limit* :", nullptr));
        customLimitRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Custom", nullptr));
        unitsGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Units", nullptr));
        metricRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Metric (ml)", nullptr));
        imperialRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Imperial (oz)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("userSettingsDialog", "Database Location", nullptr));
        dbLocationBrowseButton->setText(QCoreApplication::translate("userSettingsDialog", "Browse", nullptr));
        defaultLocationRadioBtn->setText(QCoreApplication::translate("userSettingsDialog", "Default location", nullptr));
        customLocationRadioBtn->setText(QCoreApplication::translate("userSettingsDialog", "Custom location", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userSettingsDialog: public Ui_userSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_SETTINGS_H
