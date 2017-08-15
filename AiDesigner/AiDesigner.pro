TEMPLATE = app
QT += widgets printsupport

############################################################
ROOT =G:/projects/Qt/AiDesigner

LIBS += -L$${ROOT}/GuiLibs/QScintilla -lqscintilla2_qt5d
INCLUDEPATH += $${ROOT}/GuiLibs/QScintilla
############################################################

HEADERS += \
    Gui-colorswatch.h \
    Gui-mainwindow.h \
    Gui-toolbar.h \
    BLL-ParameterTab.h \
    BLL-MesgManager.h \
    BLL-ProjectsManagerTree.h \
    BASE-Plot.h \
    BASE-QCustomPlot.h \
    BLL-CentralShowTabWgt.h \
    BASE-DataTableWgt.h \
    BASE-Util.hpp \
    BASE-DataTableWgt.h \
    BASE-Plot.h \
    BASE-QCustomPlot.h \
    BASE-Util.hpp \
    BLL-CentralShowTabWgt.h \
    BLL-MesgManager.h \
    BLL-ParameterTab.h \
    BLL-ProjectsManagerTree.h \
    Gui-colorswatch.h \
    Gui-mainwindow.h \
    Gui-toolbar.h \
    BASE-TextDataWgt.h

SOURCES += \
    main.cpp \
    Gui-colorswatch.cpp \
    Gui-mainwindow.cpp \
    Gui-toolbar.cpp \
    BLL-ParameterTab.cpp \
    BLL-MesgManager.cpp \
    BLL-ProjectsManagerTree.cpp \
    BASE-Plot.cpp \
    BASE-QCustomPlot.cpp \
    BLL-CentralShowTabWgt.cpp \
    BASE-DataTableWgt.cpp \
    BASE-DataTableWgt.cpp \
    BASE-Plot.cpp \
    BASE-QCustomPlot.cpp \
    BLL-CentralShowTabWgt.cpp \
    BLL-MesgManager.cpp \
    BLL-ParameterTab.cpp \
    BLL-ProjectsManagerTree.cpp \
    Gui-colorswatch.cpp \
    Gui-mainwindow.cpp \
    Gui-toolbar.cpp \
    main.cpp \
    BASE-TextDataWgt.cpp

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

RESOURCES += mainwindow.qrc

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/mainwindow

target.path =$$[ProjectDir]/mainwindows
INSTALLS += target


