#ifndef BOUNDARYCONDITIONDIALOG_H
#define BOUNDARYCONDITIONDIALOG_H

#include <QDialog>

namespace Ui {
class BoundaryConditionDialog;
}

class BoundaryConditionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BoundaryConditionDialog(QWidget *parent = nullptr);
    ~BoundaryConditionDialog();

    bool getConstraintX();
    bool getConstraintY();
    double getMinRange();
    double getMaxRange();

private:
    Ui::BoundaryConditionDialog *ui;
};

#endif // BOUNDARYCONDITIONDIALOG_H
