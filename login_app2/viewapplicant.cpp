#include "viewapplicant.h"
#include "ui_viewapplicant.h"

viewapplicant::viewapplicant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewapplicant)
{
    ui->setupUi(this);
}

viewapplicant::~viewapplicant()
{
    delete ui;
}
