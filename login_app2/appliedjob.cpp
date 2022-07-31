#include "appliedjob.h"
#include "ui_appliedjob.h"
#include "dialog.h"

appliedjob::appliedjob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::appliedjob)
{
    ui->setupUi(this);
}

appliedjob::~appliedjob()
{
    delete ui;
}

void appliedjob::on_pushButton_backapjob_clicked()
{
    hide();
    Dialog *secdialog =new Dialog(this);
    secdialog->show();
}

