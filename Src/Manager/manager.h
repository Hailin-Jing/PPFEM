#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include <model.h>
#include "Src/mainwindow.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>

class MainWindow;

namespace Ui {
class Manager;
}

class Manager : public QWidget
{
    Q_OBJECT

private:
    Model *model;
    MainWindow *mainwindow;
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    QString title;
    QStringList headerText;
    std::vector<std::vector<QString>> data;

public:
    explicit Manager(QWidget *parent = nullptr,Model *model = nullptr,
                     QStandardItemModel *theModel = nullptr,
                     QItemSelectionModel *theSelection = nullptr,
                     QString title = "管理器", QStringList headerText = QStringList(),
                     std::vector<std::vector<QString>> data = std::vector<std::vector<QString>>(),
                     MainWindow *mainWindow = nullptr);
    ~Manager();

    //刷新
    void Refresh(int row, int DataRow = -1, int partIndex = -1);
        void RefreshPart(int row);
        void RefreshMaterial(int row);
        void RefreshBoundaryCondition(int row, int DataRow = -1, int partIndex = -1);
        void RefreshLoad(int row, int DataRow = -1, int partIndex = -1);

    //新建
    void NewMaterial();
        void NewPart();
        void NewBoundaryCondition();
        void NewLoad();

    //保存
    void SaveMaterial();
        void SavePart();
        void SaveBoundaryCondition();
        void SaveLoad();

    //复制
    void CopyMaterial();
        void CopyPart();
        void CopyBoundaryCondition();
        void CopyLoad();

    //删除
    void DeleteMaterial();
        void DeletePart();
        void DeleteBoundaryCondition();
        void DeleteLoad();

private:
    Ui::Manager *ui;

private slots:
    void on_newButton_clicked();
    void on_SaveButton_clicked();
    void on_copyButton_clicked();
    void on_deleteButton_clicked();
};

#endif // MANAGER_H
