/********************************************************************************
** Form generated from reading UI file 'LOMView.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOMVIEW_H
#define UI_LOMVIEW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot/qcustomplot.h>
#include "inc/EndcapWidget.h"

QT_BEGIN_NAMESPACE

class Ui_LOMView
{
public:
    QWidget *centralWidget;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFormLayout *formLayout;
    QLabel *thresholdFELabel;
    QLabel *thresholdBELabel;
    QLabel *coincidenceDurationLabel;
    QSpinBox *spinBoxCoinDur;
    QLabel *backgroundThresholdLabel;
    QSpinBox *spinBoxBkg;
    QLabel *label_4;
    QPushButton *pushButtonSetThresholds;
    QDoubleSpinBox *spinBoxAmplFWD;
    QDoubleSpinBox *spinBoxAmplBWD;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QFormLayout *formLayout_3;
    QLabel *updFreqLabel;
    QSpinBox *spinBoxUpdFreq;
    QLabel *redrawFreqLabel;
    QSpinBox *spinBoxRedrawFreq;
    QLabel *label_5;
    QPushButton *pushButton_4;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *layoutWidget3;
    QVBoxLayout *eventInfoLayout;
    QLabel *label_2;
    QFormLayout *formLayout_2;
    QLabel *dLabel;
    QLineEdit *dLineEdit;
    QLabel *deadTimeLabel;
    QLineEdit *deadTimeLineEdit;
    QLabel *vetoTimeLabel;
    QLineEdit *vetoTimeLineEdit;
    QLabel *bhabhaEventsLabel;
    QLineEdit *bhabhaEventsLineEdit;
    QLabel *backgroundEventsLabel;
    QLineEdit *backgroundEventsLineEdit;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    EndcapWidget *fwdEndcapWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    EndcapWidget *fwdEndcapWidget_2;
    QCustomPlot *amplFWDWidget;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLabel *label_10;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLabel *label_11;
    QCustomPlot *amplBWDWidget;
    QCustomPlot *coinWidget;
    QLabel *fwdWidgetLabel;
    QLabel *bwdWidgetLabel;
    QLabel *coinWidgetLabel;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_4;
    QCheckBox *checkBoxHitSector;
    QLabel *redrawFreqLabel_2;
    QComboBox *fwdSectorCB;
    QLabel *redrawFreqLabel_3;
    QComboBox *bwdSectorCB;
    QPushButton *pushButtonSetThresholds_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LOMView)
    {
        if (LOMView->objectName().isEmpty())
            LOMView->setObjectName(QStringLiteral("LOMView"));
        LOMView->resize(1195, 841);
        LOMView->setMinimumSize(QSize(800, 600));
        LOMView->setAutoFillBackground(false);
        LOMView->setLocale(QLocale(QLocale::Estonian, QLocale::Estonia));
        centralWidget = new QWidget(LOMView);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(9, 9, 241, 353));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        thresholdFELabel = new QLabel(layoutWidget);
        thresholdFELabel->setObjectName(QStringLiteral("thresholdFELabel"));
        QFont font1;
        font1.setPointSize(12);
        thresholdFELabel->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, thresholdFELabel);

        thresholdBELabel = new QLabel(layoutWidget);
        thresholdBELabel->setObjectName(QStringLiteral("thresholdBELabel"));
        thresholdBELabel->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, thresholdBELabel);

        coincidenceDurationLabel = new QLabel(layoutWidget);
        coincidenceDurationLabel->setObjectName(QStringLiteral("coincidenceDurationLabel"));
        coincidenceDurationLabel->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, coincidenceDurationLabel);

        spinBoxCoinDur = new QSpinBox(layoutWidget);
        spinBoxCoinDur->setObjectName(QStringLiteral("spinBoxCoinDur"));
        spinBoxCoinDur->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxCoinDur);

        backgroundThresholdLabel = new QLabel(layoutWidget);
        backgroundThresholdLabel->setObjectName(QStringLiteral("backgroundThresholdLabel"));
        backgroundThresholdLabel->setFont(font1);

        formLayout->setWidget(3, QFormLayout::LabelRole, backgroundThresholdLabel);

        spinBoxBkg = new QSpinBox(layoutWidget);
        spinBoxBkg->setObjectName(QStringLiteral("spinBoxBkg"));
        spinBoxBkg->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(3, QFormLayout::FieldRole, spinBoxBkg);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        pushButtonSetThresholds = new QPushButton(layoutWidget);
        pushButtonSetThresholds->setObjectName(QStringLiteral("pushButtonSetThresholds"));

        formLayout->setWidget(4, QFormLayout::FieldRole, pushButtonSetThresholds);

        spinBoxAmplFWD = new QDoubleSpinBox(layoutWidget);
        spinBoxAmplFWD->setObjectName(QStringLiteral("spinBoxAmplFWD"));
        spinBoxAmplFWD->setMaximum(10);
        spinBoxAmplFWD->setSingleStep(0.5);
        spinBoxAmplFWD->setValue(3);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxAmplFWD);

        spinBoxAmplBWD = new QDoubleSpinBox(layoutWidget);
        spinBoxAmplBWD->setObjectName(QStringLiteral("spinBoxAmplBWD"));
        spinBoxAmplBWD->setMaximum(10);
        spinBoxAmplBWD->setSingleStep(0.5);
        spinBoxAmplBWD->setValue(1);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxAmplBWD);


        verticalLayout->addLayout(formLayout);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout_3->addWidget(label_3);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        updFreqLabel = new QLabel(layoutWidget1);
        updFreqLabel->setObjectName(QStringLiteral("updFreqLabel"));
        updFreqLabel->setFont(font1);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, updFreqLabel);

        spinBoxUpdFreq = new QSpinBox(layoutWidget1);
        spinBoxUpdFreq->setObjectName(QStringLiteral("spinBoxUpdFreq"));
        spinBoxUpdFreq->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxUpdFreq->setMaximum(1000);
        spinBoxUpdFreq->setValue(100);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, spinBoxUpdFreq);

        redrawFreqLabel = new QLabel(layoutWidget1);
        redrawFreqLabel->setObjectName(QStringLiteral("redrawFreqLabel"));
        redrawFreqLabel->setFont(font1);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, redrawFreqLabel);

        spinBoxRedrawFreq = new QSpinBox(layoutWidget1);
        spinBoxRedrawFreq->setObjectName(QStringLiteral("spinBoxRedrawFreq"));
        spinBoxRedrawFreq->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxRedrawFreq->setMaximum(1000);
        spinBoxRedrawFreq->setValue(100);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, spinBoxRedrawFreq);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_5);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, pushButton_4);


        verticalLayout_3->addLayout(formLayout_3);

        splitter->addWidget(layoutWidget1);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        splitter->addWidget(layoutWidget2);
        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(310, 240, 221, 195));
        eventInfoLayout = new QVBoxLayout(layoutWidget3);
        eventInfoLayout->setSpacing(6);
        eventInfoLayout->setContentsMargins(11, 11, 11, 11);
        eventInfoLayout->setObjectName(QStringLiteral("eventInfoLayout"));
        eventInfoLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        eventInfoLayout->addWidget(label_2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        dLabel = new QLabel(layoutWidget3);
        dLabel->setObjectName(QStringLiteral("dLabel"));
        dLabel->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, dLabel);

        dLineEdit = new QLineEdit(layoutWidget3);
        dLineEdit->setObjectName(QStringLiteral("dLineEdit"));
        dLineEdit->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, dLineEdit);

        deadTimeLabel = new QLabel(layoutWidget3);
        deadTimeLabel->setObjectName(QStringLiteral("deadTimeLabel"));
        deadTimeLabel->setFont(font1);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, deadTimeLabel);

        deadTimeLineEdit = new QLineEdit(layoutWidget3);
        deadTimeLineEdit->setObjectName(QStringLiteral("deadTimeLineEdit"));
        deadTimeLineEdit->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, deadTimeLineEdit);

        vetoTimeLabel = new QLabel(layoutWidget3);
        vetoTimeLabel->setObjectName(QStringLiteral("vetoTimeLabel"));
        vetoTimeLabel->setFont(font1);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, vetoTimeLabel);

        vetoTimeLineEdit = new QLineEdit(layoutWidget3);
        vetoTimeLineEdit->setObjectName(QStringLiteral("vetoTimeLineEdit"));
        vetoTimeLineEdit->setReadOnly(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, vetoTimeLineEdit);

        bhabhaEventsLabel = new QLabel(layoutWidget3);
        bhabhaEventsLabel->setObjectName(QStringLiteral("bhabhaEventsLabel"));
        bhabhaEventsLabel->setFont(font1);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, bhabhaEventsLabel);

        bhabhaEventsLineEdit = new QLineEdit(layoutWidget3);
        bhabhaEventsLineEdit->setObjectName(QStringLiteral("bhabhaEventsLineEdit"));
        bhabhaEventsLineEdit->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, bhabhaEventsLineEdit);

        backgroundEventsLabel = new QLabel(layoutWidget3);
        backgroundEventsLabel->setObjectName(QStringLiteral("backgroundEventsLabel"));
        backgroundEventsLabel->setFont(font1);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, backgroundEventsLabel);

        backgroundEventsLineEdit = new QLineEdit(layoutWidget3);
        backgroundEventsLineEdit->setObjectName(QStringLiteral("backgroundEventsLineEdit"));
        backgroundEventsLineEdit->setReadOnly(true);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, backgroundEventsLineEdit);


        eventInfoLayout->addLayout(formLayout_2);

        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(40, 460, 272, 162));
        horizontalLayout = new QHBoxLayout(layoutWidget4);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_6 = new QLabel(layoutWidget4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(0, 17));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label_6->setFont(font2);

        verticalLayout_2->addWidget(label_6);

        fwdEndcapWidget = new EndcapWidget(layoutWidget4);
        fwdEndcapWidget->setObjectName(QStringLiteral("fwdEndcapWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fwdEndcapWidget->sizePolicy().hasHeightForWidth());
        fwdEndcapWidget->setSizePolicy(sizePolicy);
        fwdEndcapWidget->setMinimumSize(QSize(130, 130));

        verticalLayout_2->addWidget(fwdEndcapWidget);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_7 = new QLabel(layoutWidget4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(0, 17));
        label_7->setFont(font2);

        verticalLayout_4->addWidget(label_7);

        fwdEndcapWidget_2 = new EndcapWidget(layoutWidget4);
        fwdEndcapWidget_2->setObjectName(QStringLiteral("fwdEndcapWidget_2"));
        sizePolicy.setHeightForWidth(fwdEndcapWidget_2->sizePolicy().hasHeightForWidth());
        fwdEndcapWidget_2->setSizePolicy(sizePolicy);
        fwdEndcapWidget_2->setMinimumSize(QSize(130, 130));

        verticalLayout_4->addWidget(fwdEndcapWidget_2);


        horizontalLayout->addLayout(verticalLayout_4);

        amplFWDWidget = new QCustomPlot(centralWidget);
        amplFWDWidget->setObjectName(QStringLiteral("amplFWDWidget"));
        amplFWDWidget->setGeometry(QRect(610, 70, 411, 151));
        layoutWidget5 = new QWidget(centralWidget);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(40, 630, 132, 24));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget5);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font3;
        font3.setFamily(QStringLiteral("Noto Sans"));
        font3.setPointSize(12);
        label_8->setFont(font3);

        horizontalLayout_3->addWidget(label_8);

        label_10 = new QLabel(layoutWidget5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font1);

        horizontalLayout_3->addWidget(label_10);

        layoutWidget6 = new QWidget(centralWidget);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(180, 630, 124, 24));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget6);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font3);

        horizontalLayout_4->addWidget(label_9);

        label_11 = new QLabel(layoutWidget6);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font1);

        horizontalLayout_4->addWidget(label_11);

        amplBWDWidget = new QCustomPlot(centralWidget);
        amplBWDWidget->setObjectName(QStringLiteral("amplBWDWidget"));
        amplBWDWidget->setGeometry(QRect(610, 270, 411, 151));
        coinWidget = new QCustomPlot(centralWidget);
        coinWidget->setObjectName(QStringLiteral("coinWidget"));
        coinWidget->setGeometry(QRect(610, 460, 411, 151));
        fwdWidgetLabel = new QLabel(centralWidget);
        fwdWidgetLabel->setObjectName(QStringLiteral("fwdWidgetLabel"));
        fwdWidgetLabel->setGeometry(QRect(610, 50, 411, 17));
        fwdWidgetLabel->setFont(font);
        bwdWidgetLabel = new QLabel(centralWidget);
        bwdWidgetLabel->setObjectName(QStringLiteral("bwdWidgetLabel"));
        bwdWidgetLabel->setGeometry(QRect(610, 240, 411, 21));
        bwdWidgetLabel->setFont(font);
        coinWidgetLabel = new QLabel(centralWidget);
        coinWidgetLabel->setObjectName(QStringLiteral("coinWidgetLabel"));
        coinWidgetLabel->setGeometry(QRect(610, 430, 411, 31));
        coinWidgetLabel->setFont(font);
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(610, 620, 211, 146));
        formLayout_4 = new QFormLayout(formLayoutWidget);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setContentsMargins(0, 0, 0, 0);
        checkBoxHitSector = new QCheckBox(formLayoutWidget);
        checkBoxHitSector->setObjectName(QStringLiteral("checkBoxHitSector"));
        checkBoxHitSector->setFont(font1);

        formLayout_4->setWidget(1, QFormLayout::LabelRole, checkBoxHitSector);

        redrawFreqLabel_2 = new QLabel(formLayoutWidget);
        redrawFreqLabel_2->setObjectName(QStringLiteral("redrawFreqLabel_2"));
        redrawFreqLabel_2->setFont(font1);

        formLayout_4->setWidget(2, QFormLayout::LabelRole, redrawFreqLabel_2);

        fwdSectorCB = new QComboBox(formLayoutWidget);
        fwdSectorCB->setObjectName(QStringLiteral("fwdSectorCB"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, fwdSectorCB);

        redrawFreqLabel_3 = new QLabel(formLayoutWidget);
        redrawFreqLabel_3->setObjectName(QStringLiteral("redrawFreqLabel_3"));
        redrawFreqLabel_3->setFont(font1);

        formLayout_4->setWidget(3, QFormLayout::LabelRole, redrawFreqLabel_3);

        bwdSectorCB = new QComboBox(formLayoutWidget);
        bwdSectorCB->setObjectName(QStringLiteral("bwdSectorCB"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, bwdSectorCB);

        pushButtonSetThresholds_2 = new QPushButton(formLayoutWidget);
        pushButtonSetThresholds_2->setObjectName(QStringLiteral("pushButtonSetThresholds_2"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, pushButtonSetThresholds_2);

        LOMView->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LOMView);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1195, 27));
        LOMView->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LOMView);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LOMView->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LOMView);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LOMView->setStatusBar(statusBar);

        retranslateUi(LOMView);
        QObject::connect(pushButtonSetThresholds, SIGNAL(clicked()), LOMView, SLOT(UpdateThresholds()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), LOMView, SLOT(UpdateSettings()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), LOMView, SLOT(StartUpdates()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), LOMView, SLOT(StopUpdates()));
        QObject::connect(checkBoxHitSector, SIGNAL(clicked()), LOMView, SLOT(ChangePlottersMode()));

        QMetaObject::connectSlotsByName(LOMView);
    } // setupUi

    void retranslateUi(QMainWindow *LOMView)
    {
        LOMView->setWindowTitle(QApplication::translate("LOMView", "Luminosity Online Monitor", 0));
        label->setText(QApplication::translate("LOMView", "Thresholds", 0));
        thresholdFELabel->setText(QApplication::translate("LOMView", "Amplitude (FWD), GeV", 0));
        thresholdBELabel->setText(QApplication::translate("LOMView", "Amplitude (BWD), GeV", 0));
        coincidenceDurationLabel->setText(QApplication::translate("LOMView", "Coincidence duration ", 0));
        backgroundThresholdLabel->setText(QApplication::translate("LOMView", "Hit", 0));
        label_4->setText(QString());
        pushButtonSetThresholds->setText(QApplication::translate("LOMView", "Set", 0));
        label_3->setText(QApplication::translate("LOMView", "Settings", 0));
        updFreqLabel->setText(QApplication::translate("LOMView", "Update frequence (Hz)", 0));
        redrawFreqLabel->setText(QApplication::translate("LOMView", "Redraw frequence (Hz)", 0));
        label_5->setText(QString());
        pushButton_4->setText(QApplication::translate("LOMView", "Set", 0));
        pushButton_2->setText(QApplication::translate("LOMView", "Start", 0));
        pushButton_3->setText(QApplication::translate("LOMView", "Stop", 0));
        label_2->setText(QApplication::translate("LOMView", "Event info", 0));
        dLabel->setText(QApplication::translate("LOMView", "DeltaT", 0));
        dLineEdit->setText(QApplication::translate("LOMView", "1 s", 0));
        deadTimeLabel->setText(QApplication::translate("LOMView", "Dead time", 0));
        deadTimeLineEdit->setText(QApplication::translate("LOMView", "1 us", 0));
        vetoTimeLabel->setText(QApplication::translate("LOMView", "Veto time", 0));
        vetoTimeLineEdit->setText(QApplication::translate("LOMView", "2 us", 0));
        bhabhaEventsLabel->setText(QApplication::translate("LOMView", "Bhabha events", 0));
        bhabhaEventsLineEdit->setText(QApplication::translate("LOMView", "0", 0));
        backgroundEventsLabel->setText(QApplication::translate("LOMView", "Background events", 0));
        backgroundEventsLineEdit->setText(QApplication::translate("LOMView", "0", 0));
        label_6->setText(QApplication::translate("LOMView", "FWD", 0));
        label_7->setText(QApplication::translate("LOMView", "BWD", 0));
        label_8->setText(QApplication::translate("LOMView", "Hit sector:", 0));
        label_10->setText(QApplication::translate("LOMView", "none", 0));
        label_9->setText(QApplication::translate("LOMView", "Hit sector:", 0));
        label_11->setText(QApplication::translate("LOMView", "none", 0));
        fwdWidgetLabel->setText(QApplication::translate("LOMView", "FWD", 0));
        bwdWidgetLabel->setText(QApplication::translate("LOMView", "BWD", 0));
        coinWidgetLabel->setText(QApplication::translate("LOMView", "Coincidence region", 0));
        checkBoxHitSector->setText(QApplication::translate("LOMView", "Show hit sectors", 0));
        redrawFreqLabel_2->setText(QApplication::translate("LOMView", "FWD Sector:", 0));
        fwdSectorCB->clear();
        fwdSectorCB->insertItems(0, QStringList()
         << QApplication::translate("LOMView", "1", 0)
         << QApplication::translate("LOMView", "2", 0)
         << QApplication::translate("LOMView", "3", 0)
         << QApplication::translate("LOMView", "4", 0)
         << QApplication::translate("LOMView", "5", 0)
         << QApplication::translate("LOMView", "6", 0)
         << QApplication::translate("LOMView", "7", 0)
         << QApplication::translate("LOMView", "8", 0)
         << QApplication::translate("LOMView", "9", 0)
         << QApplication::translate("LOMView", "10", 0)
         << QApplication::translate("LOMView", "11", 0)
         << QApplication::translate("LOMView", "12", 0)
         << QApplication::translate("LOMView", "13", 0)
         << QApplication::translate("LOMView", "14", 0)
         << QApplication::translate("LOMView", "15", 0)
         << QApplication::translate("LOMView", "16", 0)
        );
        redrawFreqLabel_3->setText(QApplication::translate("LOMView", "BWD Sector:", 0));
        bwdSectorCB->clear();
        bwdSectorCB->insertItems(0, QStringList()
         << QApplication::translate("LOMView", "1", 0)
         << QApplication::translate("LOMView", "2", 0)
         << QApplication::translate("LOMView", "3", 0)
         << QApplication::translate("LOMView", "4", 0)
         << QApplication::translate("LOMView", "5", 0)
         << QApplication::translate("LOMView", "6", 0)
         << QApplication::translate("LOMView", "7", 0)
         << QApplication::translate("LOMView", "8", 0)
         << QApplication::translate("LOMView", "9", 0)
         << QApplication::translate("LOMView", "10", 0)
         << QApplication::translate("LOMView", "11", 0)
         << QApplication::translate("LOMView", "12", 0)
         << QApplication::translate("LOMView", "13", 0)
         << QApplication::translate("LOMView", "14", 0)
         << QApplication::translate("LOMView", "15", 0)
         << QApplication::translate("LOMView", "16", 0)
        );
        pushButtonSetThresholds_2->setText(QApplication::translate("LOMView", "Update", 0));
    } // retranslateUi

};

namespace Ui {
    class LOMView: public Ui_LOMView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOMVIEW_H
