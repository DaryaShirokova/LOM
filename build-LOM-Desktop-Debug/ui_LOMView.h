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
    QSpinBox *spinBoxAmplFWD;
    QLabel *thresholdBELabel;
    QSpinBox *spinBoxAmplBWD;
    QLabel *coincidenceDurationLabel;
    QSpinBox *spinBoxCoinDur;
    QLabel *backgroundThresholdLabel;
    QSpinBox *spinBoxBkg;
    QLabel *label_4;
    QPushButton *pushButton;
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
    QLabel *label_8;
    QLabel *label_9;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    EndcapWidget *fwdEndcapWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    EndcapWidget *fwdEndcapWidget_2;
    QCustomPlot *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LOMView)
    {
        if (LOMView->objectName().isEmpty())
            LOMView->setObjectName(QStringLiteral("LOMView"));
        LOMView->resize(800, 600);
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

        spinBoxAmplFWD = new QSpinBox(layoutWidget);
        spinBoxAmplFWD->setObjectName(QStringLiteral("spinBoxAmplFWD"));
        spinBoxAmplFWD->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxAmplFWD->setMaximum(1000);
        spinBoxAmplFWD->setValue(100);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxAmplFWD);

        thresholdBELabel = new QLabel(layoutWidget);
        thresholdBELabel->setObjectName(QStringLiteral("thresholdBELabel"));
        thresholdBELabel->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, thresholdBELabel);

        spinBoxAmplBWD = new QSpinBox(layoutWidget);
        spinBoxAmplBWD->setObjectName(QStringLiteral("spinBoxAmplBWD"));
        spinBoxAmplBWD->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxAmplBWD->setMaximum(1000);
        spinBoxAmplBWD->setValue(100);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxAmplBWD);

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

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(4, QFormLayout::FieldRole, pushButton);


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
        layoutWidget3->setGeometry(QRect(560, 10, 221, 195));
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

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(280, 180, 71, 17));
        QFont font2;
        font2.setFamily(QStringLiteral("aakar"));
        font2.setPointSize(12);
        label_8->setFont(font2);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(420, 180, 71, 17));
        label_9->setFont(font2);
        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(280, 10, 272, 162));
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
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        label_6->setFont(font3);

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
        label_7->setFont(font3);

        verticalLayout_4->addWidget(label_7);

        fwdEndcapWidget_2 = new EndcapWidget(layoutWidget4);
        fwdEndcapWidget_2->setObjectName(QStringLiteral("fwdEndcapWidget_2"));
        sizePolicy.setHeightForWidth(fwdEndcapWidget_2->sizePolicy().hasHeightForWidth());
        fwdEndcapWidget_2->setSizePolicy(sizePolicy);
        fwdEndcapWidget_2->setMinimumSize(QSize(130, 130));

        verticalLayout_4->addWidget(fwdEndcapWidget_2);


        horizontalLayout->addLayout(verticalLayout_4);

        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(320, 240, 341, 111));
        LOMView->setCentralWidget(centralWidget);
        splitter->raise();
        layoutWidget->raise();
        label_8->raise();
        label_9->raise();
        layoutWidget->raise();
        fwdEndcapWidget->raise();
        widget->raise();
        menuBar = new QMenuBar(LOMView);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 27));
        LOMView->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LOMView);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LOMView->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LOMView);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LOMView->setStatusBar(statusBar);

        retranslateUi(LOMView);

        QMetaObject::connectSlotsByName(LOMView);
    } // setupUi

    void retranslateUi(QMainWindow *LOMView)
    {
        LOMView->setWindowTitle(QApplication::translate("LOMView", "Luminosity Online Monitor", 0));
        label->setText(QApplication::translate("LOMView", "Thresholds", 0));
        thresholdFELabel->setText(QApplication::translate("LOMView", "Amplitude (FWD)", 0));
        thresholdBELabel->setText(QApplication::translate("LOMView", "Amplitude (BWD)", 0));
        coincidenceDurationLabel->setText(QApplication::translate("LOMView", "Coincidence duration ", 0));
        backgroundThresholdLabel->setText(QApplication::translate("LOMView", "Background ", 0));
        label_4->setText(QString());
        pushButton->setText(QApplication::translate("LOMView", "Set", 0));
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
        label_8->setText(QApplication::translate("LOMView", "Hit sector:", 0));
        label_9->setText(QApplication::translate("LOMView", "Hit sector:", 0));
        label_6->setText(QApplication::translate("LOMView", "FWD", 0));
        label_7->setText(QApplication::translate("LOMView", "BWD", 0));
    } // retranslateUi

};

namespace Ui {
    class LOMView: public Ui_LOMView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOMVIEW_H
