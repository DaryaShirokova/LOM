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

QT_BEGIN_NAMESPACE

class Ui_LOMView
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *widget;
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
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QFormLayout *formLayout_3;
    QLabel *thresholdFELabel_2;
    QSpinBox *spinBoxAmplFWD_2;
    QLabel *thresholdBELabel_2;
    QSpinBox *spinBoxAmplBWD_2;
    QLabel *label_5;
    QPushButton *pushButton_4;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QVBoxLayout *verticalLayout_2;
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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LOMView)
    {
        if (LOMView->objectName().isEmpty())
            LOMView->setObjectName(QStringLiteral("LOMView"));
        LOMView->setMinimumSize(QSize(800, 600));
        LOMView->setAutoFillBackground(false);
        LOMView->setLocale(QLocale(QLocale::Estonian, QLocale::Estonia));
        centralWidget = new QWidget(LOMView);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
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
        thresholdFELabel = new QLabel(widget);
        thresholdFELabel->setObjectName(QStringLiteral("thresholdFELabel"));
        QFont font1;
        font1.setPointSize(12);
        thresholdFELabel->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, thresholdFELabel);

        spinBoxAmplFWD = new QSpinBox(widget);
        spinBoxAmplFWD->setObjectName(QStringLiteral("spinBoxAmplFWD"));
        spinBoxAmplFWD->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxAmplFWD->setMaximum(1000);
        spinBoxAmplFWD->setValue(100);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxAmplFWD);

        thresholdBELabel = new QLabel(widget);
        thresholdBELabel->setObjectName(QStringLiteral("thresholdBELabel"));
        thresholdBELabel->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, thresholdBELabel);

        spinBoxAmplBWD = new QSpinBox(widget);
        spinBoxAmplBWD->setObjectName(QStringLiteral("spinBoxAmplBWD"));
        spinBoxAmplBWD->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxAmplBWD->setMaximum(1000);
        spinBoxAmplBWD->setValue(100);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxAmplBWD);

        coincidenceDurationLabel = new QLabel(widget);
        coincidenceDurationLabel->setObjectName(QStringLiteral("coincidenceDurationLabel"));
        coincidenceDurationLabel->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, coincidenceDurationLabel);

        spinBoxCoinDur = new QSpinBox(widget);
        spinBoxCoinDur->setObjectName(QStringLiteral("spinBoxCoinDur"));
        spinBoxCoinDur->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxCoinDur);

        backgroundThresholdLabel = new QLabel(widget);
        backgroundThresholdLabel->setObjectName(QStringLiteral("backgroundThresholdLabel"));
        backgroundThresholdLabel->setFont(font1);

        formLayout->setWidget(3, QFormLayout::LabelRole, backgroundThresholdLabel);

        spinBoxBkg = new QSpinBox(widget);
        spinBoxBkg->setObjectName(QStringLiteral("spinBoxBkg"));
        spinBoxBkg->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(3, QFormLayout::FieldRole, spinBoxBkg);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(4, QFormLayout::FieldRole, pushButton);


        verticalLayout->addLayout(formLayout);

        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QStringLiteral("widget1"));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout_3->addWidget(label_3);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        thresholdFELabel_2 = new QLabel(widget1);
        thresholdFELabel_2->setObjectName(QStringLiteral("thresholdFELabel_2"));
        thresholdFELabel_2->setFont(font1);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, thresholdFELabel_2);

        spinBoxAmplFWD_2 = new QSpinBox(widget1);
        spinBoxAmplFWD_2->setObjectName(QStringLiteral("spinBoxAmplFWD_2"));
        spinBoxAmplFWD_2->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxAmplFWD_2->setMaximum(1000);
        spinBoxAmplFWD_2->setValue(100);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, spinBoxAmplFWD_2);

        thresholdBELabel_2 = new QLabel(widget1);
        thresholdBELabel_2->setObjectName(QStringLiteral("thresholdBELabel_2"));
        thresholdBELabel_2->setFont(font1);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, thresholdBELabel_2);

        spinBoxAmplBWD_2 = new QSpinBox(widget1);
        spinBoxAmplBWD_2->setObjectName(QStringLiteral("spinBoxAmplBWD_2"));
        spinBoxAmplBWD_2->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        spinBoxAmplBWD_2->setMaximum(1000);
        spinBoxAmplBWD_2->setValue(100);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, spinBoxAmplBWD_2);

        label_5 = new QLabel(widget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_5);

        pushButton_4 = new QPushButton(widget1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, pushButton_4);


        verticalLayout_3->addLayout(formLayout_3);

        splitter->addWidget(widget1);
        widget2 = new QWidget(splitter);
        widget2->setObjectName(QStringLiteral("widget2"));
        horizontalLayout_2 = new QHBoxLayout(widget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(widget2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        splitter->addWidget(widget2);

        horizontalLayout->addWidget(splitter);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        dLabel = new QLabel(centralWidget);
        dLabel->setObjectName(QStringLiteral("dLabel"));
        dLabel->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, dLabel);

        dLineEdit = new QLineEdit(centralWidget);
        dLineEdit->setObjectName(QStringLiteral("dLineEdit"));
        dLineEdit->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, dLineEdit);

        deadTimeLabel = new QLabel(centralWidget);
        deadTimeLabel->setObjectName(QStringLiteral("deadTimeLabel"));
        deadTimeLabel->setFont(font1);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, deadTimeLabel);

        deadTimeLineEdit = new QLineEdit(centralWidget);
        deadTimeLineEdit->setObjectName(QStringLiteral("deadTimeLineEdit"));
        deadTimeLineEdit->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, deadTimeLineEdit);

        vetoTimeLabel = new QLabel(centralWidget);
        vetoTimeLabel->setObjectName(QStringLiteral("vetoTimeLabel"));
        vetoTimeLabel->setFont(font1);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, vetoTimeLabel);

        vetoTimeLineEdit = new QLineEdit(centralWidget);
        vetoTimeLineEdit->setObjectName(QStringLiteral("vetoTimeLineEdit"));
        vetoTimeLineEdit->setReadOnly(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, vetoTimeLineEdit);

        bhabhaEventsLabel = new QLabel(centralWidget);
        bhabhaEventsLabel->setObjectName(QStringLiteral("bhabhaEventsLabel"));
        bhabhaEventsLabel->setFont(font1);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, bhabhaEventsLabel);

        bhabhaEventsLineEdit = new QLineEdit(centralWidget);
        bhabhaEventsLineEdit->setObjectName(QStringLiteral("bhabhaEventsLineEdit"));
        bhabhaEventsLineEdit->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, bhabhaEventsLineEdit);

        backgroundEventsLabel = new QLabel(centralWidget);
        backgroundEventsLabel->setObjectName(QStringLiteral("backgroundEventsLabel"));
        backgroundEventsLabel->setFont(font1);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, backgroundEventsLabel);

        backgroundEventsLineEdit = new QLineEdit(centralWidget);
        backgroundEventsLineEdit->setObjectName(QStringLiteral("backgroundEventsLineEdit"));
        backgroundEventsLineEdit->setReadOnly(true);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, backgroundEventsLineEdit);


        verticalLayout_2->addLayout(formLayout_2);


        horizontalLayout->addLayout(verticalLayout_2);

        LOMView->setCentralWidget(centralWidget);
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
        thresholdFELabel_2->setText(QApplication::translate("LOMView", "Update frequence (Hz)", 0));
        thresholdBELabel_2->setText(QApplication::translate("LOMView", "Redraw frequence (Hz)", 0));
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
    } // retranslateUi

};

namespace Ui {
    class LOMView: public Ui_LOMView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOMVIEW_H
