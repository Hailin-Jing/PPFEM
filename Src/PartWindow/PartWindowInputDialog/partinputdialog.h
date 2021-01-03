#ifndef PARTINPUTDIALOG_H
#define PARTINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class partInputDialog;
}

class partInputDialog : public QDialog
{
    Q_OBJECT
private:
    int partNumber = 0;

public:
    explicit partInputDialog(QWidget *parent = nullptr,QString partName = "部件");
    ~partInputDialog();

    QString PartName();
    QString getModelFileName();

    Ui::partInputDialog *getUI();

private slots:
    void on_pushButtonModel_clicked();

private:
    Ui::partInputDialog *ui;
};

#endif // PARTINPUTDISLOG_H
