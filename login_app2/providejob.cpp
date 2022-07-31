
#include "providejob.h"
#include "ui_providejob.h"
#include "employer.h"
#include <QPixmap>
#include "global.h"
#include "connect.cpp"
#include<QMessageBox>

providejob::providejob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::providejob)
{
    ui->setupUi(this);
    QPixmap picpj(":/resources/image/pjj.png");
    ui->label_pjpf->setPixmap(picpj.scaled(70,70,Qt::KeepAspectRatio));

}

providejob::~providejob()
{
    delete ui;
}

void providejob::on_pushButton_post_clicked()
{
    QString jobname = ui->lineEdit_jn->text();
    QString address = ui->lineEdit_ja->text();
    QString qualification = ui->lineEdit_qf->text();
    QString salary = ui->lineEdit_salary->text();
    QString type = ui->lineEdit_jobt->text();

    class connect conn;
    if(jobname!="" && address != ""&& qualification !=""&& salary != "" && type != ""){
//        if(!conn.connopen())
//        {
//            qDebug()<<"Failed to  Open Database";
//            return;

//        }
        conn.connopen();

        QSqlQuery post;
                post.prepare("insert into joblist (JobName, JobAddres, Qualification, Salary, JobType, Employer) values ('"+jobname+"','"+address+"','"+qualification+"','"+salary+"','"+type+"','"+tempid+"')");
        if(post.exec()){
        QMessageBox::critical(this,tr("Data Added Successfully"),tr("Data added Successfully"));
            qDebug()<<("Posted");
        conn.connclose();
        }else{
            QMessageBox::critical(this,tr("error::"),post.lastError().text());
            qDebug()<<("Not posted");
        };
    }


}


void providejob::on_pushButton_cancelpjob_clicked()
{
    hide();
    employer *emp = new employer(this);
    emp->show();
}

