#ifndef DATAVISUALIZATION_H
#define DATAVISUALIZATION_H

#include "Eigen3/Eigen/Dense"
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QWidget>

using namespace Eigen;

namespace Ui {
class DataVisualization;
}

class DataVisualization : public QWidget
{
    Q_OBJECT
private:
    QStandardItemModel *theModel;  //数据模型
    QItemSelectionModel *theSelection;  //选择模型

public:
    explicit DataVisualization(QStringList headerText,MatrixXd data,QWidget *parent = nullptr);
    ~DataVisualization();

private:
    Ui::DataVisualization *ui;
};

#endif // DATAVISUALIZATION_H
