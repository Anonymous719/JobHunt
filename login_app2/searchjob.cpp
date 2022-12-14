#include "searchjob.h"
#include "ui_searchjob.h"
#include <QPixmap>
#include "dialog.h"
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSql>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QDebug>
#include <QTextEdit>
#include<QMessageBox>
#include "global.h"
#include<QSqlError>
#include<mainwindow.h>

searchjob::searchjob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchjob)
{
    ui->setupUi(this);
    QPixmap sjob(":/resources/image/jobsearch.png");
    ui->label_scj->setPixmap(sjob.scaled(50,50,Qt::KeepAspectRatio));

    MainWindow conn;

    if (conn.connopen())
    {
    ui->label_su->setText("Successful ");
     conn.connclose();}
    else{
        ui->label_su->setText("Failed");
        conn.connclose();
    }

    ui->lineEdit_JobName->setPlaceholderText("Job Name");
    ui->lineEdit_JobAddress->setPlaceholderText("Job Address");
    ui->lineEdit_Qualification->setPlaceholderText("Qualification");
    ui->lineEdit_Salary->setPlaceholderText("Salary");
    ui->lineEdit_JobType->setPlaceholderText("Job Type");
    ui->lineEdit_name->setPlaceholderText("Applicant Name");
    ui->lineEdit_Employer->setPlaceholderText("Employer Name");
    ui->lineEdit_JobId->setPlaceholderText("Job Id");

}

searchjob::~searchjob()
{
    delete ui;
}

void searchjob::on_pushButton_back_clicked()
{
    hide();
       Dialog *secdialog =new Dialog(this);
       secdialog->show();

}


void searchjob::on_pushButton_sjob_clicked()
{
    MainWindow conn;
    conn.connopen();
        static QSqlQueryModel modal;
        QString keyword,location,low,up;
        keyword = ui->lineEdit_keyword->text();
        location=ui->comboBox_location->currentText();
        low=ui->lineEdit_lower->text();
        up=ui->lineEdit_upper->text();

        location=location.toUpper();
        keyword=keyword.toUpper();

        if(keyword.isEmpty() && location=="ALL"){
            modal.setQuery("SELECT JobName,JobAddres,Qualification,Salary,JobType,JobId FROM joblist WHERE Salary BETWEEN '"+low+"' AND '"+up+"'");

        }
        if(keyword.isEmpty() && location !="ALL"){
             modal.setQuery("SELECT JobName,JobAddres,Qualification,Salary,JobType,JobId FROM joblist WHERE JobAddres='"+location+"' AND Salary BETWEEN '"+low+"' AND '"+up+"'");

        }
        if(!keyword.isEmpty() && location=="ALL"){
            modal.setQuery("SELECT JobName,JobAddres,Qualification,Salary,JobType,JobId FROM joblist WHERE JobName='"+keyword+"' AND Salary BETWEEN '"+low+"' AND '"+up+"'");
         }
        if(!keyword.isEmpty() && location!="ALL"){
           modal.setQuery("SELECT JobName,JobAddres,Qualification,Salary,JobType,JobId FROM joblist WHERE JobName = '"+keyword+"' AND JobAddres='"+location+"' AND Salary BETWEEN '"+low+"' AND '"+up+"'");
        }
        ui->tableView_search->setModel(&modal);
        ui->label_display->setText("Fill The Form Provided To Apply For A Job ");
        conn.connclose();
}




void searchjob::on_tableView_search_activated(const QModelIndex &index)
{
    MainWindow conn;
    conn.connopen();
    QString val=ui->tableView_search->model()->data(index).toString();
    QSqlQuery qry4;
    qry4.prepare("SELECT * FROM joblist where JobName = '"+val+"' OR JobAddres = '"+val+"' OR Qualification = '"+val+"' OR Salary = '"+val+"' OR JobType = '"+val+"'");
    if(qry4.exec()){
        while(qry4.next()){
            ui->lineEdit_JobName->setText(qry4.value(0).toString());
            ui->lineEdit_JobAddress->setText(qry4.value(1).toString());
            ui->lineEdit_Qualification->setText(qry4.value(2).toString());
            ui->lineEdit_Salary->setText(qry4.value(3).toString());
            ui->lineEdit_JobType->setText(qry4.value(4).toString());
            ui->lineEdit_JobId->setText(qry4.value(5).toString());
            ui->lineEdit_Employer->setText(qry4.value(7).toString());
}
           ui->lineEdit_name->setText(tempid);
}
     conn.connclose();
}


void searchjob::on_pushButton_apply_clicked()
{
    MainWindow conn;
    conn.connopen();

   // mydb.open();
    QSqlQuery qry;
    QString jobname,username,jobaddress,jobtype,qualification,salary,jobid,employer;
    jobname = ui->lineEdit_JobName->text();
    username=ui->lineEdit_name->text();
    jobaddress=ui->lineEdit_JobAddress->text();
    qualification=ui->lineEdit_Qualification->text();
    salary=ui->lineEdit_Salary->text();
    jobtype=ui->lineEdit_JobType->text();
    jobid=ui->lineEdit_JobId->text();
    employer=ui->lineEdit_Employer->text();

  //qry.prepare("INSERT INTO applicants (JobId,JobName,JobAddress,Qualification,Salary,JobType,Applicant,Employer) VALUES ("+jobid+","+jobname+","+jobaddress+","+qualification+","+salary+","+jobtype+","+username+","+employer+")");
    qry.prepare("INSERT INTO applicants (JobId,JobName,JobAddress,Qualification,Salary,JobType,Applicant,Employer) VALUES (:jobid,:jobname,:jobaddress,:qualification,:salary,:jobtype,:username,:employer)");
    qry.bindValue(":JobId",jobid);
    qry.bindValue(":JobName",jobname);
    qry.bindValue(":JobAddress",jobaddress);
    qry.bindValue(":Qualification",qualification);
    qry.bindValue(":Salary",salary);
    qry.bindValue(":JobType",jobtype);
    qry.bindValue(":Applicant",username);

    qry.bindValue(":Employer",employer);


    if(qry.exec())
    {
    QMessageBox::critical(this,tr("Apply"),tr("Applied Successfully"));
      ui->label_test->setText("Sucess");
    conn.connclose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());

    };

/*
if(count>=1)
{
     QMessageBox::information(this,"Apply","Already Applied for this Job");

}
else
{
    connopen();
    QSqlQuery qry5;
    qry5.prepare("SELECT * FROM user_account where JobId='"+jobid+"' and applicant='"+tempid+"'");
    if(qry.exec())
    {
    QMessageBox::critical(this,tr("Apply"),tr("Applied Successfully"));
    connclose();
    }
}
}*/
}
