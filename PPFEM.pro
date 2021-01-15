#-------------------------------------------------
#
# Project created by QtCreator 2019-06-21T13:10:30
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PPFEM
TEMPLATE = app

RC_ICONS = icons/app_icon.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

CONFIG+=precompile_header
PRECOMPILED_HEADER = stable.h

SOURCES += \
    Src/Model/Element/TriangularElement/tri3.cpp \
    Src/Model/Element/TriangularElement/tri6.cpp \
    main.cpp \
    Src/Model/Examples/example_triangularelementsixnode.cpp \
    Src/Model/Examples/example_triangularelementthreenode.cpp \
    Src/Model/Part/DXFFilter/dxffilter.cpp \
    Src/Model/Part/DXFFilter/primitives.cpp \
    Src/Model/model.cpp \
    Src/View/QWChartView/qwchartview.cpp \
    Src/mainwindow.cpp \
    Src/View/PartWindow/ModeData/modeldata.cpp \
    Src/View/PartWindow/MeshParameter/meshparameter.cpp \
    Src/Model/Material/material.cpp \
    Src/Model/Part/part.cpp \
    Src/View/PartWindow/partwindow.cpp \
    dxflib/src/dl_dxf.cpp \
    dxflib/src/dl_writer_ascii.cpp \
    EasyMesh/Src/draw_eps.cpp \
    EasyMesh/Src/easymesh.cpp \
    EasyMesh/Src/easymesh_area.cpp \
    EasyMesh/Src/easymesh_bowyer.cpp \
    EasyMesh/Src/easymesh_circles.cpp \
    EasyMesh/Src/easymesh_classify.cpp \
    EasyMesh/Src/easymesh_compress.cpp \
    EasyMesh/Src/easymesh_diamond.cpp \
    EasyMesh/Src/easymesh_draw.cpp \
    EasyMesh/Src/easymesh_erase.cpp \
    EasyMesh/Src/easymesh_examples.cpp \
    EasyMesh/Src/easymesh_help.cpp \
    EasyMesh/Src/easymesh_in_elem.cpp \
    EasyMesh/Src/easymesh_insert_node.cpp \
    EasyMesh/Src/easymesh_load.cpp \
    EasyMesh/Src/easymesh_materials.cpp \
    EasyMesh/Src/easymesh_neighbours.cpp \
    EasyMesh/Src/easymesh_new_node.cpp \
    EasyMesh/Src/easymesh_parse.cpp \
    EasyMesh/Src/easymesh_relax.cpp \
    EasyMesh/Src/easymesh_save.cpp \
    EasyMesh/Src/easymesh_smooth.cpp \
    EasyMesh/Src/easymesh_spacing.cpp \
    EasyMesh/Src/easymesh_swap_side.cpp \
    EasyMesh/Src/timer.cpp \
    Src/View/PartWindow/PartWindowInputDialog/partinputdialog.cpp \
    Src/Dialog/MaterialInputDialog/materialinputdialog.cpp \
    Src/Dialog/PartChooseDialog/partchoosedialog.cpp \
    Src/View/BoundaryWindow/boundarywindow.cpp \
    Src/Dialog/BoundaryConditionDialog/boundaryconditiondialog.cpp \
    Src/Dialog/LoadDialog/loaddialog.cpp \
    Src/Dialog/NewLoadDialog/newloaddialog.cpp \
    Src/View/Manager/manager.cpp \
    Src/Dialog/JobDialog/jobdialog.cpp \
    Src/Model/test_gravityload.cpp \
    Src/Model/BCType/bc.cpp \
    Src/Model/LoadType/load.cpp \
    Src/View/DataVisualization/datavisualization.cpp

HEADERS += \
    Src/Model/Element/TriangularElement/tri3.h \
    Src/Model/Element/TriangularElement/tri6.h \
    Src/Model/Element/femelement.h \
    Src/Model/Part/DXFFilter/dxffilter.h \
    Src/Model/model.h \
    Src/View/QWChartView/qwchartview.h \
    Src/mainwindow.h \
    Src/Model/Math/Math.h \
    Src/View/PartWindow/ModeData/modeldata.h \
    Src/View/PartWindow/MeshParameter/meshparameter.h \
    Src/Model/Material/material.h \
    Src/Model/Part/part.h \
    Src/View/PartWindow/partwindow.h \
    Src/Model/Part/DXFFilter/primitive.h \
    dxflib/src/dl_attributes.h \
    dxflib/src/dl_codes.h \
    dxflib/src/dl_creationadapter.h \
    dxflib/src/dl_creationinterface.h \
    dxflib/src/dl_dxf.h \
    dxflib/src/dl_entities.h \
    dxflib/src/dl_exception.h \
    dxflib/src/dl_extrusion.h \
    dxflib/src/dl_global.h \
    dxflib/src/dl_writer.h \
    dxflib/src/dl_writer_ascii.h \
    EasyMesh/Src/chain.h \
    EasyMesh/Src/draw_eps.h \
    EasyMesh/Src/easymesh.h \
    EasyMesh/Src/easymesh_constants.h \
    EasyMesh/Src/element.h \
    EasyMesh/Src/node.h \
    EasyMesh/Src/options.h \
    EasyMesh/Src/precision.h \
    EasyMesh/Src/print.h \
    EasyMesh/Src/segment.h \
    EasyMesh/Src/side.h \
    EasyMesh/Src/timer.h \
    Src/View/PartWindow/PartWindowInputDialog/partinputdialog.h \
    Src/Dialog/MaterialInputDialog/materialinputdialog.h \
    Src/Dialog/PartChooseDialog/partchoosedialog.h \
    Src/View/BoundaryWindow/boundarywindow.h \
    Src/Dialog/BoundaryConditionDialog/boundaryconditiondialog.h \
    Src/Dialog/LoadDialog/loaddialog.h \
    Src/Dialog/NewLoadDialog/newloaddialog.h \
    Src/View/Manager/manager.h \
    Src/Dialog/JobDialog/jobdialog.h \
    Src/Model/test_model.h \
    Src/Model/BCType/bc.h \
    Src/Model/LoadType/load.h \
    stable.h \
    Src/View/DataVisualization/datavisualization.h

FORMS += \
    Src/mainwindow.ui \
    Src/View/PartWindow/ModeData/modeldata.ui \
    Src/View/PartWindow/MeshParameter/meshparameter.ui \
    Src/View/PartWindow/partwindow.ui \
    Src/View/PartWindow/PartWindowInputDialog/partinputdialog.ui \
    Src/Dialog/MaterialInputDialog/materialinputdialog.ui \
    Src/Dialog/PartChooseDialog/partchoosedialog.ui \
    Src/View/BoundaryWindow/boundarywindow.ui \
    Src/Dialog/BoundaryConditionDialog/boundaryconditiondialog.ui \
    Src/Dialog/LoadDialog/loaddialog.ui \
    Src/Dialog/NewLoadDialog/newloaddialog.ui \
    Src/View/Manager/manager.ui \
    Src/Dialog/JobDialog/jobdialog.ui \
    Src/View/DataVisualization/datavisualization.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ININCLUDEPATH += $$PWDCLUDEPATH += $$PWD/EasyMesh/Src/
INCLUDEPATH += $$PWD/dxflib/src/
#INCLUDEPATH += $$PWD/Eigen3/

INCLUDEPATH += $$PWD/Src/Model/
INCLUDEPATH += $$PWD/Src/Model/Math
INCLUDEPATH += $$PWD/Src/Model/Material/
INCLUDEPATH += $$PWD/Src/Model/Part/
INCLUDEPATH += $$PWD/Src/Model/Part/DXFFilter/
INCLUDEPATH += $$PWD/Src/Model/Element/
INCLUDEPATH += $$PWD/Src/Model/Element/TriangularElement/
INCLUDEPATH += $$PWD/Src/Model/Examples/
INCLUDEPATH += $$PWD/Src/Model/BCType/
INCLUDEPATH += $$PWD/Src/Model/LoadType/
INCLUDEPATH += $$PWD/Src/View/QWChartView/
INCLUDEPATH += $$PWD/Src/View/PartWindow/
INCLUDEPATH += $$PWD/Src/View/PartWindow/ModeData/
INCLUDEPATH += $$PWD/Src/View/PartWindow/MeshParameter/
INCLUDEPATH += $$PWD/Src/View/PartWindow/PartWindowInputDialog/
INCLUDEPATH += $$PWD/Src/Dialog/MaterialInputDialog/
INCLUDEPATH += $$PWD/Src/Dialog/PartChooseDialog/
INCLUDEPATH += $$PWD/Src/View/BoundaryWindow/
INCLUDEPATH += $$PWD/Src/Dialog/BoundaryConditionDialog/
INCLUDEPATH += $$PWD/Src/Dialog/LoadDialog/
INCLUDEPATH += $$PWD/Src/Dialog/NewLoadDialog/
INCLUDEPATH += $$PWD/Src/View/Manager/
INCLUDEPATH += $$PWD/Src/Dialog/JobDialog/
INCLUDEPATH += $$PWD/Src/View/DataVisualization/

RESOURCES += \
    icons.qrc
