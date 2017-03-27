#include "QMainInfo.h"
#include "ui_QMainInfo.h"

QMainInfo::QMainInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMainInfo)
{
    ui->setupUi(this);
}

QMainInfo::~QMainInfo()
{
    delete ui;
}
