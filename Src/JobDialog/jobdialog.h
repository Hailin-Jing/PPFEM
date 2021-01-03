#ifndef JOBDIALOG_H
#define JOBDIALOG_H

#include <QDialog>
#include "model.h"

namespace Ui {
class JobDialog;
}

class JobDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JobDialog(QWidget *parent = nullptr,Model *model = nullptr);
    ~JobDialog();

    int getProblemType();
    int getElementType();
    double getThickness();
    int getStorageMode();
    int getSolutionofLinearEquation();
    int getPartIndex();
    int getMaterialIndex();

private:
    Ui::JobDialog *ui;
};

#endif // JOBDIALOG_H
