#include "datavisualization.h"
#include "ui_datavisualization.h"

DataVisualization::DataVisualization
(QStringList headerText,MatrixXd data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataVisualization)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel();
    theSelection = new QItemSelectionModel(theModel);

    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    this->theModel->setColumnCount(int(data.cols()));
    this->theModel->setRowCount(int(data.rows()));

    //Header
    for (int i = 0; i < data.cols(); i++)
    {
        QStandardItem *headerItem = new QStandardItem(headerText.at(i));
        QFont font = headerItem->font();
        font.setFamily("Times New Roman");
        font.setPointSize(12);
        headerItem->setFont(font);
        this->theModel->setHorizontalHeaderItem(i,headerItem);
    }
    //Data
    for (int i = 0; i < data.rows(); i++)
    {
        for (int j = 0; j < data.cols(); j++)
        {
            QStandardItem *aItem =
                    new QStandardItem(QString::number(data(i,j)));
            aItem->setTextAlignment(Qt::AlignCenter);
            aItem->setEditable(false);
            QFont font = aItem->font();
            font.setFamily("Times New Roman");
            font.setPointSize(12);
            aItem->setFont(font);
            this->theModel->setItem(i,j,aItem);
        }
    }
}

DataVisualization::~DataVisualization()
{
    delete ui;
}

