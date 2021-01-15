#include "manager.h"
#include "ui_manager.h"
//#include "mainwindow.h"
#include <iostream>

#include <QStandardItem>

Manager::Manager(QWidget *parent,Model *model,QStandardItemModel *theModel,
                 QItemSelectionModel *theSelection,QString title,
                 QStringList headerText,std::vector<std::vector<QString>> data,
                 MainWindow *mainWindow) :
    QWidget(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
    this->mainwindow = mainWindow;
    this->model = model;
    this->theModel = theModel;
    this->theSelection = theSelection;
    this->title = title;
    this->headerText = headerText;
    this->data = data;

    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    theModel->setRowCount(int(data.size()));

    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));

}

Manager::~Manager()
{
    delete ui;
}

void Manager::on_newButton_clicked()
{
    QString windowtitle = windowTitle();

    if (windowtitle == QString("部件管理器"))
        NewPart();
    else if (windowtitle == QString("材料属性管理器"))
        NewMaterial();
    else if (windowtitle == QString("边界条件管理器"))
        NewBoundaryCondition();
    else if (windowtitle == QString("荷载管理器"))
        NewLoad();
}

void Manager::on_SaveButton_clicked()
{
    QString windowtitle = windowTitle();

    if (windowtitle == QString("部件管理器"))
        SavePart();
    else if (windowtitle == QString("材料属性管理器"))
        SaveMaterial();
    else if (windowtitle == QString("边界条件管理器"))
        SaveBoundaryCondition();
    else if (windowtitle == QString("荷载管理器"))
        SaveLoad();
}

void Manager::on_copyButton_clicked()
{
    QString windowtitle = windowTitle();

    if (windowtitle == QString("部件管理器"))
        CopyPart();
    else if (windowtitle == QString("材料属性管理器"))
        CopyMaterial();
    else if (windowtitle == QString("边界条件管理器"))
        CopyBoundaryCondition();
    else if (windowtitle == QString("荷载管理器"))
        CopyLoad();
}

void Manager::on_deleteButton_clicked()
{
    QString windowtitle = windowTitle();

    if (windowtitle == QString("部件管理器"))
        DeletePart();
    else if (windowtitle == QString("材料属性管理器"))
        DeleteMaterial();
    else if (windowtitle == QString("边界条件管理器"))
        DeleteBoundaryCondition();
    else if (windowtitle == QString("荷载管理器"))
        DeleteLoad();
}

void Manager::Refresh(int row, int DataRow, int partIndex)
{
    QString windowtitle = windowTitle();
    if (windowtitle == QString("部件管理器"))
        RefreshPart(row);
    else if (windowtitle == QString("材料属性管理器"))
        RefreshMaterial(row);
    else if (windowtitle == QString("边界条件管理器"))
        RefreshBoundaryCondition(row,DataRow,partIndex);
    else if (windowtitle == QString("荷载管理器"))
        RefreshLoad(row,DataRow,partIndex);
}

void Manager::RefreshPart(int row)
{
    QStandardItem *aItem;
    QFont font;

    //部件名
    aItem = new QStandardItem(model->getPart(row)->PN);
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,0,aItem);

    //图元数
    aItem = new QStandardItem(QString::number(model->getPart(row)->DXF->getPrimitives().size()));
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,1,aItem);

    //孔洞数
    aItem = new QStandardItem(QString::number(model->getPart(row)->NH));
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,2,aItem);

    //结点数
    aItem = new QStandardItem(QString::number(model->getPart(row)->NN));
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,3,aItem);

    //单元数
    aItem = new QStandardItem(QString::number(model->getPart(row)->NE));
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,4,aItem);

    //边数
    aItem = new QStandardItem(QString::number(model->getPart(row)->NS));
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,5,aItem);
}

void Manager::RefreshMaterial(int row)
{

    QStandardItem *aItem;
    QFont font;
    //材料名
    aItem = new QStandardItem(model->getMaterial(row)->MN);
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,0,aItem);

    //弹性模量
    aItem = new QStandardItem(QString::number
                (model->getMaterial(row)->E));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,1,aItem);

    //泊松比
    aItem = new QStandardItem(QString::number
                (model->getMaterial(row)->ANU));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,2,aItem);

    //密度
    aItem = new QStandardItem(QString::number
                (model->getMaterial(row)->Density));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,3,aItem);
}

void Manager::RefreshBoundaryCondition(int row, int DataRow, int partIndex)
{
    QStandardItem *aItem;
    QFont font;
    //所属部件
    aItem = new QStandardItem(model->getPart(partIndex)->PN);
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,0,aItem);

    //边界号
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->BC[unsigned(DataRow)].BCIndex));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,1,aItem);

    //图元号
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->BC[unsigned(DataRow)].PRIndex));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,2,aItem);

    //作用范围-起点
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->BC[unsigned(DataRow)].MinRange));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,3,aItem);

    //作用范围-终点
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->BC[unsigned(DataRow)].MaxRange));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,4,aItem);

    //约束-X
    aItem = new QStandardItem(QString("约束"));
    if (model->getPart(partIndex)->BC[unsigned(DataRow)].DegreeConstraintX)
        aItem = new QStandardItem(QString::number(1));
    else
        aItem = new QStandardItem(QString::number(0));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,5,aItem);

    //约束-Y
    if (model->getPart(partIndex)->BC[unsigned(DataRow)].DegreeConstraintY)
        aItem = new QStandardItem(QString::number(1));
    else
        aItem = new QStandardItem(QString::number(0));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,6,aItem);
}

void Manager::RefreshLoad(int row, int DataRow, int partIndex)
{

    QStandardItem *aItem;
    QFont font;

    //所属部件
    aItem = new QStandardItem(model->getPart(partIndex)->PN);
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,0,aItem);

    //荷载号
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->F[unsigned(DataRow)].LoadIndex));
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,1,aItem);

    //荷载类型
    QString Loadtype;
    if (model->getPart(partIndex)->F[unsigned(DataRow)].LoadType == 1)
        Loadtype = QString("自重荷载");
    else
        Loadtype = QString("边界分布荷载");
    aItem = new QStandardItem(Loadtype);
    aItem->setTextAlignment(Qt::AlignCenter);
    aItem->setEditable(false);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,2,aItem);

    if (model->getPart(partIndex)->F[unsigned(DataRow)].LoadType == 1)
    {
        //G-X/q-x1
        aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                          F[unsigned(DataRow)].BPX));
        aItem->setTextAlignment(Qt::AlignCenter);
        font = aItem->font();
        font.setFamily("Times New Roman");
        font.setPointSize(12);
        aItem->setFont(font);
        theModel->setItem(row,6,aItem);

        //G-Y/q-y1
        aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                          F[unsigned(DataRow)].BPY));
        aItem->setTextAlignment(Qt::AlignCenter);
        font = aItem->font();
        font.setFamily("Times New Roman");
        font.setPointSize(12);
        aItem->setFont(font);
        theModel->setItem(row,7,aItem);
        return;
    }

    //图元号
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                      F[unsigned(DataRow)].PRIndex));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,3,aItem);

    //作用范围-起点
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                      F[unsigned(DataRow)].MinRange));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,4,aItem);

    //作用范围-终点
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                      F[unsigned(DataRow)].MaxRange));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,5,aItem);

    //G-X/q-x1
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                      F[unsigned(DataRow)].BPX));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,6,aItem);

    //G-Y/q-y1
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                      F[unsigned(DataRow)].BPY));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,7,aItem);

    //q-x2
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                      F[unsigned(DataRow)].EPX));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,8,aItem);

    //q-y2
    aItem = new QStandardItem(QString::number(model->getPart(partIndex)->
                      F[unsigned(DataRow)].EPY));
    aItem->setTextAlignment(Qt::AlignCenter);
    font = aItem->font();
    font.setFamily("Times New Roman");
    font.setPointSize(12);
    aItem->setFont(font);
    theModel->setItem(row,9,aItem);
}

void Manager::NewMaterial()
{
    mainwindow->NewMaterial();
    for (int i = 0; i < model->getMaterialNumber(); i++)
        RefreshMaterial(i);
}

void Manager::NewPart()
{
    mainwindow->NewPart();
    this->close();
}

void Manager::NewBoundaryCondition()
{
    mainwindow->NewBoundaryCondition();
    this->close();
}

void Manager::NewLoad()
{
    mainwindow->NewLoad();
    this->close();
}

void Manager::SaveMaterial()
{
    for (int i = 0; i < model->getMaterialNumber(); i++)
    {
        Material *material = model->getMaterial(i);
        material->MN = theModel->item(i,0)->text();
        if (theModel->item(i,1)->text().toDouble() > 0)
            material->E = theModel->item(i,1)->text().toDouble();
        if (theModel->item(i,2)->text().toDouble() >= 0 &&
                theModel->item(i,2)->text().toDouble() <= 0.5)
            material->ANU = theModel->item(i,2)->text().toDouble();
        if (theModel->item(i,3)->text().toDouble() > 0)
            material->Density = theModel->item(i,3)->text().toDouble();
    }
    for (int i = 0; i < model->getMaterialNumber(); i++)
        RefreshMaterial(i);
}

void Manager::SavePart()
{
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        Part *part = model->getPart(i);
        part->PN = theModel->item(i,0)->text();
    }
    for (int i = 0; i < model->getPartNumber(); i++)
        RefreshPart(i);
}

void Manager::SaveBoundaryCondition()
{
    for (int i = 0; i < theModel->rowCount(); i++)
    {
        int partIndex = -1;
        for (int j = 0; j < model->getPartNumber(); j++)
        {
            Part *part = model->getPart(j);
            if (part->PN == theModel->item(i,0)->text())
            {
                partIndex = j;
                break;
            }
        }
        if (partIndex == -1)
            continue;
        std::vector<BC> BoundaryCondition = model->getPart(partIndex)->BC;

        //起点
        if (theModel->item(i,3)->text().toDouble() >= 0 &&
                theModel->item(i,3)->text().toDouble() <= 1)
            BoundaryCondition[unsigned(i)].MinRange = theModel->item(i,3)->text().toDouble();
        //终点
        if (theModel->item(i,4)->text().toDouble() >= 0 &&
                theModel->item(i,4)->text().toDouble() <= 1)
            BoundaryCondition[unsigned(i)].MaxRange = theModel->item(i,4)->text().toDouble();
        //约束-X
        if (qAbs(theModel->item(i,5)->text().toDouble()) > 0.001)
            BoundaryCondition[unsigned(i)].DegreeConstraintX = true;
        else
            BoundaryCondition[unsigned(i)].DegreeConstraintX = false;
        //约束-Y
        if (qAbs(theModel->item(i,6)->text().toDouble()) > 0.001)
            BoundaryCondition[unsigned(i)].DegreeConstraintY = true;
        else
            BoundaryCondition[unsigned(i)].DegreeConstraintY = false;

        model->getPart(partIndex)->BC = BoundaryCondition;
    }
    int row = 0;
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        Part *part = model->getPart(i);
        for (int j = 0; part->BC.size(); j++)
        {
            RefreshBoundaryCondition(row,j,i);
            row++;
        }
    }
}

void Manager::SaveLoad()
{
    for (int i = 0; i < theModel->rowCount(); i++)
    {
        int partIndex = -1;
        for (int j = 0; j < model->getPartNumber(); j++)
        {
            Part *part = model->getPart(j);
            if (part->PN == theModel->item(i,0)->text())
            {
                partIndex = j;
                break;
            }
        }
        if (partIndex == -1)
            continue;
        std::vector<LOAD> Load = model->getPart(partIndex)->F;
        if (Load[unsigned(i)].LoadType == 1)
        {
            Load[unsigned(i)].BPX = theModel->item(i,6)->text().toDouble();
            Load[unsigned(i)].BPY = theModel->item(i,7)->text().toDouble();
            model->getPart(partIndex)->F = Load;
            continue;
        }
        Load[unsigned(i)].PRIndex = theModel->item(i,3)->text().toInt();
        if (theModel->item(i,4)->text().toDouble() >= 0 &&
                theModel->item(i,4)->text().toDouble() <= 1)
            Load[unsigned(i)].MinRange = theModel->item(i,4)->text().toDouble();
        if (theModel->item(i,5)->text().toDouble() >= 0 &&
                theModel->item(i,5)->text().toDouble() <= 1)
            Load[unsigned(i)].MaxRange = theModel->item(i,5)->text().toDouble();
        Load[unsigned(i)].BPX = theModel->item(i,6)->text().toDouble();
        Load[unsigned(i)].BPY = theModel->item(i,7)->text().toDouble();
        Load[unsigned(i)].EPX = theModel->item(i,8)->text().toDouble();
        Load[unsigned(i)].EPY = theModel->item(i,9)->text().toDouble();
        model->getPart(partIndex)->F = Load;
    }
    int row = 0;
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        Part *part = model->getPart(i);
        for (int j = 0; j < int(part->BC.size()); j++)
        {
            RefreshLoad(row,j,i);
            row++;
        }
    }
}

void Manager::CopyMaterial()
{
    if (!theSelection->currentIndex().isValid())
        return;

    QModelIndex Index = theSelection->currentIndex();

    Material NewMaterial = *model->getMaterial(Index.row());
    QString Name = model->getMaterial(Index.row())->MN + QString("_复制");
    NewMaterial.MN = Name;

    model->addMaterial(NewMaterial);
}

void Manager::CopyPart()
{
    if (!theSelection->currentIndex().isValid())
        return;

    QModelIndex Index = theSelection->currentIndex();
    Part NewPart = *model->getPart(Index.row());
    QString Name = model->getPart(Index.row())->PN;
    NewPart.PN = Name;

    model->addPart(NewPart);
}

void Manager::CopyBoundaryCondition()
{
    if (!theSelection->currentIndex().isValid())
        return;
    QModelIndex Index = theSelection->currentIndex();
    int partIndex = -1;
    int BCIndex = - 1;
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        bool find = false;
        Part *part = model->getPart(i);
        for (unsigned int j = 0; j < part->BC.size(); j++)
        {
            if (part->BC[j].BCIndex == theModel->item(Index.row(),1)->text().toInt())
            {
                partIndex = i;
                BCIndex = int(j);
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
    if (partIndex == -1 || BCIndex == -1)
        return;
    std::vector<BC> BC = model->getPart(partIndex)->BC;
    BC.push_back(BC[unsigned(BCIndex)]);
    BC[BC.size()-1].BCIndex = model->getBoundaryConditionNumber();
    model->addBoundaryConditionNumber();
    model->getPart(partIndex)->BC = BC;
    Refresh(theModel->rowCount(),BCIndex,partIndex);
    SaveBoundaryCondition();
}

void Manager::CopyLoad()
{
    if (!theSelection->currentIndex().isValid())
        return;
    QModelIndex Index = theSelection->currentIndex();
    int partIndex = -1;
    int LoadIndex = - 1;
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        bool find = false;
        Part *part = model->getPart(i);
        for (unsigned int j = 0; j < part->F.size(); j++)
        {
            if (part->F[j].LoadIndex == theModel->item(Index.row(),1)->text().toInt())
            {
                partIndex = i;
                LoadIndex = int(j);
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
    if (partIndex == -1 || LoadIndex == -1)
        return;
    std::vector<LOAD> F = model->getPart(partIndex)->F;
    F.push_back(F[unsigned(LoadIndex)]);
    F[F.size()-1].LoadIndex = model->getLoadNumber();
    model->addLoadNumber();
    model->getPart(partIndex)->F = F;
    Refresh(theModel->rowCount(),LoadIndex,partIndex);
    SaveLoad();
}

void Manager::DeleteMaterial()
{
    if (!theSelection->currentIndex().isValid())
        return;

    QModelIndex Index = theSelection->currentIndex();

    model->removeMaterial(Index.row());
    theModel->removeRow(Index.row());
}

void Manager::DeletePart()
{
    if (!theSelection->currentIndex().isValid())
        return;

    QModelIndex Index = theSelection->currentIndex();

    model->removePart(Index.row());
    theModel->removeRow(Index.row());
}

void Manager::DeleteBoundaryCondition()
{
    if (!theSelection->currentIndex().isValid())
        return;
    QModelIndex Index = theSelection->currentIndex();
    int partIndex = -1;
    int BCIndex = - 1;
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        bool find = false;
        Part *part = model->getPart(i);
        for (unsigned int j = 0; j < part->BC.size(); j++)
        {
            if (part->BC[j].BCIndex == theModel->item(Index.row(),1)->text().toInt())
            {
                partIndex = i;
                BCIndex = int(j);
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
    if (partIndex == -1 || BCIndex == -1)
        return;
    std::vector<BC> BC = model->getPart(partIndex)->BC;
    BC.erase(std::begin(BC)+BCIndex);
    for (int i = BCIndex; i < int(BC.size()); i++)
        BC[unsigned(i)].BCIndex--;
    model->getPart(partIndex)->BC = BC;
    int row = 0;
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        Part *part = model->getPart(i);
        for (int j = 0; j < int(part->BC.size()); j++)
        {
            Refresh(row,j,i);
            row++;
        }
    }
    model->addBoundaryConditionNumber(-1);
    theModel->removeRow(Index.row());
    SaveBoundaryCondition();
}

void Manager::DeleteLoad()
{
    if (!theSelection->currentIndex().isValid())
        return;
    QModelIndex Index = theSelection->currentIndex();
    int partIndex = -1;
    int LoadIndex = - 1;
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        bool find = false;
        Part *part = model->getPart(i);
        for (unsigned int j = 0; j < part->F.size(); j++)
        {
            if (part->F[j].LoadIndex == theModel->item(Index.row(),1)->text().toInt())
            {
                partIndex = i;
                LoadIndex = int(j);
                find = true;
                break;
            }
        }
        if (find)
            break;
    }
    if (partIndex == -1 || LoadIndex == -1)
        return;
    std::vector<LOAD> F = model->getPart(partIndex)->F;
    F.erase(std::begin(F)+LoadIndex);
    for (int i = LoadIndex; i < int(F.size()); i++)
        F[unsigned(i)].LoadIndex--;
    model->getPart(partIndex)->F = F;
    int row = 0;
    for (int i = 0; i < model->getPartNumber(); i++)
    {
        Part *part = model->getPart(i);
        for (int j = 0; j < int(part->F.size()); j++)
        {
            Refresh(row,j,i);
            row++;
        }
    }
    model->addLoadNumber(-1);
    theModel->removeRow(Index.row());
    SaveLoad();
}
