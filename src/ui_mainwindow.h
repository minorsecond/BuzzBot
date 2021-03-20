/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
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
#include <QtWidgets/QTabWidget>
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
    QTableWidget *drinkLogTable;
    QLabel *statsLabel;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QLabel *drinksThisWeekOutput;
    QLabel *favoriteBreweryOutput;
    QLabel *ozAlcoholConsumedOutput;
    QSpacerItem *horizontalSpacer;
    QLabel *favoriteBeerLabel;
    QLabel *favoriteBeerOutput;
    QLabel *drinksLeftLabel;
    QLabel *averageIbuDrinkLabel;
    QLabel *ozAlcoholRemainingLabel;
    QLabel *avgAbvDrinkLabel;
    QLabel *drinksThisWeekLabel;
    QLabel *avgIbuDrinkOutput;
    QLabel *favoriteTypeOutput;
    QLabel *favoriteTypeLabel;
    QLabel *avgAbvDrinkOutput;
    QLabel *favoriteBreweryLabel;
    QLabel *ozAlcoholRemainingOutput;
    QLabel *ozAlcoholConsumedLabel;
    QLabel *drinksLeftOutput;
    QLabel *stdDrinksTodayLabel;
    QLabel *stdDrinksTodayOutput;
    QLabel *drinkDataLabel;
    QFrame *frame_4;
    QGridLayout *gridLayout_2;
    QPushButton *clearFieldsButton;
    QPushButton *deleteRowButton;
    QPushButton *submitRowButton;
    QTabWidget *tabWidget;
    QWidget *beerTab;
    QGridLayout *gridLayout_7;
    QLabel *drinkDateLabel;
    QLabel *beerNameLabel;
    QDateEdit *beerDateInput;
    QComboBox *beerNameInput;
    QLabel *beerBreweryLabel;
    QLabel *beerTypeLabel;
    QComboBox *beerBreweryInput;
    QComboBox *beerTypeInput;
    QLabel *beerNotesLabel;
    QLabel *beerSubtypeLabel;
    QTextEdit *beerNotesInput;
    QComboBox *beerSubtypeInput;
    QGridLayout *gridLayout_3;
    QSpinBox *beerRatingInput;
    QLabel *beerIbuLabel;
    QLabel *beerSizeLabel;
    QDoubleSpinBox *beerIbuInput;
    QLabel *beerRatingLabel;
    QLabel *beerAbvLabel;
    QDoubleSpinBox *beerAbvInput;
    QSpacerItem *verticalSpacer_2;
    QDoubleSpinBox *beerSizeInput;
    QWidget *liquorTab;
    QGridLayout *gridLayout_8;
    QLabel *liquorTypeLabel;
    QLabel *liquorDistillerLabel;
    QLabel *liquorDateInputLabel;
    QLabel *liquorSubtypeLabel;
    QGridLayout *gridLayout_6;
    QLabel *liquorSizeLabel;
    QDoubleSpinBox *liquorAbvInput;
    QLabel *liquorAbvLabel;
    QLabel *liquorRatingLabel;
    QSpinBox *liquorRatingInput;
    QSpacerItem *verticalSpacer_3;
    QDoubleSpinBox *liquorSizeInput;
    QComboBox *liquorDistillerInput;
    QLabel *liquorNotesLabel;
    QComboBox *liquorNameInput;
    QDateEdit *liquorDateInput;
    QComboBox *liquorTypeInput;
    QLabel *liquorNameInputLabel;
    QComboBox *liquorSubtypeInput;
    QTextEdit *liquorNotesInput;
    QWidget *wineTab;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_9;
    QLabel *wineSizeLabel;
    QLabel *wineVintageLabel;
    QSpinBox *wineVintage;
    QLabel *wineRatingLabel;
    QSpinBox *wineRatingInput;
    QDoubleSpinBox *wineAbvInput;
    QLabel *wineAbvLabel;
    QSpacerItem *verticalSpacer_4;
    QDoubleSpinBox *wineSizeInput;
    QDateEdit *wineDateInput;
    QLabel *wineDateLabel;
    QLabel *wineNotesLabel;
    QLabel *wineNameLabel;
    QComboBox *wineTypeInput;
    QComboBox *wineNameInput;
    QComboBox *wineryInput;
    QLabel *wineTypeLabel;
    QLabel *wineSubtypeLabel;
    QLabel *wineryLabel;
    QComboBox *wineSubtypeInput;
    QTextEdit *wineNotesInput;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1006, 694);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(1006, 670));
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


        gridLayout_4->addWidget(frame_2, 4, 1, 2, 3);

        drinkLogTable = new QTableWidget(centralwidget);
        if (drinkLogTable->columnCount() < 12)
            drinkLogTable->setColumnCount(12);
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
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        if (drinkLogTable->rowCount() < 1)
            drinkLogTable->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        drinkLogTable->setVerticalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 6, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 7, __qtablewidgetitem19);
        drinkLogTable->setObjectName(QString::fromUtf8("drinkLogTable"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(drinkLogTable->sizePolicy().hasHeightForWidth());
        drinkLogTable->setSizePolicy(sizePolicy2);
        drinkLogTable->setFocusPolicy(Qt::ClickFocus);

        gridLayout_4->addWidget(drinkLogTable, 6, 0, 12, 4);

        statsLabel = new QLabel(centralwidget);
        statsLabel->setObjectName(QString::fromUtf8("statsLabel"));
        sizePolicy.setHeightForWidth(statsLabel->sizePolicy().hasHeightForWidth());
        statsLabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        statsLabel->setFont(font);
        statsLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(statsLabel, 0, 1, 1, 3);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        drinksThisWeekOutput = new QLabel(frame);
        drinksThisWeekOutput->setObjectName(QString::fromUtf8("drinksThisWeekOutput"));
        sizePolicy.setHeightForWidth(drinksThisWeekOutput->sizePolicy().hasHeightForWidth());
        drinksThisWeekOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksThisWeekOutput, 1, 2, 1, 1);

        favoriteBreweryOutput = new QLabel(frame);
        favoriteBreweryOutput->setObjectName(QString::fromUtf8("favoriteBreweryOutput"));
        sizePolicy.setHeightForWidth(favoriteBreweryOutput->sizePolicy().hasHeightForWidth());
        favoriteBreweryOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBreweryOutput, 5, 2, 1, 1);

        ozAlcoholConsumedOutput = new QLabel(frame);
        ozAlcoholConsumedOutput->setObjectName(QString::fromUtf8("ozAlcoholConsumedOutput"));
        sizePolicy.setHeightForWidth(ozAlcoholConsumedOutput->sizePolicy().hasHeightForWidth());
        ozAlcoholConsumedOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(ozAlcoholConsumedOutput, 3, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 5, 3, 1, 1);

        favoriteBeerLabel = new QLabel(frame);
        favoriteBeerLabel->setObjectName(QString::fromUtf8("favoriteBeerLabel"));
        sizePolicy.setHeightForWidth(favoriteBeerLabel->sizePolicy().hasHeightForWidth());
        favoriteBeerLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBeerLabel, 6, 0, 1, 1);

        favoriteBeerOutput = new QLabel(frame);
        favoriteBeerOutput->setObjectName(QString::fromUtf8("favoriteBeerOutput"));
        sizePolicy.setHeightForWidth(favoriteBeerOutput->sizePolicy().hasHeightForWidth());
        favoriteBeerOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBeerOutput, 6, 2, 1, 1);

        drinksLeftLabel = new QLabel(frame);
        drinksLeftLabel->setObjectName(QString::fromUtf8("drinksLeftLabel"));
        sizePolicy.setHeightForWidth(drinksLeftLabel->sizePolicy().hasHeightForWidth());
        drinksLeftLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksLeftLabel, 2, 0, 1, 1);

        averageIbuDrinkLabel = new QLabel(frame);
        averageIbuDrinkLabel->setObjectName(QString::fromUtf8("averageIbuDrinkLabel"));
        sizePolicy.setHeightForWidth(averageIbuDrinkLabel->sizePolicy().hasHeightForWidth());
        averageIbuDrinkLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(averageIbuDrinkLabel, 10, 0, 1, 1);

        ozAlcoholRemainingLabel = new QLabel(frame);
        ozAlcoholRemainingLabel->setObjectName(QString::fromUtf8("ozAlcoholRemainingLabel"));
        sizePolicy.setHeightForWidth(ozAlcoholRemainingLabel->sizePolicy().hasHeightForWidth());
        ozAlcoholRemainingLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(ozAlcoholRemainingLabel, 4, 0, 1, 1);

        avgAbvDrinkLabel = new QLabel(frame);
        avgAbvDrinkLabel->setObjectName(QString::fromUtf8("avgAbvDrinkLabel"));
        sizePolicy.setHeightForWidth(avgAbvDrinkLabel->sizePolicy().hasHeightForWidth());
        avgAbvDrinkLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgAbvDrinkLabel, 9, 0, 1, 1);

        drinksThisWeekLabel = new QLabel(frame);
        drinksThisWeekLabel->setObjectName(QString::fromUtf8("drinksThisWeekLabel"));
        sizePolicy.setHeightForWidth(drinksThisWeekLabel->sizePolicy().hasHeightForWidth());
        drinksThisWeekLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksThisWeekLabel, 1, 0, 1, 1);

        avgIbuDrinkOutput = new QLabel(frame);
        avgIbuDrinkOutput->setObjectName(QString::fromUtf8("avgIbuDrinkOutput"));
        sizePolicy.setHeightForWidth(avgIbuDrinkOutput->sizePolicy().hasHeightForWidth());
        avgIbuDrinkOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgIbuDrinkOutput, 10, 2, 1, 1);

        favoriteTypeOutput = new QLabel(frame);
        favoriteTypeOutput->setObjectName(QString::fromUtf8("favoriteTypeOutput"));

        gridLayout_5->addWidget(favoriteTypeOutput, 7, 2, 1, 1);

        favoriteTypeLabel = new QLabel(frame);
        favoriteTypeLabel->setObjectName(QString::fromUtf8("favoriteTypeLabel"));

        gridLayout_5->addWidget(favoriteTypeLabel, 7, 0, 1, 1);

        avgAbvDrinkOutput = new QLabel(frame);
        avgAbvDrinkOutput->setObjectName(QString::fromUtf8("avgAbvDrinkOutput"));
        sizePolicy.setHeightForWidth(avgAbvDrinkOutput->sizePolicy().hasHeightForWidth());
        avgAbvDrinkOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgAbvDrinkOutput, 9, 2, 1, 1);

        favoriteBreweryLabel = new QLabel(frame);
        favoriteBreweryLabel->setObjectName(QString::fromUtf8("favoriteBreweryLabel"));
        sizePolicy.setHeightForWidth(favoriteBreweryLabel->sizePolicy().hasHeightForWidth());
        favoriteBreweryLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBreweryLabel, 5, 0, 1, 1);

        ozAlcoholRemainingOutput = new QLabel(frame);
        ozAlcoholRemainingOutput->setObjectName(QString::fromUtf8("ozAlcoholRemainingOutput"));
        sizePolicy.setHeightForWidth(ozAlcoholRemainingOutput->sizePolicy().hasHeightForWidth());
        ozAlcoholRemainingOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(ozAlcoholRemainingOutput, 4, 2, 1, 1);

        ozAlcoholConsumedLabel = new QLabel(frame);
        ozAlcoholConsumedLabel->setObjectName(QString::fromUtf8("ozAlcoholConsumedLabel"));
        sizePolicy.setHeightForWidth(ozAlcoholConsumedLabel->sizePolicy().hasHeightForWidth());
        ozAlcoholConsumedLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(ozAlcoholConsumedLabel, 3, 0, 1, 1);

        drinksLeftOutput = new QLabel(frame);
        drinksLeftOutput->setObjectName(QString::fromUtf8("drinksLeftOutput"));
        sizePolicy.setHeightForWidth(drinksLeftOutput->sizePolicy().hasHeightForWidth());
        drinksLeftOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksLeftOutput, 2, 2, 1, 1);

        stdDrinksTodayLabel = new QLabel(frame);
        stdDrinksTodayLabel->setObjectName(QString::fromUtf8("stdDrinksTodayLabel"));

        gridLayout_5->addWidget(stdDrinksTodayLabel, 0, 0, 1, 1);

        stdDrinksTodayOutput = new QLabel(frame);
        stdDrinksTodayOutput->setObjectName(QString::fromUtf8("stdDrinksTodayOutput"));

        gridLayout_5->addWidget(stdDrinksTodayOutput, 0, 2, 1, 1);


        gridLayout_4->addWidget(frame, 2, 1, 2, 3);

        drinkDataLabel = new QLabel(centralwidget);
        drinkDataLabel->setObjectName(QString::fromUtf8("drinkDataLabel"));
        sizePolicy.setHeightForWidth(drinkDataLabel->sizePolicy().hasHeightForWidth());
        drinkDataLabel->setSizePolicy(sizePolicy);
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


        gridLayout_4->addWidget(frame_4, 4, 0, 2, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        beerTab = new QWidget();
        beerTab->setObjectName(QString::fromUtf8("beerTab"));
        gridLayout_7 = new QGridLayout(beerTab);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        drinkDateLabel = new QLabel(beerTab);
        drinkDateLabel->setObjectName(QString::fromUtf8("drinkDateLabel"));
        sizePolicy.setHeightForWidth(drinkDateLabel->sizePolicy().hasHeightForWidth());
        drinkDateLabel->setSizePolicy(sizePolicy);
        drinkDateLabel->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(drinkDateLabel, 0, 0, 1, 1);

        beerNameLabel = new QLabel(beerTab);
        beerNameLabel->setObjectName(QString::fromUtf8("beerNameLabel"));
        sizePolicy.setHeightForWidth(beerNameLabel->sizePolicy().hasHeightForWidth());
        beerNameLabel->setSizePolicy(sizePolicy);
        beerNameLabel->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(beerNameLabel, 0, 1, 1, 1);

        beerDateInput = new QDateEdit(beerTab);
        beerDateInput->setObjectName(QString::fromUtf8("beerDateInput"));
        sizePolicy1.setHeightForWidth(beerDateInput->sizePolicy().hasHeightForWidth());
        beerDateInput->setSizePolicy(sizePolicy1);
        beerDateInput->setMinimumSize(QSize(0, 0));
        beerDateInput->setMaximumSize(QSize(16777215, 16777215));
        beerDateInput->setFocusPolicy(Qt::WheelFocus);
        beerDateInput->setStyleSheet(QString::fromUtf8(""));
        beerDateInput->setCalendarPopup(true);

        gridLayout_7->addWidget(beerDateInput, 1, 0, 1, 1);

        beerNameInput = new QComboBox(beerTab);
        beerNameInput->setObjectName(QString::fromUtf8("beerNameInput"));
        sizePolicy1.setHeightForWidth(beerNameInput->sizePolicy().hasHeightForWidth());
        beerNameInput->setSizePolicy(sizePolicy1);
        beerNameInput->setMinimumSize(QSize(300, 0));
        beerNameInput->setEditable(true);

        gridLayout_7->addWidget(beerNameInput, 1, 1, 1, 1);

        beerBreweryLabel = new QLabel(beerTab);
        beerBreweryLabel->setObjectName(QString::fromUtf8("beerBreweryLabel"));
        sizePolicy.setHeightForWidth(beerBreweryLabel->sizePolicy().hasHeightForWidth());
        beerBreweryLabel->setSizePolicy(sizePolicy);
        beerBreweryLabel->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(beerBreweryLabel, 2, 0, 1, 1);

        beerTypeLabel = new QLabel(beerTab);
        beerTypeLabel->setObjectName(QString::fromUtf8("beerTypeLabel"));
        sizePolicy.setHeightForWidth(beerTypeLabel->sizePolicy().hasHeightForWidth());
        beerTypeLabel->setSizePolicy(sizePolicy);
        beerTypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(beerTypeLabel, 2, 1, 1, 1);

        beerBreweryInput = new QComboBox(beerTab);
        beerBreweryInput->setObjectName(QString::fromUtf8("beerBreweryInput"));
        sizePolicy1.setHeightForWidth(beerBreweryInput->sizePolicy().hasHeightForWidth());
        beerBreweryInput->setSizePolicy(sizePolicy1);
        beerBreweryInput->setEditable(true);

        gridLayout_7->addWidget(beerBreweryInput, 3, 0, 1, 1);

        beerTypeInput = new QComboBox(beerTab);
        beerTypeInput->setObjectName(QString::fromUtf8("beerTypeInput"));
        sizePolicy1.setHeightForWidth(beerTypeInput->sizePolicy().hasHeightForWidth());
        beerTypeInput->setSizePolicy(sizePolicy1);
        beerTypeInput->setEditable(true);

        gridLayout_7->addWidget(beerTypeInput, 3, 1, 1, 1);

        beerNotesLabel = new QLabel(beerTab);
        beerNotesLabel->setObjectName(QString::fromUtf8("beerNotesLabel"));
        sizePolicy.setHeightForWidth(beerNotesLabel->sizePolicy().hasHeightForWidth());
        beerNotesLabel->setSizePolicy(sizePolicy);
        beerNotesLabel->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(beerNotesLabel, 4, 0, 1, 1);

        beerSubtypeLabel = new QLabel(beerTab);
        beerSubtypeLabel->setObjectName(QString::fromUtf8("beerSubtypeLabel"));
        beerSubtypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(beerSubtypeLabel, 4, 1, 1, 1);

        beerNotesInput = new QTextEdit(beerTab);
        beerNotesInput->setObjectName(QString::fromUtf8("beerNotesInput"));
        sizePolicy.setHeightForWidth(beerNotesInput->sizePolicy().hasHeightForWidth());
        beerNotesInput->setSizePolicy(sizePolicy);
        beerNotesInput->setFocusPolicy(Qt::ClickFocus);

        gridLayout_7->addWidget(beerNotesInput, 5, 0, 2, 1);

        beerSubtypeInput = new QComboBox(beerTab);
        beerSubtypeInput->setObjectName(QString::fromUtf8("beerSubtypeInput"));
        beerSubtypeInput->setEditable(true);

        gridLayout_7->addWidget(beerSubtypeInput, 5, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        beerRatingInput = new QSpinBox(beerTab);
        beerRatingInput->setObjectName(QString::fromUtf8("beerRatingInput"));
        sizePolicy1.setHeightForWidth(beerRatingInput->sizePolicy().hasHeightForWidth());
        beerRatingInput->setSizePolicy(sizePolicy1);
        beerRatingInput->setMaximum(10);

        gridLayout_3->addWidget(beerRatingInput, 2, 2, 1, 1);

        beerIbuLabel = new QLabel(beerTab);
        beerIbuLabel->setObjectName(QString::fromUtf8("beerIbuLabel"));
        sizePolicy.setHeightForWidth(beerIbuLabel->sizePolicy().hasHeightForWidth());
        beerIbuLabel->setSizePolicy(sizePolicy);
        beerIbuLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(beerIbuLabel, 1, 1, 1, 1);

        beerSizeLabel = new QLabel(beerTab);
        beerSizeLabel->setObjectName(QString::fromUtf8("beerSizeLabel"));
        sizePolicy.setHeightForWidth(beerSizeLabel->sizePolicy().hasHeightForWidth());
        beerSizeLabel->setSizePolicy(sizePolicy);
        beerSizeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(beerSizeLabel, 1, 3, 1, 1);

        beerIbuInput = new QDoubleSpinBox(beerTab);
        beerIbuInput->setObjectName(QString::fromUtf8("beerIbuInput"));
        sizePolicy1.setHeightForWidth(beerIbuInput->sizePolicy().hasHeightForWidth());
        beerIbuInput->setSizePolicy(sizePolicy1);
        beerIbuInput->setDecimals(0);
        beerIbuInput->setMaximum(9999.000000000000000);

        gridLayout_3->addWidget(beerIbuInput, 2, 1, 1, 1);

        beerRatingLabel = new QLabel(beerTab);
        beerRatingLabel->setObjectName(QString::fromUtf8("beerRatingLabel"));
        sizePolicy.setHeightForWidth(beerRatingLabel->sizePolicy().hasHeightForWidth());
        beerRatingLabel->setSizePolicy(sizePolicy);
        beerRatingLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(beerRatingLabel, 1, 2, 1, 1);

        beerAbvLabel = new QLabel(beerTab);
        beerAbvLabel->setObjectName(QString::fromUtf8("beerAbvLabel"));
        sizePolicy.setHeightForWidth(beerAbvLabel->sizePolicy().hasHeightForWidth());
        beerAbvLabel->setSizePolicy(sizePolicy);
        beerAbvLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(beerAbvLabel, 1, 0, 1, 1);

        beerAbvInput = new QDoubleSpinBox(beerTab);
        beerAbvInput->setObjectName(QString::fromUtf8("beerAbvInput"));
        sizePolicy1.setHeightForWidth(beerAbvInput->sizePolicy().hasHeightForWidth());
        beerAbvInput->setSizePolicy(sizePolicy1);
        beerAbvInput->setMaximum(100.000000000000000);

        gridLayout_3->addWidget(beerAbvInput, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 0, 1, 1);

        beerSizeInput = new QDoubleSpinBox(beerTab);
        beerSizeInput->setObjectName(QString::fromUtf8("beerSizeInput"));
        beerSizeInput->setDecimals(1);
        beerSizeInput->setMaximum(10000.000000000000000);

        gridLayout_3->addWidget(beerSizeInput, 2, 3, 1, 1);


        gridLayout_7->addLayout(gridLayout_3, 6, 1, 1, 1);

        tabWidget->addTab(beerTab, QString());
        liquorTab = new QWidget();
        liquorTab->setObjectName(QString::fromUtf8("liquorTab"));
        gridLayout_8 = new QGridLayout(liquorTab);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        liquorTypeLabel = new QLabel(liquorTab);
        liquorTypeLabel->setObjectName(QString::fromUtf8("liquorTypeLabel"));
        sizePolicy.setHeightForWidth(liquorTypeLabel->sizePolicy().hasHeightForWidth());
        liquorTypeLabel->setSizePolicy(sizePolicy);
        liquorTypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(liquorTypeLabel, 2, 2, 1, 1);

        liquorDistillerLabel = new QLabel(liquorTab);
        liquorDistillerLabel->setObjectName(QString::fromUtf8("liquorDistillerLabel"));
        sizePolicy.setHeightForWidth(liquorDistillerLabel->sizePolicy().hasHeightForWidth());
        liquorDistillerLabel->setSizePolicy(sizePolicy);
        liquorDistillerLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(liquorDistillerLabel, 2, 0, 1, 2);

        liquorDateInputLabel = new QLabel(liquorTab);
        liquorDateInputLabel->setObjectName(QString::fromUtf8("liquorDateInputLabel"));
        sizePolicy.setHeightForWidth(liquorDateInputLabel->sizePolicy().hasHeightForWidth());
        liquorDateInputLabel->setSizePolicy(sizePolicy);
        liquorDateInputLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(liquorDateInputLabel, 0, 0, 1, 2);

        liquorSubtypeLabel = new QLabel(liquorTab);
        liquorSubtypeLabel->setObjectName(QString::fromUtf8("liquorSubtypeLabel"));
        liquorSubtypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(liquorSubtypeLabel, 4, 2, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        liquorSizeLabel = new QLabel(liquorTab);
        liquorSizeLabel->setObjectName(QString::fromUtf8("liquorSizeLabel"));
        sizePolicy.setHeightForWidth(liquorSizeLabel->sizePolicy().hasHeightForWidth());
        liquorSizeLabel->setSizePolicy(sizePolicy);
        liquorSizeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(liquorSizeLabel, 1, 2, 1, 1);

        liquorAbvInput = new QDoubleSpinBox(liquorTab);
        liquorAbvInput->setObjectName(QString::fromUtf8("liquorAbvInput"));
        sizePolicy1.setHeightForWidth(liquorAbvInput->sizePolicy().hasHeightForWidth());
        liquorAbvInput->setSizePolicy(sizePolicy1);
        liquorAbvInput->setMaximum(100.000000000000000);

        gridLayout_6->addWidget(liquorAbvInput, 2, 0, 1, 1);

        liquorAbvLabel = new QLabel(liquorTab);
        liquorAbvLabel->setObjectName(QString::fromUtf8("liquorAbvLabel"));
        sizePolicy.setHeightForWidth(liquorAbvLabel->sizePolicy().hasHeightForWidth());
        liquorAbvLabel->setSizePolicy(sizePolicy);
        liquorAbvLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(liquorAbvLabel, 1, 0, 1, 1);

        liquorRatingLabel = new QLabel(liquorTab);
        liquorRatingLabel->setObjectName(QString::fromUtf8("liquorRatingLabel"));
        sizePolicy.setHeightForWidth(liquorRatingLabel->sizePolicy().hasHeightForWidth());
        liquorRatingLabel->setSizePolicy(sizePolicy);
        liquorRatingLabel->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(liquorRatingLabel, 1, 1, 1, 1);

        liquorRatingInput = new QSpinBox(liquorTab);
        liquorRatingInput->setObjectName(QString::fromUtf8("liquorRatingInput"));
        sizePolicy1.setHeightForWidth(liquorRatingInput->sizePolicy().hasHeightForWidth());
        liquorRatingInput->setSizePolicy(sizePolicy1);
        liquorRatingInput->setMaximum(10);

        gridLayout_6->addWidget(liquorRatingInput, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_3, 0, 1, 1, 1);

        liquorSizeInput = new QDoubleSpinBox(liquorTab);
        liquorSizeInput->setObjectName(QString::fromUtf8("liquorSizeInput"));
        liquorSizeInput->setDecimals(1);
        liquorSizeInput->setMaximum(10000.000000000000000);

        gridLayout_6->addWidget(liquorSizeInput, 2, 2, 1, 1);


        gridLayout_8->addLayout(gridLayout_6, 6, 2, 1, 1);

        liquorDistillerInput = new QComboBox(liquorTab);
        liquorDistillerInput->setObjectName(QString::fromUtf8("liquorDistillerInput"));
        sizePolicy1.setHeightForWidth(liquorDistillerInput->sizePolicy().hasHeightForWidth());
        liquorDistillerInput->setSizePolicy(sizePolicy1);
        liquorDistillerInput->setEditable(true);

        gridLayout_8->addWidget(liquorDistillerInput, 3, 0, 1, 2);

        liquorNotesLabel = new QLabel(liquorTab);
        liquorNotesLabel->setObjectName(QString::fromUtf8("liquorNotesLabel"));
        sizePolicy.setHeightForWidth(liquorNotesLabel->sizePolicy().hasHeightForWidth());
        liquorNotesLabel->setSizePolicy(sizePolicy);
        liquorNotesLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(liquorNotesLabel, 4, 0, 1, 2);

        liquorNameInput = new QComboBox(liquorTab);
        liquorNameInput->setObjectName(QString::fromUtf8("liquorNameInput"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(liquorNameInput->sizePolicy().hasHeightForWidth());
        liquorNameInput->setSizePolicy(sizePolicy4);
        liquorNameInput->setEditable(true);

        gridLayout_8->addWidget(liquorNameInput, 1, 2, 1, 1);

        liquorDateInput = new QDateEdit(liquorTab);
        liquorDateInput->setObjectName(QString::fromUtf8("liquorDateInput"));
        sizePolicy1.setHeightForWidth(liquorDateInput->sizePolicy().hasHeightForWidth());
        liquorDateInput->setSizePolicy(sizePolicy1);
        liquorDateInput->setMinimumSize(QSize(0, 0));
        liquorDateInput->setMaximumSize(QSize(16777215, 16777215));
        liquorDateInput->setFocusPolicy(Qt::WheelFocus);
        liquorDateInput->setStyleSheet(QString::fromUtf8(""));
        liquorDateInput->setCalendarPopup(true);

        gridLayout_8->addWidget(liquorDateInput, 1, 0, 1, 2);

        liquorTypeInput = new QComboBox(liquorTab);
        liquorTypeInput->setObjectName(QString::fromUtf8("liquorTypeInput"));
        sizePolicy1.setHeightForWidth(liquorTypeInput->sizePolicy().hasHeightForWidth());
        liquorTypeInput->setSizePolicy(sizePolicy1);
        liquorTypeInput->setEditable(true);

        gridLayout_8->addWidget(liquorTypeInput, 3, 2, 1, 1);

        liquorNameInputLabel = new QLabel(liquorTab);
        liquorNameInputLabel->setObjectName(QString::fromUtf8("liquorNameInputLabel"));
        sizePolicy.setHeightForWidth(liquorNameInputLabel->sizePolicy().hasHeightForWidth());
        liquorNameInputLabel->setSizePolicy(sizePolicy);
        liquorNameInputLabel->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(liquorNameInputLabel, 0, 2, 1, 1);

        liquorSubtypeInput = new QComboBox(liquorTab);
        liquorSubtypeInput->setObjectName(QString::fromUtf8("liquorSubtypeInput"));
        liquorSubtypeInput->setEditable(true);

        gridLayout_8->addWidget(liquorSubtypeInput, 5, 2, 1, 1);

        liquorNotesInput = new QTextEdit(liquorTab);
        liquorNotesInput->setObjectName(QString::fromUtf8("liquorNotesInput"));
        sizePolicy.setHeightForWidth(liquorNotesInput->sizePolicy().hasHeightForWidth());
        liquorNotesInput->setSizePolicy(sizePolicy);
        liquorNotesInput->setFocusPolicy(Qt::ClickFocus);

        gridLayout_8->addWidget(liquorNotesInput, 5, 0, 2, 2);

        tabWidget->addTab(liquorTab, QString());
        wineTab = new QWidget();
        wineTab->setObjectName(QString::fromUtf8("wineTab"));
        gridLayout_10 = new QGridLayout(wineTab);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        wineSizeLabel = new QLabel(wineTab);
        wineSizeLabel->setObjectName(QString::fromUtf8("wineSizeLabel"));
        sizePolicy.setHeightForWidth(wineSizeLabel->sizePolicy().hasHeightForWidth());
        wineSizeLabel->setSizePolicy(sizePolicy);
        wineSizeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(wineSizeLabel, 1, 3, 1, 1);

        wineVintageLabel = new QLabel(wineTab);
        wineVintageLabel->setObjectName(QString::fromUtf8("wineVintageLabel"));
        wineVintageLabel->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(wineVintageLabel, 1, 0, 1, 1);

        wineVintage = new QSpinBox(wineTab);
        wineVintage->setObjectName(QString::fromUtf8("wineVintage"));
        wineVintage->setMaximum(9999);
        wineVintage->setValue(2000);

        gridLayout_9->addWidget(wineVintage, 2, 0, 1, 1);

        wineRatingLabel = new QLabel(wineTab);
        wineRatingLabel->setObjectName(QString::fromUtf8("wineRatingLabel"));
        sizePolicy.setHeightForWidth(wineRatingLabel->sizePolicy().hasHeightForWidth());
        wineRatingLabel->setSizePolicy(sizePolicy);
        wineRatingLabel->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(wineRatingLabel, 1, 2, 1, 1);

        wineRatingInput = new QSpinBox(wineTab);
        wineRatingInput->setObjectName(QString::fromUtf8("wineRatingInput"));
        sizePolicy1.setHeightForWidth(wineRatingInput->sizePolicy().hasHeightForWidth());
        wineRatingInput->setSizePolicy(sizePolicy1);
        wineRatingInput->setMaximum(10);

        gridLayout_9->addWidget(wineRatingInput, 2, 2, 1, 1);

        wineAbvInput = new QDoubleSpinBox(wineTab);
        wineAbvInput->setObjectName(QString::fromUtf8("wineAbvInput"));
        sizePolicy1.setHeightForWidth(wineAbvInput->sizePolicy().hasHeightForWidth());
        wineAbvInput->setSizePolicy(sizePolicy1);
        wineAbvInput->setMaximum(100.000000000000000);

        gridLayout_9->addWidget(wineAbvInput, 2, 1, 1, 1);

        wineAbvLabel = new QLabel(wineTab);
        wineAbvLabel->setObjectName(QString::fromUtf8("wineAbvLabel"));
        sizePolicy.setHeightForWidth(wineAbvLabel->sizePolicy().hasHeightForWidth());
        wineAbvLabel->setSizePolicy(sizePolicy);
        wineAbvLabel->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(wineAbvLabel, 1, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_9->addItem(verticalSpacer_4, 0, 0, 1, 1);

        wineSizeInput = new QDoubleSpinBox(wineTab);
        wineSizeInput->setObjectName(QString::fromUtf8("wineSizeInput"));
        wineSizeInput->setDecimals(1);
        wineSizeInput->setMaximum(10000.000000000000000);

        gridLayout_9->addWidget(wineSizeInput, 2, 3, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 6, 2, 1, 1);

        wineDateInput = new QDateEdit(wineTab);
        wineDateInput->setObjectName(QString::fromUtf8("wineDateInput"));
        sizePolicy.setHeightForWidth(wineDateInput->sizePolicy().hasHeightForWidth());
        wineDateInput->setSizePolicy(sizePolicy);
        wineDateInput->setMaximumSize(QSize(16777215, 16777215));
        wineDateInput->setFocusPolicy(Qt::WheelFocus);
        wineDateInput->setStyleSheet(QString::fromUtf8(""));
        wineDateInput->setCalendarPopup(true);

        gridLayout_10->addWidget(wineDateInput, 1, 0, 1, 2);

        wineDateLabel = new QLabel(wineTab);
        wineDateLabel->setObjectName(QString::fromUtf8("wineDateLabel"));
        sizePolicy.setHeightForWidth(wineDateLabel->sizePolicy().hasHeightForWidth());
        wineDateLabel->setSizePolicy(sizePolicy);
        wineDateLabel->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(wineDateLabel, 0, 0, 1, 2);

        wineNotesLabel = new QLabel(wineTab);
        wineNotesLabel->setObjectName(QString::fromUtf8("wineNotesLabel"));
        sizePolicy.setHeightForWidth(wineNotesLabel->sizePolicy().hasHeightForWidth());
        wineNotesLabel->setSizePolicy(sizePolicy);
        wineNotesLabel->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(wineNotesLabel, 4, 0, 1, 2);

        wineNameLabel = new QLabel(wineTab);
        wineNameLabel->setObjectName(QString::fromUtf8("wineNameLabel"));
        sizePolicy.setHeightForWidth(wineNameLabel->sizePolicy().hasHeightForWidth());
        wineNameLabel->setSizePolicy(sizePolicy);
        wineNameLabel->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(wineNameLabel, 0, 2, 1, 1);

        wineTypeInput = new QComboBox(wineTab);
        wineTypeInput->setObjectName(QString::fromUtf8("wineTypeInput"));
        sizePolicy1.setHeightForWidth(wineTypeInput->sizePolicy().hasHeightForWidth());
        wineTypeInput->setSizePolicy(sizePolicy1);
        wineTypeInput->setEditable(true);

        gridLayout_10->addWidget(wineTypeInput, 3, 2, 1, 1);

        wineNameInput = new QComboBox(wineTab);
        wineNameInput->setObjectName(QString::fromUtf8("wineNameInput"));
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(wineNameInput->sizePolicy().hasHeightForWidth());
        wineNameInput->setSizePolicy(sizePolicy5);
        wineNameInput->setEditable(true);

        gridLayout_10->addWidget(wineNameInput, 1, 2, 1, 1);

        wineryInput = new QComboBox(wineTab);
        wineryInput->setObjectName(QString::fromUtf8("wineryInput"));
        sizePolicy1.setHeightForWidth(wineryInput->sizePolicy().hasHeightForWidth());
        wineryInput->setSizePolicy(sizePolicy1);
        wineryInput->setEditable(true);

        gridLayout_10->addWidget(wineryInput, 3, 0, 1, 2);

        wineTypeLabel = new QLabel(wineTab);
        wineTypeLabel->setObjectName(QString::fromUtf8("wineTypeLabel"));
        sizePolicy.setHeightForWidth(wineTypeLabel->sizePolicy().hasHeightForWidth());
        wineTypeLabel->setSizePolicy(sizePolicy);
        wineTypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(wineTypeLabel, 2, 2, 1, 1);

        wineSubtypeLabel = new QLabel(wineTab);
        wineSubtypeLabel->setObjectName(QString::fromUtf8("wineSubtypeLabel"));
        wineSubtypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(wineSubtypeLabel, 4, 2, 1, 1);

        wineryLabel = new QLabel(wineTab);
        wineryLabel->setObjectName(QString::fromUtf8("wineryLabel"));
        sizePolicy.setHeightForWidth(wineryLabel->sizePolicy().hasHeightForWidth());
        wineryLabel->setSizePolicy(sizePolicy);
        wineryLabel->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(wineryLabel, 2, 0, 1, 2);

        wineSubtypeInput = new QComboBox(wineTab);
        wineSubtypeInput->setObjectName(QString::fromUtf8("wineSubtypeInput"));
        wineSubtypeInput->setEditable(true);

        gridLayout_10->addWidget(wineSubtypeInput, 5, 2, 1, 1);

        wineNotesInput = new QTextEdit(wineTab);
        wineNotesInput->setObjectName(QString::fromUtf8("wineNotesInput"));
        sizePolicy.setHeightForWidth(wineNotesInput->sizePolicy().hasHeightForWidth());
        wineNotesInput->setSizePolicy(sizePolicy);
        wineNotesInput->setFocusPolicy(Qt::ClickFocus);

        gridLayout_10->addWidget(wineNotesInput, 5, 0, 2, 2);

        tabWidget->addTab(wineTab, QString());

        gridLayout_4->addWidget(tabWidget, 2, 0, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1006, 24));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(tabWidget, beerDateInput);
        QWidget::setTabOrder(beerDateInput, beerNameInput);
        QWidget::setTabOrder(beerNameInput, beerBreweryInput);
        QWidget::setTabOrder(beerBreweryInput, beerTypeInput);
        QWidget::setTabOrder(beerTypeInput, beerSubtypeInput);
        QWidget::setTabOrder(beerSubtypeInput, beerAbvInput);
        QWidget::setTabOrder(beerAbvInput, beerIbuInput);
        QWidget::setTabOrder(beerIbuInput, beerRatingInput);
        QWidget::setTabOrder(beerRatingInput, liquorDateInput);
        QWidget::setTabOrder(liquorDateInput, liquorNameInput);
        QWidget::setTabOrder(liquorNameInput, liquorDistillerInput);
        QWidget::setTabOrder(liquorDistillerInput, liquorTypeInput);
        QWidget::setTabOrder(liquorTypeInput, liquorSubtypeInput);
        QWidget::setTabOrder(liquorSubtypeInput, liquorAbvInput);
        QWidget::setTabOrder(liquorAbvInput, liquorRatingInput);
        QWidget::setTabOrder(liquorRatingInput, wineDateInput);
        QWidget::setTabOrder(wineDateInput, wineNameInput);
        QWidget::setTabOrder(wineNameInput, wineryInput);
        QWidget::setTabOrder(wineryInput, wineTypeInput);
        QWidget::setTabOrder(wineTypeInput, wineSubtypeInput);
        QWidget::setTabOrder(wineSubtypeInput, wineVintage);
        QWidget::setTabOrder(wineVintage, wineAbvInput);
        QWidget::setTabOrder(wineAbvInput, wineRatingInput);
        QWidget::setTabOrder(wineRatingInput, filterCategoryInput);
        QWidget::setTabOrder(filterCategoryInput, filterTextInput);
        QWidget::setTabOrder(filterTextInput, deleteRowButton);
        QWidget::setTabOrder(deleteRowButton, clearFieldsButton);
        QWidget::setTabOrder(clearFieldsButton, submitRowButton);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BuzzBot", nullptr));
        filterLabel->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        filterCategoryLabel->setText(QCoreApplication::translate("MainWindow", "Filter Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem = drinkLogTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = drinkLogTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = drinkLogTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = drinkLogTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Subtype", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = drinkLogTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Producer", nullptr));
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
        QTableWidgetItem *___qtablewidgetitem11 = drinkLogTable->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Sort", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = drinkLogTable->verticalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "1", nullptr));

        const bool __sortingEnabled = drinkLogTable->isSortingEnabled();
        drinkLogTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem13 = drinkLogTable->item(0, 0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "09/07/2020", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = drinkLogTable->item(0, 1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Everything Rhymes with Orange", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = drinkLogTable->item(0, 2);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "IPA", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = drinkLogTable->item(0, 4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Roughtail Brewing", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = drinkLogTable->item(0, 5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "8.0", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = drinkLogTable->item(0, 6);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "65", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = drinkLogTable->item(0, 7);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        drinkLogTable->setSortingEnabled(__sortingEnabled);

        statsLabel->setText(QCoreApplication::translate("MainWindow", "Stats", nullptr));
        drinksThisWeekOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        favoriteBreweryOutput->setText(QCoreApplication::translate("MainWindow", "Roughtail Brewing Co.", nullptr));
        ozAlcoholConsumedOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        favoriteBeerLabel->setText(QCoreApplication::translate("MainWindow", "Most frequent drink:", nullptr));
        favoriteBeerOutput->setText(QCoreApplication::translate("MainWindow", "Everything Rhymes with Orange", nullptr));
        drinksLeftLabel->setText(QCoreApplication::translate("MainWindow", "Std. drinks remaining:", nullptr));
        averageIbuDrinkLabel->setText(QCoreApplication::translate("MainWindow", "Average IBU per beer:", nullptr));
        ozAlcoholRemainingLabel->setText(QCoreApplication::translate("MainWindow", "Oz. alcohol remaining:", nullptr));
        avgAbvDrinkLabel->setText(QCoreApplication::translate("MainWindow", "Average ABV per drink:", nullptr));
        drinksThisWeekLabel->setText(QCoreApplication::translate("MainWindow", "Std. drinks this week:", nullptr));
        avgIbuDrinkOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        favoriteTypeOutput->setText(QCoreApplication::translate("MainWindow", "IPA", nullptr));
        favoriteTypeLabel->setText(QCoreApplication::translate("MainWindow", "Most frequent type:", nullptr));
        avgAbvDrinkOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        favoriteBreweryLabel->setText(QCoreApplication::translate("MainWindow", "Most frequent producer:", nullptr));
        ozAlcoholRemainingOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        ozAlcoholConsumedLabel->setText(QCoreApplication::translate("MainWindow", "Oz. alcohol consumed:", nullptr));
        drinksLeftOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        stdDrinksTodayLabel->setText(QCoreApplication::translate("MainWindow", "Std. drinks today:", nullptr));
        stdDrinksTodayOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        drinkDataLabel->setText(QCoreApplication::translate("MainWindow", "Drink Data", nullptr));
        clearFieldsButton->setText(QCoreApplication::translate("MainWindow", "Clear Selections", nullptr));
        deleteRowButton->setText(QCoreApplication::translate("MainWindow", "Delete Row", nullptr));
        submitRowButton->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        drinkDateLabel->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        beerNameLabel->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        beerDateInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "MMM/dd/yyyy", nullptr));
        beerBreweryLabel->setText(QCoreApplication::translate("MainWindow", "Brewery", nullptr));
        beerTypeLabel->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        beerNotesLabel->setText(QCoreApplication::translate("MainWindow", "Notes", nullptr));
        beerSubtypeLabel->setText(QCoreApplication::translate("MainWindow", "Subtype", nullptr));
        beerIbuLabel->setText(QCoreApplication::translate("MainWindow", "IBU", nullptr));
        beerSizeLabel->setText(QCoreApplication::translate("MainWindow", "Size (oz)", nullptr));
        beerRatingLabel->setText(QCoreApplication::translate("MainWindow", "Rating", nullptr));
        beerAbvLabel->setText(QCoreApplication::translate("MainWindow", "ABV", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(beerTab), QCoreApplication::translate("MainWindow", "Beer", nullptr));
        liquorTypeLabel->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        liquorDistillerLabel->setText(QCoreApplication::translate("MainWindow", "Distillery", nullptr));
        liquorDateInputLabel->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        liquorSubtypeLabel->setText(QCoreApplication::translate("MainWindow", "Subtype", nullptr));
        liquorSizeLabel->setText(QCoreApplication::translate("MainWindow", "Size (oz)", nullptr));
        liquorAbvLabel->setText(QCoreApplication::translate("MainWindow", "ABV", nullptr));
        liquorRatingLabel->setText(QCoreApplication::translate("MainWindow", "Rating", nullptr));
        liquorNotesLabel->setText(QCoreApplication::translate("MainWindow", "Notes", nullptr));
        liquorDateInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "MMM/dd/yyyy", nullptr));
        liquorNameInputLabel->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(liquorTab), QCoreApplication::translate("MainWindow", "Liquor", nullptr));
        wineSizeLabel->setText(QCoreApplication::translate("MainWindow", "Size (oz)", nullptr));
        wineVintageLabel->setText(QCoreApplication::translate("MainWindow", "Vintage", nullptr));
        wineRatingLabel->setText(QCoreApplication::translate("MainWindow", "Rating", nullptr));
        wineAbvLabel->setText(QCoreApplication::translate("MainWindow", "ABV", nullptr));
        wineDateInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "MMM/dd/yyyy", nullptr));
        wineDateLabel->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        wineNotesLabel->setText(QCoreApplication::translate("MainWindow", "Notes", nullptr));
        wineNameLabel->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        wineTypeLabel->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        wineSubtypeLabel->setText(QCoreApplication::translate("MainWindow", "Subtype", nullptr));
        wineryLabel->setText(QCoreApplication::translate("MainWindow", "Winery", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(wineTab), QCoreApplication::translate("MainWindow", "Wine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
