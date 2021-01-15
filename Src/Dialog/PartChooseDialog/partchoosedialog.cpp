#include "partchoosedialog.h"
#include "ui_partchoosedialog.h"

PartChooseDialog::PartChooseDialog(QWidget *parent,QStringList *partItem,int NI) :
    QDialog(parent),
    ui(new Ui::PartChooseDialog)
{
    ui->setupUi(this);
    for (int i = 0; i < NI; i++)
        ui->partItem->addItem(partItem->at(i));
}

PartChooseDialog::~PartChooseDialog()
{
    delete ui;
}

int PartChooseDialog::getPartIndex()
{
    return ui->partItem->currentIndex();
}
