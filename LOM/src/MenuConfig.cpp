#include "inc/MenuConfig.h"
#include "ui_MenuConfig.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

MenuConfig::MenuConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuConfig)
{
    ui->setupUi(this);
    setWindowTitle("Configurations");
}

MenuConfig::~MenuConfig()
{
    delete ui;
}

QString MenuConfig::GetDataDir()
{
    return ui->lineDataDir->text();
}
void MenuConfig::SetDataDir(QString dataDir)
{
    ui->lineDataDir->setText(dataDir);
}

QString MenuConfig::GetLogDir()
{
    return ui->lineLogDir->text();
}

void MenuConfig::SetLogDir(QString logDir)
{
    ui->lineLogDir->setText(logDir);
}

bool MenuConfig::IfWriteFile()
{
    return ui->chbSaveRootFile->isChecked();
}

void MenuConfig::SetWriteFile(bool writeFile)
{
    ui->chbSaveRootFile->setChecked(writeFile);
}

bool MenuConfig::IsAdvanced()
{
    return ui->chbAdvanced->isChecked();
}

void MenuConfig::SetAdvanced(bool advanced)
{
    ui->chbAdvanced->setChecked(advanced);
}

int MenuConfig::GetRootFileSize()
{
    return ui->sbRootFileSize->value();
}

void MenuConfig::SetRootFileSize(int size)
{
    ui->sbRootFileSize->setValue(size);
}

void MenuConfig::OnApply()
{
    emit Apply(this);
}

void MenuConfig::OnSave()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "config/appset.conf",
                               tr("Config (*.conf)"));
    if(!filename.isNull())
        emit Save(this, filename);
}

void MenuConfig::OnCancel()
{
    this->close();
}

void MenuConfig::OnBrowseData()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ".",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!dir.isNull())
        ui->lineDataDir->setText(dir);
}

void MenuConfig::OnBrowseLog()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ".",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!dir.isNull())
        ui->lineLogDir->setText(dir);
}

