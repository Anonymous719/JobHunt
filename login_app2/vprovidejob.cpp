#include "vprovidejob.h"
#include "ui_vprovidejob.h"
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

vprovidejob::vprovidejob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vprovidejob)
{
    ui->setupUi(this);
    MainWindow conn;
          conn.connopen();
        static QSqlQueryModel modal;
           modal.setQuery("SELECT * FROM applicants WHERE Employer='"+tempid+"'");
            ui->tableView_application->setModel(&modal);
            conn.connclose();
}

vprovidejob::~vprovidejob()
{
    delete ui;
}





void vprovidejob::on_pushButton_backvp_clicked()
{
    hide();
    employer *emp = new employer(this);
    emp->show();
}

