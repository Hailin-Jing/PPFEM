#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>

namespace Ui {
class LoadDialog;
}

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadDialog(QWidget *parent = nullptr);
    ~LoadDialog();

    int getLoadType();
    double getBPX();
    double getBPY();
    double getEPX();
    double getEPY();
    double getMinRange();
    double getMaxRange();

private slots:
    void on_LoadType_currentIndexChanged(const QString &arg1);

private:
    Ui::LoadDialog *ui;
};

#endif // LOADDIALOG_H
