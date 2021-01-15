#ifndef MATERIALINPUTDIALOG_H
#define MATERIALINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class MaterialInputDialog;
}

class MaterialInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaterialInputDialog(QWidget *parent = nullptr,QString materialName = "材料");
    ~MaterialInputDialog();

    double Modulus();
    double PossionsRatio();
    double Density();
    QString MaterialName();

private:
    Ui::MaterialInputDialog *ui;
};

#endif // MATERIALINPUTDIALOG_H
