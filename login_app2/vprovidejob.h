#ifndef VPROVIDEJOB_H
#define VPROVIDEJOB_H

#include <QDialog>

namespace Ui {
class vprovidejob;
}

class vprovidejob : public QDialog
{
    Q_OBJECT

public:
    explicit vprovidejob(QWidget *parent = nullptr);
    ~vprovidejob();

private slots:


    void on_pushButton_backvp_clicked();

private:
    Ui::vprovidejob *ui;
};

#endif // VPROVIDEJOB_H
