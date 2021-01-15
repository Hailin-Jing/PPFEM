#ifndef MESHPARAMETER_H
#define MESHPARAMETER_H

#include <QDialog>

namespace Ui {
class MeshParameter;
}

class MeshParameter : public QDialog
{
    Q_OBJECT

public:
    explicit MeshParameter(QWidget *parent = nullptr);
    ~MeshParameter();
    double getBoundaryNodes();
    double getHoleNodes();

private:
    Ui::MeshParameter *ui;
};

#endif // MESHPARAMETER_H
