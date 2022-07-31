#ifndef VIEWAPPLICANT_H
#define VIEWAPPLICANT_H

#include <QDialog>

namespace Ui {
class viewapplicant;
}

class viewapplicant : public QDialog
{
    Q_OBJECT

public:
    explicit viewapplicant(QWidget *parent = nullptr);
    ~viewapplicant();

private:
    Ui::viewapplicant *ui;
};

#endif // VIEWAPPLICANT_H
