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
    main.cpp \
    Src/Model/Element/TriangularElement/triangularelementsixnode.cpp \
    Src/Model/Element/TriangularElement/triangularelementthreenode.cpp \
    Src/Model/Examples/example_triangularelementsixnode.cpp \
    Src/Model/Examples/example_triangularelementthreenode.cpp \
    Src/Model/Part/DXFFilter/dxffilter.cpp \
    Src/Model/Part/DXFFilter/primitives.cpp \
    Src/Model/model.cpp \
    Src/QWChartView/qwchartview.cpp \
    Src/mainwindow.cpp \
    Src/PartWindow/ModeData/modeldata.cpp \
    Src/PartWindow/MeshParameter/meshparameter.cpp \
    Src/Model/Material/material.cpp \
    Src/Model/Part/part.cpp \
    Src/PartWindow/partwindow.cpp \
    dxflib/src/dl_dxf.cpp \
    dxflib/src/dl_writer_ascii.cpp \
    EasyMeshMaster/Src/draw_eps.cpp \
    EasyMeshMaster/Src/easymesh.cpp \
    EasyMeshMaster/Src/easymesh_area.cpp \
    EasyMeshMaster/Src/easymesh_bowyer.cpp \
    EasyMeshMaster/Src/easymesh_circles.cpp \
    EasyMeshMaster/Src/easymesh_classify.cpp \
    EasyMeshMaster/Src/easymesh_compress.cpp \
    EasyMeshMaster/Src/easymesh_diamond.cpp \
    EasyMeshMaster/Src/easymesh_draw.cpp \
    EasyMeshMaster/Src/easymesh_erase.cpp \
    EasyMeshMaster/Src/easymesh_examples.cpp \
    EasyMeshMaster/Src/easymesh_help.cpp \
    EasyMeshMaster/Src/easymesh_in_elem.cpp \
    EasyMeshMaster/Src/easymesh_insert_node.cpp \
    EasyMeshMaster/Src/easymesh_load.cpp \
    EasyMeshMaster/Src/easymesh_materials.cpp \
    EasyMeshMaster/Src/easymesh_neighbours.cpp \
    EasyMeshMaster/Src/easymesh_new_node.cpp \
    EasyMeshMaster/Src/easymesh_parse.cpp \
    EasyMeshMaster/Src/easymesh_relax.cpp \
    EasyMeshMaster/Src/easymesh_save.cpp \
    EasyMeshMaster/Src/easymesh_smooth.cpp \
    EasyMeshMaster/Src/easymesh_spacing.cpp \
    EasyMeshMaster/Src/easymesh_swap_side.cpp \
    EasyMeshMaster/Src/timer.cpp \
    Src/Model/Element/myelement.cpp \
    Src/PartWindow/PartWindowInputDialog/partinputdialog.cpp \
    Src/MaterialInputDialog/materialinputdialog.cpp \
    Src/PartChooseDialog/partchoosedialog.cpp \
    Src/BoundaryWindow/boundarywindow.cpp \
    Src/BoundaryConditionDialog/boundaryconditiondialog.cpp \
    Src/LoadDialog/loaddialog.cpp \
    Src/NewLoadDialog/newloaddialog.cpp \
    Src/Manager/manager.cpp \
    Src/JobDialog/jobdialog.cpp \
    Src/Model/test_gravityload.cpp \
    Src/Model/BCType/bc.cpp \
    Src/Model/LoadType/load.cpp \
    Src/DataVisualization/datavisualization.cpp

HEADERS += \
    Src/Model/Element/TriangularElement/triangularelementsixnode.h \
    Src/Model/Element/TriangularElement/triangularelementthreenode.h \
    Src/Model/Part/DXFFilter/dxffilter.h \
    Src/Model/model.h \
    Src/QWChartView/qwchartview.h \
    Src/mainwindow.h \
    Src/Model/Math/LU.h \
    Src/PartWindow/ModeData/modeldata.h \
    Src/PartWindow/MeshParameter/meshparameter.h \
    Src/Model/Material/material.h \
    Src/Model/Part/part.h \
    Src/PartWindow/partwindow.h \
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
    EasyMeshMaster/Src/chain.h \
    EasyMeshMaster/Src/draw_eps.h \
    EasyMeshMaster/Src/easymesh.h \
    EasyMeshMaster/Src/easymesh_constants.h \
    EasyMeshMaster/Src/element.h \
    EasyMeshMaster/Src/node.h \
    EasyMeshMaster/Src/options.h \
    EasyMeshMaster/Src/precision.h \
    EasyMeshMaster/Src/print.h \
    EasyMeshMaster/Src/segment.h \
    EasyMeshMaster/Src/side.h \
    EasyMeshMaster/Src/timer.h \
    Src/Model/Element/myelement.h \
    Src/PartWindow/PartWindowInputDialog/partinputdialog.h \
    Src/MaterialInputDialog/materialinputdialog.h \
    Src/PartChooseDialog/partchoosedialog.h \
    Src/BoundaryWindow/boundarywindow.h \
    Src/BoundaryConditionDialog/boundaryconditiondialog.h \
    Src/LoadDialog/loaddialog.h \
    Src/NewLoadDialog/newloaddialog.h \
    Src/Manager/manager.h \
    Src/JobDialog/jobdialog.h \
    Src/Model/test_model.h \
    Src/Model/BCType/bc.h \
    Src/Model/LoadType/load.h \
    stable.h \
    Src/DataVisualization/datavisualization.h

FORMS += \
    Src/mainwindow.ui \
    Src/PartWindow/ModeData/modeldata.ui \
    Src/PartWindow/MeshParameter/meshparameter.ui \
    Src/PartWindow/partwindow.ui \
    Src/PartWindow/PartWindowInputDialog/partinputdialog.ui \
    Src/MaterialInputDialog/materialinputdialog.ui \
    Src/PartChooseDialog/partchoosedialog.ui \
    Src/BoundaryWindow/boundarywindow.ui \
    Src/BoundaryConditionDialog/boundaryconditiondialog.ui \
    Src/LoadDialog/loaddialog.ui \
    Src/NewLoadDialog/newloaddialog.ui \
    Src/Manager/manager.ui \
    Src/JobDialog/jobdialog.ui \
    Src/DataVisualization/datavisualization.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ININCLUDEPATH += $$PWDCLUDEPATH += $$PWD/EasyMeshMaster/Src/
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
INCLUDEPATH += $$PWD/Src/QWChartView/
INCLUDEPATH += $$PWD/Src/PartWindow/
INCLUDEPATH += $$PWD/Src/PartWindow/ModeData/
INCLUDEPATH += $$PWD/Src/PartWindow/MeshParameter/
INCLUDEPATH += $$PWD/Src/PartWindow/PartWindowInputDialog/
INCLUDEPATH += $$PWD/Src/MaterialInputDialog/
INCLUDEPATH += $$PWD/Src/PartChooseDialog/
INCLUDEPATH += $$PWD/Src/BoundaryWindow/
INCLUDEPATH += $$PWD/Src/BoundaryConditionDialog/
INCLUDEPATH += $$PWD/Src/LoadDialog/
INCLUDEPATH += $$PWD/Src/NewLoadDialog/
INCLUDEPATH += $$PWD/Src/Manager/
INCLUDEPATH += $$PWD/Src/JobDialog/
INCLUDEPATH += $$PWD/Src/DataVisualization/

RESOURCES += \
    icons.qrc
