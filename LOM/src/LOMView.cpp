#include "../inc/LOMView.h"
#include "ui_LOMView.h"

LOMView::LOMView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LOMView)
{
    ui->setupUi(this);
    //ui->fwdEndcapWidget->se
    //centralWidget()->layout()->setAlignment(Qt::AlignTop);
    //layout()->setAlignment(widget, layout)
}

LOMView::~LOMView()
{
    delete ui;
}
