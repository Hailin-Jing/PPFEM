#ifndef MODELDATA_H
#define MODELDATA_H

#include <QMainWindow>

namespace Ui {
class ModelData;
}

class ModelData : public QMainWindow
{
    Q_OBJECT

private:
    int partIndex;

public:
    explicit ModelData(QWidget *parent = nullptr,int partIndex = -1);
    ~ModelData();

private slots:
    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

    void on_actionSave_triggered();

private:
    Ui::ModelData *ui;
};

#endif // ModelData_H
