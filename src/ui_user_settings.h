/********************************************************************************
** Form generated from reading UI file 'user_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_SETTINGS_H
#define UI_USER_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_userSettingsDialog
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QGroupBox *sexGroup;
    QGridLayout *gridLayout_4;
    QRadioButton *maleSelection;
    QRadioButton *femaleSelection;
    QDialogButtonBox *userSettingsButtonBox;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QGroupBox *dateCalculationGroup;
    QGridLayout *gridLayout;
    QComboBox *weekdayStartInput;
    QLabel *weekdayStartLabel;
    QRadioButton *fixedDateRadioButton;
    QRadioButton *rollingDateRadioButton;
    QSpacerItem *verticalSpacer_2;
    QFrame *weeklyLimitFrame;
    QGridLayout *gridLayout_7;
    QGroupBox *weeklyLimitGroup;
    QGridLayout *gridLayout_6;
    QRadioButton *customLimitRadioButton;
    QSpacerItem *verticalSpacer_3;
    QRadioButton *niaaaStandardsRadioButton;
    QLabel *label;
    QSpinBox *spinBox;

    void setupUi(QDialog *userSettingsDialog)
    {
        if (userSettingsDialog->objectName().isEmpty())
            userSettingsDialog->setObjectName(QString::fromUtf8("userSettingsDialog"));
        userSettingsDialog->resize(609, 224);
        userSettingsDialog->setModal(true);
        gridLayout_2 = new QGridLayout(userSettingsDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
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

        gridLayout_4->addWidget(maleSelection, 0, 0, 1, 1);

        femaleSelection = new QRadioButton(sexGroup);
        femaleSelection->setObjectName(QString::fromUtf8("femaleSelection"));

        gridLayout_4->addWidget(femaleSelection, 1, 0, 1, 1);


        gridLayout_5->addWidget(sexGroup, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);

        userSettingsButtonBox = new QDialogButtonBox(userSettingsDialog);
        userSettingsButtonBox->setObjectName(QString::fromUtf8("userSettingsButtonBox"));
        userSettingsButtonBox->setOrientation(Qt::Vertical);
        userSettingsButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(userSettingsButtonBox, 0, 3, 1, 1);

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
        weekdayStartInput = new QComboBox(dateCalculationGroup);
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->addItem(QString());
        weekdayStartInput->setObjectName(QString::fromUtf8("weekdayStartInput"));

        gridLayout->addWidget(weekdayStartInput, 4, 0, 1, 1);

        weekdayStartLabel = new QLabel(dateCalculationGroup);
        weekdayStartLabel->setObjectName(QString::fromUtf8("weekdayStartLabel"));

        gridLayout->addWidget(weekdayStartLabel, 3, 0, 1, 1);

        fixedDateRadioButton = new QRadioButton(dateCalculationGroup);
        fixedDateRadioButton->setObjectName(QString::fromUtf8("fixedDateRadioButton"));

        gridLayout->addWidget(fixedDateRadioButton, 1, 0, 1, 1);

        rollingDateRadioButton = new QRadioButton(dateCalculationGroup);
        rollingDateRadioButton->setObjectName(QString::fromUtf8("rollingDateRadioButton"));
        rollingDateRadioButton->setChecked(true);

        gridLayout->addWidget(rollingDateRadioButton, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 1);


        gridLayout_3->addWidget(dateCalculationGroup, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_2, 0, 1, 1, 1);

        weeklyLimitFrame = new QFrame(userSettingsDialog);
        weeklyLimitFrame->setObjectName(QString::fromUtf8("weeklyLimitFrame"));
        weeklyLimitFrame->setFrameShape(QFrame::StyledPanel);
        weeklyLimitFrame->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(weeklyLimitFrame);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        weeklyLimitGroup = new QGroupBox(weeklyLimitFrame);
        weeklyLimitGroup->setObjectName(QString::fromUtf8("weeklyLimitGroup"));
        weeklyLimitGroup->setToolTipDuration(-1);
        weeklyLimitGroup->setAlignment(Qt::AlignCenter);
        weeklyLimitGroup->setFlat(true);
        gridLayout_6 = new QGridLayout(weeklyLimitGroup);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        customLimitRadioButton = new QRadioButton(weeklyLimitGroup);
        customLimitRadioButton->setObjectName(QString::fromUtf8("customLimitRadioButton"));

        gridLayout_6->addWidget(customLimitRadioButton, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_3, 2, 0, 1, 1);

        niaaaStandardsRadioButton = new QRadioButton(weeklyLimitGroup);
        niaaaStandardsRadioButton->setObjectName(QString::fromUtf8("niaaaStandardsRadioButton"));

        gridLayout_6->addWidget(niaaaStandardsRadioButton, 0, 0, 1, 2);

        label = new QLabel(weeklyLimitGroup);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_6->addWidget(label, 4, 0, 1, 2);

        spinBox = new QSpinBox(weeklyLimitGroup);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy);
        spinBox->setMinimumSize(QSize(0, 25));

        gridLayout_6->addWidget(spinBox, 5, 0, 1, 1);


        gridLayout_7->addWidget(weeklyLimitGroup, 0, 0, 1, 1);


        gridLayout_2->addWidget(weeklyLimitFrame, 0, 2, 1, 1);


        retranslateUi(userSettingsDialog);
        QObject::connect(userSettingsButtonBox, SIGNAL(accepted()), userSettingsDialog, SLOT(accept()));
        QObject::connect(userSettingsButtonBox, SIGNAL(rejected()), userSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(userSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *userSettingsDialog)
    {
        userSettingsDialog->setWindowTitle(QCoreApplication::translate("userSettingsDialog", "User Settings", nullptr));
        sexGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Sex", nullptr));
        maleSelection->setText(QCoreApplication::translate("userSettingsDialog", "Male", nullptr));
        femaleSelection->setText(QCoreApplication::translate("userSettingsDialog", "Female", nullptr));
        dateCalculationGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Date Calculation", nullptr));
        weekdayStartInput->setItemText(0, QCoreApplication::translate("userSettingsDialog", "Sunday", nullptr));
        weekdayStartInput->setItemText(1, QCoreApplication::translate("userSettingsDialog", "Monday", nullptr));
        weekdayStartInput->setItemText(2, QCoreApplication::translate("userSettingsDialog", "Tuesday", nullptr));
        weekdayStartInput->setItemText(3, QCoreApplication::translate("userSettingsDialog", "Wednesday", nullptr));
        weekdayStartInput->setItemText(4, QCoreApplication::translate("userSettingsDialog", "Thursday", nullptr));
        weekdayStartInput->setItemText(5, QCoreApplication::translate("userSettingsDialog", "Friday", nullptr));
        weekdayStartInput->setItemText(6, QCoreApplication::translate("userSettingsDialog", "Saturday", nullptr));

        weekdayStartLabel->setText(QCoreApplication::translate("userSettingsDialog", "Reset stats on:", nullptr));
        fixedDateRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Reset on day", nullptr));
        rollingDateRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Rolling", nullptr));
        weeklyLimitGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Weekly Limit Standard", nullptr));
        customLimitRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Custom", nullptr));
        niaaaStandardsRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "NIAAA", nullptr));
        label->setText(QCoreApplication::translate("userSettingsDialog", "Custom Limit:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userSettingsDialog: public Ui_userSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_SETTINGS_H
