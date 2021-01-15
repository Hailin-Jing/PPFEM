#ifndef PARTCHOOSEDIALOG_H
#define PARTCHOOSEDIALOG_H

#include <QDialog>

namespace Ui {
class PartChooseDialog;
}

class PartChooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PartChooseDialog(QWidget *parent = nullptr,QStringList *partItem = nullptr,int NI = 0);
    ~PartChooseDialog();
    int getPartIndex();

private:
    Ui::PartChooseDialog *ui;
};

#endif // PARTCHOOSEDIALOG_H
