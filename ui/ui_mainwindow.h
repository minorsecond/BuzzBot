/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
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
#include <QtWidgets/QHBoxLayout>
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QLabel *stdDrinksTodayLabel;
    QSpacerItem *verticalSpacer;
    QLabel *favoriteBeerLabel;
    QLabel *daysConsecutiveLabel;
    QLabel *favoriteBreweryLabel;
    QLabel *volAlcoholConsumedLabel;
    QLabel *drinksLeftOutput;
    QLabel *consecutiveConsumptionLabel;
    QLabel *avgAbvDrinkOutput;
    QLabel *avgIbuDrinkOutput;
    QLabel *favoriteTypeOutput;
    QLabel *volAlcoholConsumedOutput;
    QLabel *drinksThisWeekOutput;
    QLabel *drinksThisWeekLabel;
    QLabel *volAlcoholRemainingOutput;
    QLabel *favoriteDrinkOutput;
    QLabel *stdDrinksTodayOutput;
    QLabel *favoriteProducerOutput;
    QLabel *favoriteTypeLabel;
    QLabel *avgAbvDrinkLabel;
    QLabel *drinksLeftLabel;
    QLabel *volAlcoholRemainingLabel;
    QLabel *averageIbuDrinkLabel;
    QLabel *statsLabel;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *deleteRowButton;
    QPushButton *clearFieldsButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *submitRowButton;
    QLabel *drinkDataLabel;
    QTableWidget *drinkLogTable;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QLabel *filterCategoryLabel;
    QSpacerItem *horizontalSpacer;
    QComboBox *filterTextInput;
    QComboBox *filterCategoryInput;
    QLabel *filterLabel;
    QTabWidget *tabWidget;
    QWidget *beerTab;
    QGridLayout *gridLayout_14;
    QLabel *beerSubtypeLabel;
    QLabel *beerBreweryLabel;
    QLabel *beerTypeLabel;
    QLabel *drinkDateLabel;
    QDateEdit *beerDateInput;
    QLabel *beerNameLabel;
    QComboBox *beerNameInput;
    QComboBox *beerBreweryInput;
    QComboBox *beerTypeInput;
    QLabel *beerNotesLabel;
    QComboBox *beerSubtypeInput;
    QGridLayout *gridLayout_3;
    QLabel *beerRatingLabel;
    QDoubleSpinBox *beerAbvInput;
    QDoubleSpinBox *beerSizeInput;
    QLabel *beerSizeLabel;
    QLabel *beerAbvLabel;
    QSpinBox *beerRatingInput;
    QLabel *beerIbuLabel;
    QDoubleSpinBox *beerIbuInput;
    QTextEdit *beerNotesInput;
    QWidget *liquorTab;
    QGridLayout *gridLayout_8;
    QLabel *liquorDateInputLabel;
    QLabel *liquorNameInputLabel;
    QDateEdit *liquorDateInput;
    QComboBox *liquorNameInput;
    QLabel *liquorDistillerLabel;
    QLabel *liquorTypeLabel;
    QComboBox *liquorDistillerInput;
    QComboBox *liquorTypeInput;
    QLabel *liquorSubtypeLabel;
    QComboBox *liquorSubtypeInput;
    QLabel *liquorNotesLabel;
    QTextEdit *liquorNotesInput;
    QGridLayout *gridLayout_6;
    QLabel *liquorAbvLabel;
    QLabel *liquorRatingLabel;
    QLabel *liquorSizeLabel;
    QWidget *widget;
    QDoubleSpinBox *liquorAbvInput;
    QSpinBox *liquorRatingInput;
    QDoubleSpinBox *liquorSizeInput;
    QWidget *wineTab;
    QGridLayout *gridLayout_10;
    QLabel *wineDateLabel;
    QLabel *wineNameLabel;
    QDateEdit *wineDateInput;
    QComboBox *wineNameInput;
    QLabel *wineryLabel;
    QLabel *wineTypeLabel;
    QComboBox *wineryInput;
    QComboBox *wineTypeInput;
    QLabel *wineSubtypeLabel;
    QComboBox *wineSubtypeInput;
    QLabel *wineNotesLabel;
    QTextEdit *wineNotesInput;
    QGridLayout *gridLayout_9;
    QLabel *wineVintageLabel;
    QLabel *wineAbvLabel;
    QLabel *wineRatingLabel;
    QLabel *wineSizeLabel;
    QSpinBox *wineVintage;
    QDoubleSpinBox *wineAbvInput;
    QSpinBox *wineRatingInput;
    QDoubleSpinBox *wineSizeInput;
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
        centralwidget->setMinimumSize(QSize(800, 670));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        stdDrinksTodayLabel = new QLabel(frame);
        stdDrinksTodayLabel->setObjectName(QString::fromUtf8("stdDrinksTodayLabel"));

        gridLayout_5->addWidget(stdDrinksTodayLabel, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_5->addItem(verticalSpacer, 11, 0, 1, 1);

        favoriteBeerLabel = new QLabel(frame);
        favoriteBeerLabel->setObjectName(QString::fromUtf8("favoriteBeerLabel"));
        sizePolicy.setHeightForWidth(favoriteBeerLabel->sizePolicy().hasHeightForWidth());
        favoriteBeerLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBeerLabel, 7, 0, 1, 1);

        daysConsecutiveLabel = new QLabel(frame);
        daysConsecutiveLabel->setObjectName(QString::fromUtf8("daysConsecutiveLabel"));

        gridLayout_5->addWidget(daysConsecutiveLabel, 0, 0, 1, 1);

        favoriteBreweryLabel = new QLabel(frame);
        favoriteBreweryLabel->setObjectName(QString::fromUtf8("favoriteBreweryLabel"));
        sizePolicy.setHeightForWidth(favoriteBreweryLabel->sizePolicy().hasHeightForWidth());
        favoriteBreweryLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteBreweryLabel, 6, 0, 1, 1);

        volAlcoholConsumedLabel = new QLabel(frame);
        volAlcoholConsumedLabel->setObjectName(QString::fromUtf8("volAlcoholConsumedLabel"));
        sizePolicy.setHeightForWidth(volAlcoholConsumedLabel->sizePolicy().hasHeightForWidth());
        volAlcoholConsumedLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(volAlcoholConsumedLabel, 4, 0, 1, 1);

        drinksLeftOutput = new QLabel(frame);
        drinksLeftOutput->setObjectName(QString::fromUtf8("drinksLeftOutput"));
        sizePolicy.setHeightForWidth(drinksLeftOutput->sizePolicy().hasHeightForWidth());
        drinksLeftOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksLeftOutput, 3, 1, 1, 1);

        consecutiveConsumptionLabel = new QLabel(frame);
        consecutiveConsumptionLabel->setObjectName(QString::fromUtf8("consecutiveConsumptionLabel"));

        gridLayout_5->addWidget(consecutiveConsumptionLabel, 0, 1, 1, 1);

        avgAbvDrinkOutput = new QLabel(frame);
        avgAbvDrinkOutput->setObjectName(QString::fromUtf8("avgAbvDrinkOutput"));
        sizePolicy.setHeightForWidth(avgAbvDrinkOutput->sizePolicy().hasHeightForWidth());
        avgAbvDrinkOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgAbvDrinkOutput, 9, 1, 1, 1);

        avgIbuDrinkOutput = new QLabel(frame);
        avgIbuDrinkOutput->setObjectName(QString::fromUtf8("avgIbuDrinkOutput"));
        sizePolicy.setHeightForWidth(avgIbuDrinkOutput->sizePolicy().hasHeightForWidth());
        avgIbuDrinkOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgIbuDrinkOutput, 10, 1, 1, 1);

        favoriteTypeOutput = new QLabel(frame);
        favoriteTypeOutput->setObjectName(QString::fromUtf8("favoriteTypeOutput"));

        gridLayout_5->addWidget(favoriteTypeOutput, 8, 1, 1, 1);

        volAlcoholConsumedOutput = new QLabel(frame);
        volAlcoholConsumedOutput->setObjectName(QString::fromUtf8("volAlcoholConsumedOutput"));
        sizePolicy.setHeightForWidth(volAlcoholConsumedOutput->sizePolicy().hasHeightForWidth());
        volAlcoholConsumedOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(volAlcoholConsumedOutput, 4, 1, 1, 1);

        drinksThisWeekOutput = new QLabel(frame);
        drinksThisWeekOutput->setObjectName(QString::fromUtf8("drinksThisWeekOutput"));
        sizePolicy.setHeightForWidth(drinksThisWeekOutput->sizePolicy().hasHeightForWidth());
        drinksThisWeekOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksThisWeekOutput, 2, 1, 1, 1);

        drinksThisWeekLabel = new QLabel(frame);
        drinksThisWeekLabel->setObjectName(QString::fromUtf8("drinksThisWeekLabel"));
        sizePolicy.setHeightForWidth(drinksThisWeekLabel->sizePolicy().hasHeightForWidth());
        drinksThisWeekLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksThisWeekLabel, 2, 0, 1, 1);

        volAlcoholRemainingOutput = new QLabel(frame);
        volAlcoholRemainingOutput->setObjectName(QString::fromUtf8("volAlcoholRemainingOutput"));
        sizePolicy.setHeightForWidth(volAlcoholRemainingOutput->sizePolicy().hasHeightForWidth());
        volAlcoholRemainingOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(volAlcoholRemainingOutput, 5, 1, 1, 1);

        favoriteDrinkOutput = new QLabel(frame);
        favoriteDrinkOutput->setObjectName(QString::fromUtf8("favoriteDrinkOutput"));
        sizePolicy.setHeightForWidth(favoriteDrinkOutput->sizePolicy().hasHeightForWidth());
        favoriteDrinkOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteDrinkOutput, 7, 1, 1, 1);

        stdDrinksTodayOutput = new QLabel(frame);
        stdDrinksTodayOutput->setObjectName(QString::fromUtf8("stdDrinksTodayOutput"));

        gridLayout_5->addWidget(stdDrinksTodayOutput, 1, 1, 1, 1);

        favoriteProducerOutput = new QLabel(frame);
        favoriteProducerOutput->setObjectName(QString::fromUtf8("favoriteProducerOutput"));
        sizePolicy.setHeightForWidth(favoriteProducerOutput->sizePolicy().hasHeightForWidth());
        favoriteProducerOutput->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(favoriteProducerOutput, 6, 1, 1, 1);

        favoriteTypeLabel = new QLabel(frame);
        favoriteTypeLabel->setObjectName(QString::fromUtf8("favoriteTypeLabel"));

        gridLayout_5->addWidget(favoriteTypeLabel, 8, 0, 1, 1);

        avgAbvDrinkLabel = new QLabel(frame);
        avgAbvDrinkLabel->setObjectName(QString::fromUtf8("avgAbvDrinkLabel"));
        sizePolicy.setHeightForWidth(avgAbvDrinkLabel->sizePolicy().hasHeightForWidth());
        avgAbvDrinkLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(avgAbvDrinkLabel, 9, 0, 1, 1);

        drinksLeftLabel = new QLabel(frame);
        drinksLeftLabel->setObjectName(QString::fromUtf8("drinksLeftLabel"));
        sizePolicy.setHeightForWidth(drinksLeftLabel->sizePolicy().hasHeightForWidth());
        drinksLeftLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(drinksLeftLabel, 3, 0, 1, 1);

        volAlcoholRemainingLabel = new QLabel(frame);
        volAlcoholRemainingLabel->setObjectName(QString::fromUtf8("volAlcoholRemainingLabel"));
        sizePolicy.setHeightForWidth(volAlcoholRemainingLabel->sizePolicy().hasHeightForWidth());
        volAlcoholRemainingLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(volAlcoholRemainingLabel, 5, 0, 1, 1);

        averageIbuDrinkLabel = new QLabel(frame);
        averageIbuDrinkLabel->setObjectName(QString::fromUtf8("averageIbuDrinkLabel"));
        sizePolicy.setHeightForWidth(averageIbuDrinkLabel->sizePolicy().hasHeightForWidth());
        averageIbuDrinkLabel->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(averageIbuDrinkLabel, 10, 0, 1, 1);


        gridLayout_4->addWidget(frame, 1, 1, 1, 1);

        statsLabel = new QLabel(centralwidget);
        statsLabel->setObjectName(QString::fromUtf8("statsLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(statsLabel->sizePolicy().hasHeightForWidth());
        statsLabel->setSizePolicy(sizePolicy2);
        QFont font;
        font.setBold(true);
        statsLabel->setFont(font);

        gridLayout_4->addWidget(statsLabel, 0, 1, 1, 1);

        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        deleteRowButton = new QPushButton(frame_4);
        deleteRowButton->setObjectName(QString::fromUtf8("deleteRowButton"));
        sizePolicy2.setHeightForWidth(deleteRowButton->sizePolicy().hasHeightForWidth());
        deleteRowButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(deleteRowButton);

        clearFieldsButton = new QPushButton(frame_4);
        clearFieldsButton->setObjectName(QString::fromUtf8("clearFieldsButton"));
        sizePolicy2.setHeightForWidth(clearFieldsButton->sizePolicy().hasHeightForWidth());
        clearFieldsButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(clearFieldsButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        submitRowButton = new QPushButton(frame_4);
        submitRowButton->setObjectName(QString::fromUtf8("submitRowButton"));
        sizePolicy2.setHeightForWidth(submitRowButton->sizePolicy().hasHeightForWidth());
        submitRowButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(submitRowButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_4->addWidget(frame_4, 2, 0, 1, 1);

        drinkDataLabel = new QLabel(centralwidget);
        drinkDataLabel->setObjectName(QString::fromUtf8("drinkDataLabel"));
        sizePolicy.setHeightForWidth(drinkDataLabel->sizePolicy().hasHeightForWidth());
        drinkDataLabel->setSizePolicy(sizePolicy);
        drinkDataLabel->setFont(font);

        gridLayout_4->addWidget(drinkDataLabel, 0, 0, 1, 1);

        drinkLogTable = new QTableWidget(centralwidget);
        if (drinkLogTable->columnCount() < 13)
            drinkLogTable->setColumnCount(13);
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
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        drinkLogTable->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        if (drinkLogTable->rowCount() < 1)
            drinkLogTable->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        drinkLogTable->setVerticalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 4, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 5, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 6, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        drinkLogTable->setItem(0, 7, __qtablewidgetitem20);
        drinkLogTable->setObjectName(QString::fromUtf8("drinkLogTable"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(100);
        sizePolicy3.setHeightForWidth(drinkLogTable->sizePolicy().hasHeightForWidth());
        drinkLogTable->setSizePolicy(sizePolicy3);
        drinkLogTable->setFocusPolicy(Qt::ClickFocus);

        gridLayout_4->addWidget(drinkLogTable, 3, 0, 1, 2);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        filterCategoryLabel = new QLabel(frame_2);
        filterCategoryLabel->setObjectName(QString::fromUtf8("filterCategoryLabel"));
        sizePolicy.setHeightForWidth(filterCategoryLabel->sizePolicy().hasHeightForWidth());
        filterCategoryLabel->setSizePolicy(sizePolicy);

        gridLayout->addWidget(filterCategoryLabel, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 1, 1);

        filterTextInput = new QComboBox(frame_2);
        filterTextInput->setObjectName(QString::fromUtf8("filterTextInput"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(filterTextInput->sizePolicy().hasHeightForWidth());
        filterTextInput->setSizePolicy(sizePolicy4);
        filterTextInput->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(filterTextInput, 1, 3, 1, 1);

        filterCategoryInput = new QComboBox(frame_2);
        filterCategoryInput->setObjectName(QString::fromUtf8("filterCategoryInput"));
        sizePolicy4.setHeightForWidth(filterCategoryInput->sizePolicy().hasHeightForWidth());
        filterCategoryInput->setSizePolicy(sizePolicy4);
        filterCategoryInput->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(filterCategoryInput, 1, 1, 1, 1);

        filterLabel = new QLabel(frame_2);
        filterLabel->setObjectName(QString::fromUtf8("filterLabel"));
        sizePolicy.setHeightForWidth(filterLabel->sizePolicy().hasHeightForWidth());
        filterLabel->setSizePolicy(sizePolicy);
        filterLabel->setMargin(5);

        gridLayout->addWidget(filterLabel, 1, 2, 1, 1);


        gridLayout_4->addWidget(frame_2, 4, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy5);
        beerTab = new QWidget();
        beerTab->setObjectName(QString::fromUtf8("beerTab"));
        gridLayout_14 = new QGridLayout(beerTab);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        beerSubtypeLabel = new QLabel(beerTab);
        beerSubtypeLabel->setObjectName(QString::fromUtf8("beerSubtypeLabel"));

        gridLayout_14->addWidget(beerSubtypeLabel, 5, 1, 1, 1);

        beerBreweryLabel = new QLabel(beerTab);
        beerBreweryLabel->setObjectName(QString::fromUtf8("beerBreweryLabel"));
        sizePolicy.setHeightForWidth(beerBreweryLabel->sizePolicy().hasHeightForWidth());
        beerBreweryLabel->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(beerBreweryLabel, 2, 0, 1, 1);

        beerTypeLabel = new QLabel(beerTab);
        beerTypeLabel->setObjectName(QString::fromUtf8("beerTypeLabel"));
        sizePolicy.setHeightForWidth(beerTypeLabel->sizePolicy().hasHeightForWidth());
        beerTypeLabel->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(beerTypeLabel, 2, 1, 1, 1);

        drinkDateLabel = new QLabel(beerTab);
        drinkDateLabel->setObjectName(QString::fromUtf8("drinkDateLabel"));
        sizePolicy.setHeightForWidth(drinkDateLabel->sizePolicy().hasHeightForWidth());
        drinkDateLabel->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(drinkDateLabel, 0, 0, 1, 1);

        beerDateInput = new QDateEdit(beerTab);
        beerDateInput->setObjectName(QString::fromUtf8("beerDateInput"));
        sizePolicy2.setHeightForWidth(beerDateInput->sizePolicy().hasHeightForWidth());
        beerDateInput->setSizePolicy(sizePolicy2);
        beerDateInput->setFocusPolicy(Qt::WheelFocus);
        beerDateInput->setStyleSheet(QString::fromUtf8(""));
        beerDateInput->setCalendarPopup(true);

        gridLayout_14->addWidget(beerDateInput, 1, 0, 1, 1);

        beerNameLabel = new QLabel(beerTab);
        beerNameLabel->setObjectName(QString::fromUtf8("beerNameLabel"));
        sizePolicy.setHeightForWidth(beerNameLabel->sizePolicy().hasHeightForWidth());
        beerNameLabel->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(beerNameLabel, 0, 1, 1, 1);

        beerNameInput = new QComboBox(beerTab);
        beerNameInput->setObjectName(QString::fromUtf8("beerNameInput"));
        beerNameInput->setEditable(true);

        gridLayout_14->addWidget(beerNameInput, 1, 1, 1, 1);

        beerBreweryInput = new QComboBox(beerTab);
        beerBreweryInput->setObjectName(QString::fromUtf8("beerBreweryInput"));
        beerBreweryInput->setEditable(true);

        gridLayout_14->addWidget(beerBreweryInput, 3, 0, 1, 1);

        beerTypeInput = new QComboBox(beerTab);
        beerTypeInput->setObjectName(QString::fromUtf8("beerTypeInput"));
        beerTypeInput->setEditable(true);

        gridLayout_14->addWidget(beerTypeInput, 3, 1, 1, 1);

        beerNotesLabel = new QLabel(beerTab);
        beerNotesLabel->setObjectName(QString::fromUtf8("beerNotesLabel"));
        sizePolicy.setHeightForWidth(beerNotesLabel->sizePolicy().hasHeightForWidth());
        beerNotesLabel->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(beerNotesLabel, 8, 0, 1, 1);

        beerSubtypeInput = new QComboBox(beerTab);
        beerSubtypeInput->setObjectName(QString::fromUtf8("beerSubtypeInput"));
        beerSubtypeInput->setEditable(true);

        gridLayout_14->addWidget(beerSubtypeInput, 6, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        beerRatingLabel = new QLabel(beerTab);
        beerRatingLabel->setObjectName(QString::fromUtf8("beerRatingLabel"));
        sizePolicy.setHeightForWidth(beerRatingLabel->sizePolicy().hasHeightForWidth());
        beerRatingLabel->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(beerRatingLabel, 0, 0, 1, 1);

        beerAbvInput = new QDoubleSpinBox(beerTab);
        beerAbvInput->setObjectName(QString::fromUtf8("beerAbvInput"));
        sizePolicy2.setHeightForWidth(beerAbvInput->sizePolicy().hasHeightForWidth());
        beerAbvInput->setSizePolicy(sizePolicy2);
        beerAbvInput->setMaximum(100.000000000000000);

        gridLayout_3->addWidget(beerAbvInput, 1, 2, 1, 1);

        beerSizeInput = new QDoubleSpinBox(beerTab);
        beerSizeInput->setObjectName(QString::fromUtf8("beerSizeInput"));
        beerSizeInput->setDecimals(1);
        beerSizeInput->setMaximum(10000.000000000000000);

        gridLayout_3->addWidget(beerSizeInput, 1, 1, 1, 1);

        beerSizeLabel = new QLabel(beerTab);
        beerSizeLabel->setObjectName(QString::fromUtf8("beerSizeLabel"));
        sizePolicy.setHeightForWidth(beerSizeLabel->sizePolicy().hasHeightForWidth());
        beerSizeLabel->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(beerSizeLabel, 0, 1, 1, 1);

        beerAbvLabel = new QLabel(beerTab);
        beerAbvLabel->setObjectName(QString::fromUtf8("beerAbvLabel"));
        sizePolicy.setHeightForWidth(beerAbvLabel->sizePolicy().hasHeightForWidth());
        beerAbvLabel->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(beerAbvLabel, 0, 2, 1, 1);

        beerRatingInput = new QSpinBox(beerTab);
        beerRatingInput->setObjectName(QString::fromUtf8("beerRatingInput"));
        sizePolicy2.setHeightForWidth(beerRatingInput->sizePolicy().hasHeightForWidth());
        beerRatingInput->setSizePolicy(sizePolicy2);
        beerRatingInput->setMaximum(10);

        gridLayout_3->addWidget(beerRatingInput, 1, 0, 1, 1);

        beerIbuLabel = new QLabel(beerTab);
        beerIbuLabel->setObjectName(QString::fromUtf8("beerIbuLabel"));
        sizePolicy.setHeightForWidth(beerIbuLabel->sizePolicy().hasHeightForWidth());
        beerIbuLabel->setSizePolicy(sizePolicy);
        beerIbuLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(beerIbuLabel, 0, 3, 1, 1);

        beerIbuInput = new QDoubleSpinBox(beerTab);
        beerIbuInput->setObjectName(QString::fromUtf8("beerIbuInput"));
        sizePolicy2.setHeightForWidth(beerIbuInput->sizePolicy().hasHeightForWidth());
        beerIbuInput->setSizePolicy(sizePolicy2);
        beerIbuInput->setDecimals(0);
        beerIbuInput->setMaximum(9999.000000000000000);

        gridLayout_3->addWidget(beerIbuInput, 1, 3, 1, 1);


        gridLayout_14->addLayout(gridLayout_3, 5, 0, 2, 1);

        beerNotesInput = new QTextEdit(beerTab);
        beerNotesInput->setObjectName(QString::fromUtf8("beerNotesInput"));
        sizePolicy.setHeightForWidth(beerNotesInput->sizePolicy().hasHeightForWidth());
        beerNotesInput->setSizePolicy(sizePolicy);
        beerNotesInput->setFocusPolicy(Qt::ClickFocus);

        gridLayout_14->addWidget(beerNotesInput, 9, 0, 3, 2);

        tabWidget->addTab(beerTab, QString());
        liquorTab = new QWidget();
        liquorTab->setObjectName(QString::fromUtf8("liquorTab"));
        gridLayout_8 = new QGridLayout(liquorTab);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        liquorDateInputLabel = new QLabel(liquorTab);
        liquorDateInputLabel->setObjectName(QString::fromUtf8("liquorDateInputLabel"));
        sizePolicy.setHeightForWidth(liquorDateInputLabel->sizePolicy().hasHeightForWidth());
        liquorDateInputLabel->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(liquorDateInputLabel, 0, 0, 1, 1);

        liquorNameInputLabel = new QLabel(liquorTab);
        liquorNameInputLabel->setObjectName(QString::fromUtf8("liquorNameInputLabel"));
        sizePolicy.setHeightForWidth(liquorNameInputLabel->sizePolicy().hasHeightForWidth());
        liquorNameInputLabel->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(liquorNameInputLabel, 0, 1, 1, 1);

        liquorDateInput = new QDateEdit(liquorTab);
        liquorDateInput->setObjectName(QString::fromUtf8("liquorDateInput"));
        sizePolicy2.setHeightForWidth(liquorDateInput->sizePolicy().hasHeightForWidth());
        liquorDateInput->setSizePolicy(sizePolicy2);
        liquorDateInput->setFocusPolicy(Qt::WheelFocus);
        liquorDateInput->setStyleSheet(QString::fromUtf8(""));
        liquorDateInput->setCalendarPopup(true);

        gridLayout_8->addWidget(liquorDateInput, 1, 0, 1, 1);

        liquorNameInput = new QComboBox(liquorTab);
        liquorNameInput->setObjectName(QString::fromUtf8("liquorNameInput"));
        liquorNameInput->setEditable(true);

        gridLayout_8->addWidget(liquorNameInput, 1, 1, 1, 1);

        liquorDistillerLabel = new QLabel(liquorTab);
        liquorDistillerLabel->setObjectName(QString::fromUtf8("liquorDistillerLabel"));
        sizePolicy.setHeightForWidth(liquorDistillerLabel->sizePolicy().hasHeightForWidth());
        liquorDistillerLabel->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(liquorDistillerLabel, 2, 0, 1, 1);

        liquorTypeLabel = new QLabel(liquorTab);
        liquorTypeLabel->setObjectName(QString::fromUtf8("liquorTypeLabel"));
        sizePolicy.setHeightForWidth(liquorTypeLabel->sizePolicy().hasHeightForWidth());
        liquorTypeLabel->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(liquorTypeLabel, 2, 1, 1, 1);

        liquorDistillerInput = new QComboBox(liquorTab);
        liquorDistillerInput->setObjectName(QString::fromUtf8("liquorDistillerInput"));
        sizePolicy2.setHeightForWidth(liquorDistillerInput->sizePolicy().hasHeightForWidth());
        liquorDistillerInput->setSizePolicy(sizePolicy2);
        liquorDistillerInput->setEditable(true);

        gridLayout_8->addWidget(liquorDistillerInput, 3, 0, 1, 1);

        liquorTypeInput = new QComboBox(liquorTab);
        liquorTypeInput->setObjectName(QString::fromUtf8("liquorTypeInput"));
        liquorTypeInput->setEditable(true);

        gridLayout_8->addWidget(liquorTypeInput, 3, 1, 1, 1);

        liquorSubtypeLabel = new QLabel(liquorTab);
        liquorSubtypeLabel->setObjectName(QString::fromUtf8("liquorSubtypeLabel"));

        gridLayout_8->addWidget(liquorSubtypeLabel, 4, 1, 1, 1);

        liquorSubtypeInput = new QComboBox(liquorTab);
        liquorSubtypeInput->setObjectName(QString::fromUtf8("liquorSubtypeInput"));
        liquorSubtypeInput->setEditable(true);

        gridLayout_8->addWidget(liquorSubtypeInput, 5, 1, 1, 1);

        liquorNotesLabel = new QLabel(liquorTab);
        liquorNotesLabel->setObjectName(QString::fromUtf8("liquorNotesLabel"));
        sizePolicy.setHeightForWidth(liquorNotesLabel->sizePolicy().hasHeightForWidth());
        liquorNotesLabel->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(liquorNotesLabel, 7, 0, 1, 1);

        liquorNotesInput = new QTextEdit(liquorTab);
        liquorNotesInput->setObjectName(QString::fromUtf8("liquorNotesInput"));
        sizePolicy.setHeightForWidth(liquorNotesInput->sizePolicy().hasHeightForWidth());
        liquorNotesInput->setSizePolicy(sizePolicy);
        liquorNotesInput->setFocusPolicy(Qt::ClickFocus);

        gridLayout_8->addWidget(liquorNotesInput, 8, 0, 1, 2);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        liquorAbvLabel = new QLabel(liquorTab);
        liquorAbvLabel->setObjectName(QString::fromUtf8("liquorAbvLabel"));
        sizePolicy.setHeightForWidth(liquorAbvLabel->sizePolicy().hasHeightForWidth());
        liquorAbvLabel->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(liquorAbvLabel, 0, 0, 1, 1);

        liquorRatingLabel = new QLabel(liquorTab);
        liquorRatingLabel->setObjectName(QString::fromUtf8("liquorRatingLabel"));
        sizePolicy.setHeightForWidth(liquorRatingLabel->sizePolicy().hasHeightForWidth());
        liquorRatingLabel->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(liquorRatingLabel, 0, 1, 1, 1);

        liquorSizeLabel = new QLabel(liquorTab);
        liquorSizeLabel->setObjectName(QString::fromUtf8("liquorSizeLabel"));
        sizePolicy.setHeightForWidth(liquorSizeLabel->sizePolicy().hasHeightForWidth());
        liquorSizeLabel->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(liquorSizeLabel, 0, 2, 1, 1);

        widget = new QWidget(liquorTab);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_6->addWidget(widget, 0, 3, 2, 1);

        liquorAbvInput = new QDoubleSpinBox(liquorTab);
        liquorAbvInput->setObjectName(QString::fromUtf8("liquorAbvInput"));
        sizePolicy2.setHeightForWidth(liquorAbvInput->sizePolicy().hasHeightForWidth());
        liquorAbvInput->setSizePolicy(sizePolicy2);
        liquorAbvInput->setMaximum(100.000000000000000);

        gridLayout_6->addWidget(liquorAbvInput, 1, 0, 1, 1);

        liquorRatingInput = new QSpinBox(liquorTab);
        liquorRatingInput->setObjectName(QString::fromUtf8("liquorRatingInput"));
        sizePolicy2.setHeightForWidth(liquorRatingInput->sizePolicy().hasHeightForWidth());
        liquorRatingInput->setSizePolicy(sizePolicy2);
        liquorRatingInput->setMaximum(10);

        gridLayout_6->addWidget(liquorRatingInput, 1, 1, 1, 1);

        liquorSizeInput = new QDoubleSpinBox(liquorTab);
        liquorSizeInput->setObjectName(QString::fromUtf8("liquorSizeInput"));
        sizePolicy2.setHeightForWidth(liquorSizeInput->sizePolicy().hasHeightForWidth());
        liquorSizeInput->setSizePolicy(sizePolicy2);
        liquorSizeInput->setDecimals(1);
        liquorSizeInput->setMaximum(10000.000000000000000);

        gridLayout_6->addWidget(liquorSizeInput, 1, 2, 1, 1);


        gridLayout_8->addLayout(gridLayout_6, 4, 0, 2, 1);

        tabWidget->addTab(liquorTab, QString());
        wineTab = new QWidget();
        wineTab->setObjectName(QString::fromUtf8("wineTab"));
        gridLayout_10 = new QGridLayout(wineTab);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        wineDateLabel = new QLabel(wineTab);
        wineDateLabel->setObjectName(QString::fromUtf8("wineDateLabel"));
        sizePolicy.setHeightForWidth(wineDateLabel->sizePolicy().hasHeightForWidth());
        wineDateLabel->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(wineDateLabel, 0, 0, 1, 1);

        wineNameLabel = new QLabel(wineTab);
        wineNameLabel->setObjectName(QString::fromUtf8("wineNameLabel"));
        sizePolicy.setHeightForWidth(wineNameLabel->sizePolicy().hasHeightForWidth());
        wineNameLabel->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(wineNameLabel, 0, 1, 1, 1);

        wineDateInput = new QDateEdit(wineTab);
        wineDateInput->setObjectName(QString::fromUtf8("wineDateInput"));
        sizePolicy2.setHeightForWidth(wineDateInput->sizePolicy().hasHeightForWidth());
        wineDateInput->setSizePolicy(sizePolicy2);
        wineDateInput->setMaximumSize(QSize(16777215, 16777215));
        wineDateInput->setFocusPolicy(Qt::WheelFocus);
        wineDateInput->setStyleSheet(QString::fromUtf8(""));
        wineDateInput->setCalendarPopup(true);

        gridLayout_10->addWidget(wineDateInput, 1, 0, 1, 1);

        wineNameInput = new QComboBox(wineTab);
        wineNameInput->setObjectName(QString::fromUtf8("wineNameInput"));
        wineNameInput->setEditable(true);

        gridLayout_10->addWidget(wineNameInput, 1, 1, 1, 1);

        wineryLabel = new QLabel(wineTab);
        wineryLabel->setObjectName(QString::fromUtf8("wineryLabel"));
        sizePolicy.setHeightForWidth(wineryLabel->sizePolicy().hasHeightForWidth());
        wineryLabel->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(wineryLabel, 2, 0, 1, 1);

        wineTypeLabel = new QLabel(wineTab);
        wineTypeLabel->setObjectName(QString::fromUtf8("wineTypeLabel"));
        sizePolicy.setHeightForWidth(wineTypeLabel->sizePolicy().hasHeightForWidth());
        wineTypeLabel->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(wineTypeLabel, 2, 1, 1, 1);

        wineryInput = new QComboBox(wineTab);
        wineryInput->setObjectName(QString::fromUtf8("wineryInput"));
        sizePolicy2.setHeightForWidth(wineryInput->sizePolicy().hasHeightForWidth());
        wineryInput->setSizePolicy(sizePolicy2);
        wineryInput->setEditable(true);

        gridLayout_10->addWidget(wineryInput, 3, 0, 1, 1);

        wineTypeInput = new QComboBox(wineTab);
        wineTypeInput->setObjectName(QString::fromUtf8("wineTypeInput"));
        wineTypeInput->setEditable(true);

        gridLayout_10->addWidget(wineTypeInput, 3, 1, 1, 1);

        wineSubtypeLabel = new QLabel(wineTab);
        wineSubtypeLabel->setObjectName(QString::fromUtf8("wineSubtypeLabel"));

        gridLayout_10->addWidget(wineSubtypeLabel, 4, 1, 1, 1);

        wineSubtypeInput = new QComboBox(wineTab);
        wineSubtypeInput->setObjectName(QString::fromUtf8("wineSubtypeInput"));
        wineSubtypeInput->setEditable(true);

        gridLayout_10->addWidget(wineSubtypeInput, 5, 1, 1, 1);

        wineNotesLabel = new QLabel(wineTab);
        wineNotesLabel->setObjectName(QString::fromUtf8("wineNotesLabel"));
        sizePolicy.setHeightForWidth(wineNotesLabel->sizePolicy().hasHeightForWidth());
        wineNotesLabel->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(wineNotesLabel, 7, 0, 1, 1);

        wineNotesInput = new QTextEdit(wineTab);
        wineNotesInput->setObjectName(QString::fromUtf8("wineNotesInput"));
        sizePolicy.setHeightForWidth(wineNotesInput->sizePolicy().hasHeightForWidth());
        wineNotesInput->setSizePolicy(sizePolicy);
        wineNotesInput->setFocusPolicy(Qt::ClickFocus);

        gridLayout_10->addWidget(wineNotesInput, 8, 0, 1, 2);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        wineVintageLabel = new QLabel(wineTab);
        wineVintageLabel->setObjectName(QString::fromUtf8("wineVintageLabel"));

        gridLayout_9->addWidget(wineVintageLabel, 0, 0, 1, 1);

        wineAbvLabel = new QLabel(wineTab);
        wineAbvLabel->setObjectName(QString::fromUtf8("wineAbvLabel"));
        sizePolicy.setHeightForWidth(wineAbvLabel->sizePolicy().hasHeightForWidth());
        wineAbvLabel->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(wineAbvLabel, 0, 1, 1, 1);

        wineRatingLabel = new QLabel(wineTab);
        wineRatingLabel->setObjectName(QString::fromUtf8("wineRatingLabel"));
        sizePolicy.setHeightForWidth(wineRatingLabel->sizePolicy().hasHeightForWidth());
        wineRatingLabel->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(wineRatingLabel, 0, 2, 1, 1);

        wineSizeLabel = new QLabel(wineTab);
        wineSizeLabel->setObjectName(QString::fromUtf8("wineSizeLabel"));
        sizePolicy.setHeightForWidth(wineSizeLabel->sizePolicy().hasHeightForWidth());
        wineSizeLabel->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(wineSizeLabel, 0, 3, 1, 1);

        wineVintage = new QSpinBox(wineTab);
        wineVintage->setObjectName(QString::fromUtf8("wineVintage"));
        sizePolicy2.setHeightForWidth(wineVintage->sizePolicy().hasHeightForWidth());
        wineVintage->setSizePolicy(sizePolicy2);
        wineVintage->setMaximum(9999);
        wineVintage->setValue(2000);

        gridLayout_9->addWidget(wineVintage, 1, 0, 1, 1);

        wineAbvInput = new QDoubleSpinBox(wineTab);
        wineAbvInput->setObjectName(QString::fromUtf8("wineAbvInput"));
        sizePolicy2.setHeightForWidth(wineAbvInput->sizePolicy().hasHeightForWidth());
        wineAbvInput->setSizePolicy(sizePolicy2);
        wineAbvInput->setMaximum(100.000000000000000);

        gridLayout_9->addWidget(wineAbvInput, 1, 1, 1, 1);

        wineRatingInput = new QSpinBox(wineTab);
        wineRatingInput->setObjectName(QString::fromUtf8("wineRatingInput"));
        sizePolicy2.setHeightForWidth(wineRatingInput->sizePolicy().hasHeightForWidth());
        wineRatingInput->setSizePolicy(sizePolicy2);
        wineRatingInput->setMaximum(10);

        gridLayout_9->addWidget(wineRatingInput, 1, 2, 1, 1);

        wineSizeInput = new QDoubleSpinBox(wineTab);
        wineSizeInput->setObjectName(QString::fromUtf8("wineSizeInput"));
        sizePolicy2.setHeightForWidth(wineSizeInput->sizePolicy().hasHeightForWidth());
        wineSizeInput->setSizePolicy(sizePolicy2);
        wineSizeInput->setDecimals(1);
        wineSizeInput->setMaximum(10000.000000000000000);

        gridLayout_9->addWidget(wineSizeInput, 1, 3, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 4, 0, 2, 1);

        tabWidget->addTab(wineTab, QString());

        gridLayout_4->addWidget(tabWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1006, 24));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(tabWidget, beerDateInput);
        QWidget::setTabOrder(beerDateInput, beerNameInput);
        QWidget::setTabOrder(beerNameInput, beerBreweryInput);
        QWidget::setTabOrder(beerBreweryInput, beerTypeInput);
        QWidget::setTabOrder(beerTypeInput, beerRatingInput);
        QWidget::setTabOrder(beerRatingInput, beerSizeInput);
        QWidget::setTabOrder(beerSizeInput, liquorDateInput);
        QWidget::setTabOrder(liquorDateInput, liquorNameInput);
        QWidget::setTabOrder(liquorNameInput, liquorDistillerInput);
        QWidget::setTabOrder(liquorDistillerInput, liquorTypeInput);
        QWidget::setTabOrder(liquorTypeInput, liquorSubtypeInput);
        QWidget::setTabOrder(liquorSubtypeInput, liquorAbvInput);
        QWidget::setTabOrder(liquorAbvInput, liquorRatingInput);
        QWidget::setTabOrder(liquorRatingInput, liquorSizeInput);
        QWidget::setTabOrder(liquorSizeInput, wineDateInput);
        QWidget::setTabOrder(wineDateInput, wineNameInput);
        QWidget::setTabOrder(wineNameInput, wineryInput);
        QWidget::setTabOrder(wineryInput, wineTypeInput);
        QWidget::setTabOrder(wineTypeInput, wineSubtypeInput);
        QWidget::setTabOrder(wineSubtypeInput, wineVintage);
        QWidget::setTabOrder(wineVintage, wineAbvInput);
        QWidget::setTabOrder(wineAbvInput, wineRatingInput);
        QWidget::setTabOrder(wineRatingInput, wineSizeInput);
        QWidget::setTabOrder(wineSizeInput, deleteRowButton);
        QWidget::setTabOrder(deleteRowButton, clearFieldsButton);
        QWidget::setTabOrder(clearFieldsButton, submitRowButton);
        QWidget::setTabOrder(submitRowButton, filterTextInput);
        QWidget::setTabOrder(filterTextInput, filterCategoryInput);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BuzzBot", nullptr));
        stdDrinksTodayLabel->setText(QCoreApplication::translate("MainWindow", "Std. drinks today:", nullptr));
        favoriteBeerLabel->setText(QCoreApplication::translate("MainWindow", "Most frequent drink:", nullptr));
        daysConsecutiveLabel->setText(QCoreApplication::translate("MainWindow", "Days consumed\n"
"consecutively:", nullptr));
        favoriteBreweryLabel->setText(QCoreApplication::translate("MainWindow", "Most frequent producer:", nullptr));
        volAlcoholConsumedLabel->setText(QCoreApplication::translate("MainWindow", "Oz. alcohol consumed:", nullptr));
        drinksLeftOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        consecutiveConsumptionLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        avgAbvDrinkOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        avgIbuDrinkOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        favoriteTypeOutput->setText(QCoreApplication::translate("MainWindow", "IPA", nullptr));
        volAlcoholConsumedOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        drinksThisWeekOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        drinksThisWeekLabel->setText(QCoreApplication::translate("MainWindow", "Std. drinks this week:", nullptr));
        volAlcoholRemainingOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        favoriteDrinkOutput->setText(QCoreApplication::translate("MainWindow", "Everything Rhymes\n"
"with Orange", nullptr));
        stdDrinksTodayOutput->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        favoriteProducerOutput->setText(QCoreApplication::translate("MainWindow", "Roughtail Brewing Co.", nullptr));
        favoriteTypeLabel->setText(QCoreApplication::translate("MainWindow", "Most frequent type:", nullptr));
        avgAbvDrinkLabel->setText(QCoreApplication::translate("MainWindow", "Average ABV per drink:", nullptr));
        drinksLeftLabel->setText(QCoreApplication::translate("MainWindow", "Std. drinks remaining:", nullptr));
        volAlcoholRemainingLabel->setText(QCoreApplication::translate("MainWindow", "Oz. alcohol remaining:", nullptr));
        averageIbuDrinkLabel->setText(QCoreApplication::translate("MainWindow", "Average IBU per beer:", nullptr));
        statsLabel->setText(QCoreApplication::translate("MainWindow", "Stats", nullptr));
        deleteRowButton->setText(QCoreApplication::translate("MainWindow", "Delete Row...", nullptr));
        clearFieldsButton->setText(QCoreApplication::translate("MainWindow", "Clear Selections", nullptr));
        submitRowButton->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        drinkDataLabel->setText(QCoreApplication::translate("MainWindow", "Drink Data", nullptr));
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
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "S. Drinks", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = drinkLogTable->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Rating", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = drinkLogTable->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = drinkLogTable->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Timestamp", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = drinkLogTable->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Sort", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = drinkLogTable->verticalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "1", nullptr));

        const bool __sortingEnabled = drinkLogTable->isSortingEnabled();
        drinkLogTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem14 = drinkLogTable->item(0, 0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "09/07/2020", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = drinkLogTable->item(0, 1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Everything Rhymes with Orange", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = drinkLogTable->item(0, 2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "IPA", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = drinkLogTable->item(0, 4);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Roughtail Brewing", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = drinkLogTable->item(0, 5);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "8.0", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = drinkLogTable->item(0, 6);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "65", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = drinkLogTable->item(0, 7);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        drinkLogTable->setSortingEnabled(__sortingEnabled);

        filterCategoryLabel->setText(QCoreApplication::translate("MainWindow", "Filter category:", nullptr));
        filterLabel->setText(QCoreApplication::translate("MainWindow", "Filter:", nullptr));
        beerSubtypeLabel->setText(QCoreApplication::translate("MainWindow", "Subtype:", nullptr));
        beerBreweryLabel->setText(QCoreApplication::translate("MainWindow", "Brewery:", nullptr));
        beerTypeLabel->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        drinkDateLabel->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        beerDateInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "MMM/dd/yyyy", nullptr));
        beerNameLabel->setText(QCoreApplication::translate("MainWindow", "Name:", nullptr));
        beerNotesLabel->setText(QCoreApplication::translate("MainWindow", "Notes:", nullptr));
        beerRatingLabel->setText(QCoreApplication::translate("MainWindow", "Rating:", nullptr));
        beerSizeLabel->setText(QCoreApplication::translate("MainWindow", "Size (oz):", nullptr));
        beerAbvLabel->setText(QCoreApplication::translate("MainWindow", "ABV:", nullptr));
        beerIbuLabel->setText(QCoreApplication::translate("MainWindow", "IBU:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(beerTab), QCoreApplication::translate("MainWindow", "Beer", nullptr));
        liquorDateInputLabel->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        liquorNameInputLabel->setText(QCoreApplication::translate("MainWindow", "Name:", nullptr));
        liquorDateInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "MMM/dd/yyyy", nullptr));
        liquorDistillerLabel->setText(QCoreApplication::translate("MainWindow", "Distillery:", nullptr));
        liquorTypeLabel->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        liquorSubtypeLabel->setText(QCoreApplication::translate("MainWindow", "Subtype:", nullptr));
        liquorNotesLabel->setText(QCoreApplication::translate("MainWindow", "Notes:", nullptr));
        liquorAbvLabel->setText(QCoreApplication::translate("MainWindow", "ABV:", nullptr));
        liquorRatingLabel->setText(QCoreApplication::translate("MainWindow", "Rating:", nullptr));
        liquorSizeLabel->setText(QCoreApplication::translate("MainWindow", "Size (oz):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(liquorTab), QCoreApplication::translate("MainWindow", "Liquor", nullptr));
        wineDateLabel->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        wineNameLabel->setText(QCoreApplication::translate("MainWindow", "Name:", nullptr));
        wineDateInput->setDisplayFormat(QCoreApplication::translate("MainWindow", "MMM/dd/yyyy", nullptr));
        wineryLabel->setText(QCoreApplication::translate("MainWindow", "Winery:", nullptr));
        wineTypeLabel->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        wineSubtypeLabel->setText(QCoreApplication::translate("MainWindow", "Subtype:", nullptr));
        wineNotesLabel->setText(QCoreApplication::translate("MainWindow", "Notes:", nullptr));
        wineVintageLabel->setText(QCoreApplication::translate("MainWindow", "Vintage:", nullptr));
        wineAbvLabel->setText(QCoreApplication::translate("MainWindow", "ABV:", nullptr));
        wineRatingLabel->setText(QCoreApplication::translate("MainWindow", "Rating:", nullptr));
        wineSizeLabel->setText(QCoreApplication::translate("MainWindow", "Size (oz):", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(wineTab), QCoreApplication::translate("MainWindow", "Wine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
