#include "inc/QMenuConfig.h"
#include "ui_QMenuConfig.h"

#include <QMessageBox>
#include <QFileDialog>

QMenuConfig::QMenuConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMenuConfig) {
    ui->setupUi(this);
    setWindowTitle("Configurations");
}

QMenuConfig::~QMenuConfig() {
    delete ui;
}

QString QMenuConfig::GetDataDir() {
    return ui->lineDataDir->text();
}

void QMenuConfig::SetDataDir(QString dataDir) {
    ui->lineDataDir->setText(dataDir);
}

QString QMenuConfig::GetLogDir() {
    return ui->lineLogDir->text();
}

void QMenuConfig::SetLogDir(QString logDir) {
    ui->lineLogDir->setText(logDir);
}

bool QMenuConfig::IfWriteFile() {
    return ui->chbSaveRootFile->isChecked();
}

void QMenuConfig::SetWriteFile(bool writeFile) {
    ui->chbSaveRootFile->setChecked(writeFile);
}

bool QMenuConfig::IsAdvanced() {
    return ui->chbAdvanced->isChecked();
}

void QMenuConfig::SetAdvanced(bool advanced) {
    ui->chbAdvanced->setChecked(advanced);
}

int QMenuConfig::GetRootFileSize() {
    return ui->sbRootFileSize->value();
}

void QMenuConfig::SetRootFileSize(int size) {
    ui->sbRootFileSize->setValue(size);
}

int QMenuConfig::GetHistRecordFreq() {
    return ui->sbHistRecord->value();
}

void QMenuConfig::SetHistRecordFreq(int freq) {
    ui->sbHistRecord->setValue(freq);
}

bool QMenuConfig::IfWriteHist() {
    return ui->chbSaveHist->isChecked();
}

void QMenuConfig::SetWriteHist(bool writeHist) {
    ui->chbSaveHist->setChecked(writeHist);
}

void QMenuConfig::SetHistDir(QString histDir) {
    ui->lineHistDir->setText(histDir);
}

QString QMenuConfig::GetHistDir() {
    return ui->lineHistDir->text();
}

void QMenuConfig::OnApply() {
    emit Apply(this);
}


void QMenuConfig::OnCancel() {
    this->close();
}

void QMenuConfig::OnBrowseData() {

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ".",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!dir.isNull())
        ui->lineDataDir->setText(dir);
}

void QMenuConfig::OnBrowseHist() {

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ".",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!dir.isNull())
        ui->lineHistDir->setText(dir);
}

void QMenuConfig::OnBrowseLog() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ".",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!dir.isNull())
        ui->lineLogDir->setText(dir);
}

