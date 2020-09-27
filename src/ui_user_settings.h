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

QT_BEGIN_NAMESPACE

class Ui_userSettingsDialog
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QGroupBox *dateCalculationGroup;
    QGridLayout *gridLayout;
    QComboBox *weekdayStartInput;
    QLabel *weekdayStartLabel;
    QRadioButton *fixedDateRadioButton;
    QRadioButton *rollingDateRadioButton;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *userSettingsButtonBox;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QGroupBox *sexGroup;
    QGridLayout *gridLayout_4;
    QRadioButton *maleSelection;
    QRadioButton *femaleSelection;

    void setupUi(QDialog *userSettingsDialog)
    {
        if (userSettingsDialog->objectName().isEmpty())
            userSettingsDialog->setObjectName(QString::fromUtf8("userSettingsDialog"));
        userSettingsDialog->resize(452, 204);
        userSettingsDialog->setModal(true);
        gridLayout_2 = new QGridLayout(userSettingsDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
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

        userSettingsButtonBox = new QDialogButtonBox(userSettingsDialog);
        userSettingsButtonBox->setObjectName(QString::fromUtf8("userSettingsButtonBox"));
        userSettingsButtonBox->setOrientation(Qt::Vertical);
        userSettingsButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(userSettingsButtonBox, 0, 2, 1, 1);

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


        retranslateUi(userSettingsDialog);
        QObject::connect(userSettingsButtonBox, SIGNAL(accepted()), userSettingsDialog, SLOT(accept()));
        QObject::connect(userSettingsButtonBox, SIGNAL(rejected()), userSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(userSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *userSettingsDialog)
    {
        userSettingsDialog->setWindowTitle(QCoreApplication::translate("userSettingsDialog", "User Settings", nullptr));
        dateCalculationGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Date Calculation", nullptr));
        weekdayStartInput->setItemText(0, QCoreApplication::translate("userSettingsDialog", "Sunday", nullptr));
        weekdayStartInput->setItemText(1, QCoreApplication::translate("userSettingsDialog", "Monday", nullptr));
        weekdayStartInput->setItemText(2, QCoreApplication::translate("userSettingsDialog", "Tuesday", nullptr));
        weekdayStartInput->setItemText(3, QCoreApplication::translate("userSettingsDialog", "Wednesday", nullptr));
        weekdayStartInput->setItemText(4, QCoreApplication::translate("userSettingsDialog", "Thursday", nullptr));
        weekdayStartInput->setItemText(5, QCoreApplication::translate("userSettingsDialog", "Friday", nullptr));
        weekdayStartInput->setItemText(6, QCoreApplication::translate("userSettingsDialog", "Saturday", nullptr));

        weekdayStartLabel->setText(QCoreApplication::translate("userSettingsDialog", "Week begins on:", nullptr));
        fixedDateRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Fixed date", nullptr));
        rollingDateRadioButton->setText(QCoreApplication::translate("userSettingsDialog", "Rolling date", nullptr));
        sexGroup->setTitle(QCoreApplication::translate("userSettingsDialog", "Sex", nullptr));
        maleSelection->setText(QCoreApplication::translate("userSettingsDialog", "Male", nullptr));
        femaleSelection->setText(QCoreApplication::translate("userSettingsDialog", "Female", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userSettingsDialog: public Ui_userSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_SETTINGS_H
