/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QComboBox *filterCategoryInput;
    QComboBox *filterTextInput;
    QLabel *filterLabel;
    QLabel *filterCategoryLabel;
    QSpacerItem *verticalSpacer;
    QFrame *frame_3;
    QGridLayout *gridLayout_6;
    QComboBox *nameInput;
    QComboBox *subtypeInput;
    QDateEdit *drinkDateInput;
    QLabel *typeLabel;
    QLabel *breweryLabel;
    QGridLayout *gridLayout_3;
    QLabel *abvLabel;
    QDoubleSpinBox *ibuInput;
    QLabel *sizeLabel;
    QDoubleSpinBox *abvInput;
    QLabel *ratingLabel;
    QSpinBox *sizeInput;
    QSpacerItem *verticalSpacer_2;
    QLabel *ibuLabel;
    QSpinBox *ratingInput;
    QComboBox *typeInput;
    QLabel *drinkDateLabel;
    QComboBox *breweryInput;
    QLabel *nameLabel;
    QLabel *notesLabel;
    QTextEdit *notesInput;
    QLabel *subtypeLabel;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QLabel *favoriteBreweryOutput;
    QLabel *ozAlcoholConsumedOutput;
    QLabel *avgIbuDrinkOutput;
    QLabel *averageIbuDrinkLabel;
    QLabel *favoriteTypeOutput;
    QLabel *ozAlcoholConsumedLabel;
    QLabel *favoriteBeerLabel;
    QLabel *favoriteBreweryLabel;
    QLabel *ozAlcoholRemainingOutput;
    QLabel *ozAlcoholRemainingLabel;
    QLabel *favoriteTypeLabel;
    QLabel *avgAbvDrinkLabel;
    QLabel *avgAbvDrinkOutput;
    QSpacerItem *horizontalSpacer;
    QLabel *favoriteBeerOutput;
    QLabel *drinksThisWeekOutput;
    QLabel *drinksThisWeekLabel;
    QLabel *drinksLeftLabel;
    QLabel *drinksLeftOutput;
    QTableWidget *drinkLogTable;
    QLabel *drinkDataLabel;
    QFrame *frame_4;
    QGridLayout *gridLayout_2;
    QPushButton *clearFieldsButton;
    QPushButton *deleteRowButton;
    QPushButton *submitRowButton;
    QLabel *statsLabel;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1226, 670);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(0, 550));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        filterCategoryInput = new QComboBox(frame_2);
        filterCategoryInput->setObjectName(QString::fromUtf8("filterCategoryInput"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(filterCategoryInput->sizePolicy().hasHeightForWidth());
        filterCategoryInput->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(filterCategoryInput, 2, 0, 1, 1);

        filterTextInput = new QComboBox(frame_2);
        filterTextInput->setObjectName(QString::fromUtf8("filterTextInput"));
        sizePolicy1.setHeightForWidth(filterTextInput->sizePolicy().hasHeightForWidth());
        filterTextInput->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(filterTextInput, 2, 1, 1, 1);

        filterLabel = new QLabel(frame_2);
        filterLabel->setObjectName(QString::fromUtf8("filterLabel"));
        sizePolicy.setHeightForWidth(filterLabel->sizePolicy().hasHeightForWidth());
        filterLabel->setSizePolicy(sizePolicy);
        filterLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(filterLabel, 1, 1, 1, 1);

        filterCategoryLabel = new QLabel(frame_2);
        filterCategoryLabel->setObjectName(QString::fromUtf8("filterCategoryLabel"));
        sizePolicy.setHeightForWidth(filterCategoryLabel->sizePolicy().hasHeightForWidth());
        filterCategoryLabel->setSizePolicy(sizePolicy);
        filterCategoryLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(filterCategoryLabel, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);


        gridLayout_4->addWidget(frame_2, 9, 1, 2, 3);

        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_3->setLineWidth(1);
        gridLayout_6 = new QGridLayout(frame_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        nameInput = new QComboBox(frame_3);
        nameInput->setObjectName(QString::fromUtf8("nameInput"));
        sizePolicy1.setHeightForWidth(nameInput->sizePolicy().hasHeightForWidth());
        nameInput->setSizePolicy(sizePolicy1);
        nameInput->setEditable(true);

        gridLayout_6->addWidget(nameInput, 1, 1, 1, 1);

        subtypeInput = new QComboBox(frame_3);
        subtypeInput->setObjectName(QString::fromUtf8("subtypeInput"));
        subtypeInput->setEditable(true);

        gridLayout_6->addWidget(subtypeInput, 6, 1, 1, 1);

        drinkDateInput = new QDateEdit(frame_3);
        drinkDateInput->setObjectName(QString::fromUtf8("drinkDateInput"));
        sizePolicy1.setHeightForWidth(drinkDateInput->sizePolicy().hasHeightForWidth());
        drinkDateInput->setSizePolicy(sizePolicy1);
        drinkDateInput->setFocusPolicy(Qt::WheelFocus);
        drinkDateInput->setStyleSheet(QString::fromUtf8(""));
        drinkDateInput->setCalendarPopup(true);

        gridLayout_6->addWidget(drinkDateInput, 1, 0, 1, 1);

        typeLabel = new QLabel(frame_3);
        typeLabel->setObjectName(QString::fromUtf8("typeLabel"));
        sizePolicy.setHeightForWidth(typeLabel->sizePolicy().hasHeightForWidth());
        typeLabel->setSizePolicy(sizePolicy);
        typeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(typeLabel, 2, 1, 1, 1);

        breweryLabel = new QLabel(frame_3);
        breweryLabel->setObjectName(QString::fromUtf8("breweryLabel"));
        sizePolicy.setHeightForWidth(breweryLabel->sizePolicy().hasHeightForWidth());
        breweryLabel->setSizePolicy(sizePolicy);
        breweryLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(breweryLabel, 2, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        abvLabel = new QLabel(frame_3);
        abvLabel->setObjectName(QString::fromUtf8("abvLabel"));
        sizePolicy.setHeightForWidth(abvLabel->sizePolicy().hasHeightForWidth());
        abvLabel->setSizePolicy(sizePolicy);
        abvLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(abvLabel, 1, 0, 1, 1);

        ibuInput = new QDoubleSpinBox(frame_3);
        ibuInput->setObjectName(QString::fromUtf8("ibuInput"));
        sizePolicy1.setHeightForWidth(ibuInput->sizePolicy().hasHeightForWidth());
        ibuInput->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(ibuInput, 2, 1, 1, 1);

        sizeLabel = new QLabel(frame_3);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));
        sizePolicy.setHeightForWidth(sizeLabel->sizePolicy().hasHeightForWidth());
        sizeLabel->setSizePolicy(sizePolicy);
        sizeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(sizeLabel, 1, 3, 1, 1);

        abvInput = new QDoubleSpinBox(frame_3);
        abvInput->setObjectName(QString::fromUtf8("abvInput"));
        sizePolicy1.setHeightForWidth(abvInput->sizePolicy().hasHeightForWidth());
        abvInput->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(abvInput, 2, 0, 1, 1);

        ratingLabel = new QLabel(frame_3);
        ratingLabel->setObjectName(QString::fromUtf8("ratingLabel"));
        sizePolicy.setHeightForWidth(ratingLabel->sizePolicy().hasHeightForWidth());
        ratingLabel->setSizePolicy(sizePolicy);
        ratingLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(ratingLabel, 1, 2, 1, 1);

        sizeInput = new QSpinBox(frame_3);
        sizeInput->setObjectName(QString::fromUtf8("sizeInput"));
        sizePolicy1.setHeightForWidth(sizeInput->sizePolicy().hasHeightForWidth());
        sizeInput->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(sizeInput, 2, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 0, 1, 1);

        ibuLabel = new QLabel(frame_3);
        ibuLabel->setObjectName(QString::fromUtf8("ibuLabel"));
        sizePolicy.setHeightForWidth(ibuLabel->sizePolicy().hasHeightForWidth());
        ibuLabel->setSizePolicy(sizePolicy);
        ibuLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(ibuLabel, 1, 1, 1, 1);

        ratingInput = new QSpinBox(frame_3);
        ratingInput->setObjectName(QString::fromUtf8("ratingInput"));
        sizePolicy1.setHeightForWidth(ratingInput->sizePolicy().hasHeightForWidth());
        ratingInput->setSizePolicy(sizePolicy1);
        ratingInput->setMaximum(10);

        gridLayout_3->addWidget(ratingInput, 2, 2, 1, 1);


        gridLayout_6->addLayout(gridLayout_3, 7, 1, 3, 1);

        typeInput = new QComboBox(frame_3);
        typeInput->setObjectName(QString::fromUtf8("typeInput"));
        sizePolicy1.setHeightForWidth(typeInput->sizePolicy().hasHeightForWidth());
        typeInput->setSizePolicy(sizePolicy1);
        typeInput->setEditable(true);

        gridLayout_6->addWidget(typeInput, 3, 1, 1, 1);

        drinkDateLabel = new QLabel(frame_3);
        drinkDateLabel->setObjectName(QString::fromUtf8("drinkDateLabel"));
        sizePolicy.setHeightForWidth(drinkDateLabel->sizePolicy().hasHeightForWidth());
        drinkDateLabel->setSizePolicy(sizePolicy);
        drinkDateLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(drinkDateLabel, 0, 0, 1, 1);

        breweryInput = new QComboBox(frame_3);
        breweryInput->setObjectName(QString::fromUtf8("breweryInput"));
        sizePolicy1.setHeightForWidth(breweryInput->sizePolicy().hasHeightForWidth());
        breweryInput->setSizePolicy(sizePolicy1);
        breweryInput->setEditable(true);

        gridLayout_6->addWidget(breweryInput, 3, 0, 1, 1);

        nameLabel = new QLabel(frame_3);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        sizePolicy.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy);
        nameLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(nameLabel, 0, 1, 1, 1);

        notesLabel = new QLabel(frame_3);
        notesLabel->setObjectName(QString::fromUtf8("notesLabel"));
        sizePolicy.setHeightForWidth(notesLabel->sizePolicy().hasHeightForWidth());
        notesLabel->setSizePolicy(sizePolicy);
        notesLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(notesLabel, 5, 0, 1, 1);

        notesInput = new QTextEdit(frame_3);
        notesInput->setObjectName(QString::fromUtf8("notesInput"));
        sizePolicy.setHeightForWidth(notesInput->sizePolicy().hasHeightForWidth());
        notesInput->setSizePolicy(sizePolicy);
        notesInput->setFocusPolicy(Qt::ClickFocus);

        gridLayout_6->addWidget(notesInput, 6, 0, 4, 1);

        subtypeLabel = new QLabel(frame_3);
        subtypeLabel->setObjectName(QString::fromUtf8("subtypeLabel"));
        subtypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(subtypeLabel, 5, 1, 1, 1);


        gridLayout_4->addWidget(frame_3, 2, 0, 7, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        favoriteBreweryOutput = new QLabel(frame);
        favoriteBreweryOutput->setObjectName(QString::fromUtf8("favoriteBreweryOutput"));
        sizePolicy.setHeightForWidth(favoriteBreweryOutput->sizePolicy().hasHeightForWidth());
        favoriteBreweryOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBreweryOutput, 4, 2, 1, 1);

        ozAlcoholConsumedOutput = new QLabel(frame);
        ozAlcoholConsumedOutput->setObjectName(QString::fromUtf8("ozAlcoholConsumedOutput"));
        sizePolicy.setHeightForWidth(ozAlcoholConsumedOutput->sizePolicy().hasHeightForWidth());
        ozAlcoholConsumedOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(ozAlcoholConsumedOutput, 2, 2, 1, 1);

        avgIbuDrinkOutput = new QLabel(frame);
        avgIbuDrinkOutput->setObjectName(QString::fromUtf8("avgIbuDrinkOutput"));
        sizePolicy.setHeightForWidth(avgIbuDrinkOutput->sizePolicy().hasHeightForWidth());
        avgIbuDrinkOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgIbuDrinkOutput, 9, 2, 1, 1);

        averageIbuDrinkLabel = new QLabel(frame);
        averageIbuDrinkLabel->setObjectName(QString::fromUtf8("averageIbuDrinkLabel"));
        sizePolicy.setHeightForWidth(averageIbuDrinkLabel->sizePolicy().hasHeightForWidth());
        averageIbuDrinkLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(averageIbuDrinkLabel, 9, 0, 1, 1);

        favoriteTypeOutput = new QLabel(frame);
        favoriteTypeOutput->setObjectName(QString::fromUtf8("favoriteTypeOutput"));

        gridLayout_5->addWidget(favoriteTypeOutput, 6, 2, 1, 1);

        ozAlcoholConsumedLabel = new QLabel(frame);
        ozAlcoholConsumedLabel->setObjectName(QString::fromUtf8("ozAlcoholConsumedLabel"));
        sizePolicy.setHeightForWidth(ozAlcoholConsumedLabel->sizePolicy().hasHeightForWidth());
        ozAlcoholConsumedLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(ozAlcoholConsumedLabel, 2, 0, 1, 1);

        favoriteBeerLabel = new QLabel(frame);
        favoriteBeerLabel->setObjectName(QString::fromUtf8("favoriteBeerLabel"));
        sizePolicy.setHeightForWidth(favoriteBeerLabel->sizePolicy().hasHeightForWidth());
        favoriteBeerLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBeerLabel, 5, 0, 1, 1);

        favoriteBreweryLabel = new QLabel(frame);
        favoriteBreweryLabel->setObjectName(QString::fromUtf8("favoriteBreweryLabel"));
        sizePolicy.setHeightForWidth(favoriteBreweryLabel->sizePolicy().hasHeightForWidth());
        favoriteBreweryLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBreweryLabel, 4, 0, 1, 1);

        ozAlcoholRemainingOutput = new QLabel(frame);
        ozAlcoholRemainingOutput->setObjectName(QString::fromUtf8("ozAlcoholRemainingOutput"));
        sizePolicy.setHeightForWidth(ozAlcoholRemainingOutput->sizePolicy().hasHeightForWidth());
        ozAlcoholRemainingOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(ozAlcoholRemainingOutput, 3, 2, 1, 1);

        ozAlcoholRemainingLabel = new QLabel(frame);
        ozAlcoholRemainingLabel->setObjectName(QString::fromUtf8("ozAlcoholRemainingLabel"));
        sizePolicy.setHeightForWidth(ozAlcoholRemainingLabel->sizePolicy().hasHeightForWidth());
        ozAlcoholRemainingLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(ozAlcoholRemainingLabel, 3, 0, 1, 1);

        favoriteTypeLabel = new QLabel(frame);
        favoriteTypeLabel->setObjectName(QString::fromUtf8("favoriteTypeLabel"));

        gridLayout_5->addWidget(favoriteTypeLabel, 6, 0, 1, 1);

        avgAbvDrinkLabel = new QLabel(frame);
        avgAbvDrinkLabel->setObjectName(QString::fromUtf8("avgAbvDrinkLabel"));
        sizePolicy.setHeightForWidth(avgAbvDrinkLabel->sizePolicy().hasHeightForWidth());
        avgAbvDrinkLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgAbvDrinkLabel, 8, 0, 1, 1);

        avgAbvDrinkOutput = new QLabel(frame);
        avgAbvDrinkOutput->setObjectName(QString::fromUtf8("avgAbvDrinkOutput"));
        sizePolicy.setHeightForWidth(avgAbvDrinkOutput->sizePolicy().hasHeightForWidth());
        avgAbvDrinkOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgAbvDrinkOutput, 8, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 4, 3, 1, 1);

        favoriteBeerOutput = new QLabel(frame);
        favoriteBeerOutput->setObjectName(QString::fromUtf8("favoriteBeerOutput"));
        sizePolicy.setHeightForWidth(favoriteBeerOutput->sizePolicy().hasHeightForWidth());
        favoriteBeerOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBeerOutput, 5, 2, 1, 1);

        drinksThisWeekOutput = new QLabel(frame);
        drinksThisWeekOutput->setObjectName(QString::fromUtf8("drinksThisWeekOutput"));
        sizePolicy.setHeightForWidth(drinksThisWeekOutput->sizePolicy().hasHeightForWidth());
        drinksThisWeekOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksThisWeekOutput, 0, 2, 1, 1);

        drinksThisWeekLabel = new QLabel(frame);
        drinksThisWeekLabel->setObjectName(QString::fromUtf8("drinksThisWeekLabel"));
        sizePolicy.setHeightForWidth(drinksThisWeekLabel->sizePolicy().hasHeightForWidth());
        drinksThisWeekLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksThisWeekLabel, 0, 0, 1, 1);

        drinksLeftLabel = new QLabel(frame);
        drinksLeftLabel->setObjectName(QString::fromUtf8("drinksLeftLabel"));
        sizePolicy.setHeightForWidth(drinksLeftLabel->sizePolicy().hasHeightForWidth());
        drinksLeftLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksLeftLabel, 1, 0, 1, 1);

        drinksLeftOutput = new QLabel(frame);
        drinksLeftOutput->setObjectName(QString::fromUtf8("drinksLeftOutput"));
        sizePolicy.setHeightForWidth(drinksLeftOutput->sizePolicy().hasHeightForWidth());
        drinksLeftOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksLeftOutput, 1, 2, 1, 1);


        gridLayout_4->addWidget(frame, 2, 1, 7, 3);

        drinkLogTable = new QTableWidget(centralwidget);
        if (drinkLogTable->columnCount() < 11)
            drinkLogTable->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        if (drinkLogTable->rowCount() < 1)
            drinkLogTable->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        drinkLogTable->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 5, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 6, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 7, __qtablewidgetitem18);
        drinkLogTable->setObjectName(QString::fromUtf8("drinkLogTable"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(drinkLogTable->sizePolicy().hasHeightForWidth());
        drinkLogTable->setSizePolicy(sizePolicy2);
        drinkLogTable->setFocusPolicy(Qt::ClickFocus);

        gridLayout_4->addWidget(drinkLogTable, 11, 0, 12, 4);

        drinkDataLabel = new QLabel(centralwidget);
        drinkDataLabel->setObjectName(QString::fromUtf8("drinkDataLabel"));
        sizePolicy.setHeightForWidth(drinkDataLabel->sizePolicy().hasHeightForWidth());
        drinkDataLabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        drinkDataLabel->setFont(font);
        drinkDataLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(drinkDataLabel, 0, 0, 1, 1);

        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        clearFieldsButton = new QPushButton(frame_4);
        clearFieldsButton->setObjectName(QString::fromUtf8("clearFieldsButton"));
        sizePolicy1.setHeightForWidth(clearFieldsButton->sizePolicy().hasHeightForWidth());
        clearFieldsButton->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(clearFieldsButton, 0, 2, 1, 1);

        deleteRowButton = new QPushButton(frame_4);
        deleteRowButton->setObjectName(QString::fromUtf8("deleteRowButton"));
        sizePolicy1.setHeightForWidth(deleteRowButton->sizePolicy().hasHeightForWidth());
        deleteRowButton->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(deleteRowButton, 0, 0, 1, 1);

        submitRowButton = new QPushButton(frame_4);
        submitRowButton->setObjectName(QString::fromUtf8("submitRowButton"));
        sizePolicy1.setHeightForWidth(submitRowButton->sizePolicy().hasHeightForWidth());
        submitRowButton->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(submitRowButton, 0, 3, 1, 1);


        gridLayout_4->addWidget(frame_4, 9, 0, 2, 1);

        statsLabel = new QLabel(centralwidget);
        statsLabel->setObjectName(QString::fromUtf8("statsLabel"));
        sizePolicy.setHeightForWidth(statsLabel->sizePolicy().hasHeightForWidth());
        statsLabel->setSizePolicy(sizePolicy);
        statsLabel->setFont(font);
        statsLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(statsLabel, 0, 1, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1226, 22));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(drinkDateInput, nameInput);
        QWidget::setTabOrder(nameInput, breweryInput);
        QWidget::setTabOrder(breweryInput, typeInput);
        QWidget::setTabOrder(typeInput, subtypeInput);
        QWidget::setTabOrder(subtypeInput, abvInput);
        QWidget::setTabOrder(abvInput, ibuInput);
        QWidget::setTabOrder(ibuInput, ratingInput);
        QWidget::setTabOrder(ratingInput, sizeInput);
        QWidget::setTabOrder(sizeInput, filterCategoryInput);
        QWidget::setTabOrder(filterCategoryInput, filterTextInput);
        QWidget::setTabOrder(filterTextInput, deleteRowButton);
        QWidget::setTabOrder(deleteRowButton, clearFieldsButton);
        QWidget::setTabOrder(clearFieldsButton, submitRowButton);
        QWidget::setTabOrder(submitRowButton, drinkLogTable);
        QWidget::setTabOrder(drinkLogTable, notesInput);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BuzzBot", nullptr));
        filterLabel->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        filterCategoryLabel->setText(QCoreApplication::translate("MainWindow", "Filter Category", nullptr));
        drinkDateInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "MMM/dd/yyyy", nullptr));
        typeLabel->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        breweryLabel->setText(QCoreApplication::translate("MainWindow", "Brewery", nullptr));
        abvLabel->setText(QCoreApplication::translate("MainWindow", "ABV", nullptr));
        sizeLabel->setText(QCoreApplication::translate("MainWindow", "Size (oz)", nullptr));
        ratingLabel->setText(QCoreApplication::translate("MainWindow", "Rating", nullptr));
        ibuLabel->setText(QCoreApplication::translate("MainWindow", "IBU", nullptr));
        drinkDateLabel->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        nameLabel->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        notesLabel->setText(QCoreApplication::translate("MainWindow", "Notes", nullptr));
        subtypeLabel->setText(QCoreApplication::translate("MainWindow", "Subtype", nullptr));
        favoriteBreweryOutput->setText(QCoreApplication::translate("MainWindow", "Roughtail Brewing Co.", nullptr));
        ozAlcoholConsumedOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        avgIbuDrinkOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        averageIbuDrinkLabel->setText(QCoreApplication::translate("MainWindow", "Average IBU per drink:", nullptr));
        favoriteTypeOutput->setText(QCoreApplication::translate("MainWindow", "IPA", nullptr));
        ozAlcoholConsumedLabel->setText(QCoreApplication::translate("MainWindow", "Oz. alcohol consumed:", nullptr));
        favoriteBeerLabel->setText(QCoreApplication::translate("MainWindow", "Favorite beer:", nullptr));
        favoriteBreweryLabel->setText(QCoreApplication::translate("MainWindow", "Favorite brewery:", nullptr));
        ozAlcoholRemainingOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        ozAlcoholRemainingLabel->setText(QCoreApplication::translate("MainWindow", "Oz. alcohol remaining:", nullptr));
        favoriteTypeLabel->setText(QCoreApplication::translate("MainWindow", "Favorite type:", nullptr));
        avgAbvDrinkLabel->setText(QCoreApplication::translate("MainWindow", "Average ABV per drink:", nullptr));
        avgAbvDrinkOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        favoriteBeerOutput->setText(QCoreApplication::translate("MainWindow", "Everything Rhymes with Orange", nullptr));
        drinksThisWeekOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        drinksThisWeekLabel->setText(QCoreApplication::translate("MainWindow", "Std. drinks this week:", nullptr));
        drinksLeftLabel->setText(QCoreApplication::translate("MainWindow", "Std. drinks remaining:", nullptr));
        drinksLeftOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem = drinkLogTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = drinkLogTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = drinkLogTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = drinkLogTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Subtype", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = drinkLogTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Brewery", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = drinkLogTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "ABV", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = drinkLogTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "IBU", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = drinkLogTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = drinkLogTable->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Rating", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = drinkLogTable->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = drinkLogTable->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Timestamp", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = drinkLogTable->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "1", nullptr));

        const bool __sortingEnabled = drinkLogTable->isSortingEnabled();
        drinkLogTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem12 = drinkLogTable->item(0, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "09/07/2020", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = drinkLogTable->item(0, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Everything Rhymes with Orange", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = drinkLogTable->item(0, 2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "IPA", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = drinkLogTable->item(0, 4);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Roughtail Brewing", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = drinkLogTable->item(0, 5);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "8.0", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = drinkLogTable->item(0, 6);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "65", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = drinkLogTable->item(0, 7);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        drinkLogTable->setSortingEnabled(__sortingEnabled);

        drinkDataLabel->setText(QCoreApplication::translate("MainWindow", "Drink Data", nullptr));
        clearFieldsButton->setText(QCoreApplication::translate("MainWindow", "Clear Selections", nullptr));
        deleteRowButton->setText(QCoreApplication::translate("MainWindow", "Delete Row", nullptr));
        submitRowButton->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        statsLabel->setText(QCoreApplication::translate("MainWindow", "Stats", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
