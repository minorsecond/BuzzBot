/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_aboutDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *acknowledgementsLabel;
    QLabel *copyrightLabel;
    QLabel *versionLabel;
    QLabel *miniIcon;
    QFrame *line;
    QLabel *appNameLabel;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *aboutDialog)
    {
        if (aboutDialog->objectName().isEmpty())
            aboutDialog->setObjectName(QString::fromUtf8("aboutDialog"));
        aboutDialog->resize(237, 272);
        gridLayout = new QGridLayout(aboutDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        acknowledgementsLabel = new QLabel(aboutDialog);
        acknowledgementsLabel->setObjectName(QString::fromUtf8("acknowledgementsLabel"));
        acknowledgementsLabel->setWordWrap(true);

        gridLayout->addWidget(acknowledgementsLabel, 5, 0, 1, 1);

        copyrightLabel = new QLabel(aboutDialog);
        copyrightLabel->setObjectName(QString::fromUtf8("copyrightLabel"));

        gridLayout->addWidget(copyrightLabel, 4, 0, 1, 1);

        versionLabel = new QLabel(aboutDialog);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        versionLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout->addWidget(versionLabel, 2, 0, 1, 1);

        miniIcon = new QLabel(aboutDialog);
        miniIcon->setObjectName(QString::fromUtf8("miniIcon"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(miniIcon->sizePolicy().hasHeightForWidth());
        miniIcon->setSizePolicy(sizePolicy);
        miniIcon->setMaximumSize(QSize(500, 500));
        miniIcon->setPixmap(QPixmap(QString::fromUtf8(":/res/mini-icon.png")));
        miniIcon->setScaledContents(false);
        miniIcon->setAlignment(Qt::AlignCenter);
        miniIcon->setWordWrap(false);

        gridLayout->addWidget(miniIcon, 0, 0, 1, 1);

        line = new QFrame(aboutDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 0, 1, 1);

        appNameLabel = new QLabel(aboutDialog);
        appNameLabel->setObjectName(QString::fromUtf8("appNameLabel"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        appNameLabel->setFont(font);
        appNameLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout->addWidget(appNameLabel, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);


        retranslateUi(aboutDialog);

        QMetaObject::connectSlotsByName(aboutDialog);
    } // setupUi

    void retranslateUi(QDialog *aboutDialog)
    {
        aboutDialog->setWindowTitle(QCoreApplication::translate("aboutDialog", "About", nullptr));
        acknowledgementsLabel->setText(QCoreApplication::translate("aboutDialog", "This application makes use of Qt Open Source and is licensed under the LGPL.", nullptr));
        copyrightLabel->setText(QCoreApplication::translate("aboutDialog", "Ross Wardrup, 2020", nullptr));
        versionLabel->setText(QCoreApplication::translate("aboutDialog", "Version 0.8.0", nullptr));
        miniIcon->setText(QString());
        appNameLabel->setText(QCoreApplication::translate("aboutDialog", "BuzzBot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aboutDialog: public Ui_aboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
