

#include "vprofileemp.h"
#include "ui_vprofileemp.h"
#include "employer.h"
#include "editprofileemp.h"
#include "global.h"
#include "connect.cpp"


vprofileemp::vprofileemp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vprofileemp)
{
    ui->setupUi(this);

    class connect conn;
    conn.connopen();
    QSqlQuery view("select username,address,phone,email from user_account where username='"+tempid+"'");
    qDebug()<<(tempid);
    if(view.exec()){
        view.first();
        ui->label_vpe1->setText(view.value(0).toString());
        ui->label_vpe2->setText(view.value(3).toString());
        ui->label_vpe3->setText(view.value(2).toString());
        ui->label_vpe4->setText(view.value(1).toString());
        //ui->label_edu->setText(view.value(3).toString());
    }
    conn.connclose();
}

vprofileemp::~vprofileemp()
{
    delete ui;
}

void vprofileemp::on_pushButton_backvj_clicked()
{
    hide();
    employer *emp = new employer(this);
    emp->show();
}


void vprofileemp::on_pushButton_editvj_clicked()
{
    hide();
    editprofileemp *epfemp =new editprofileemp(this);
    epfemp->show();
}

