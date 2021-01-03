#ifndef NEWLOADDIALOG_H
#define NEWLOADDIALOG_H

#include <QDialog>

namespace Ui {
class NewLoadDialog;
}

class NewLoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewLoadDialog(QWidget *parent = nullptr,QStringList *partItem = nullptr,int NI = 0);
    ~NewLoadDialog();

    int getLoadType();
    double getGX();
    double getGY();
    int getPartIndex();

private slots:
    void on_LoadType_currentIndexChanged(const QString &arg1);

private:
    Ui::NewLoadDialog *ui;
};

#endif // NEWLOADDIALOG_H
