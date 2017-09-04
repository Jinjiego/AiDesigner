TEMPLATE = app
QT += widgets printsupport

############################################################
ROOT =I:/Projects/Qt/AiDesigner

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
    BLL-CentralShowTabWgt.h \
    BLL-CentralShowTabWgt.h \
    BLL-MesgManager.h \
    BLL-ParameterTab.h \
    BLL-ProjectsManagerTree.h \
    Gui-colorswatch.h \
    Gui-mainwindow.h \
    Gui-toolbar.h \
    svm/svm.h \
    baseWgt/BASE-DataTableWgt.h \
    baseWgt/BASE-Plot.h \
    baseWgt/BASE-QCustomPlot.h \
    baseWgt/BASE-TextDataWgt.h \
    baseWgt/BASE-Type.hpp \
    baseWgt/BASE-Util.hpp\
    Solvers/Learner.hpp \
    CplusHeader.h \
    Common.h \
    GlobalVars.h \
    BLL-ProgressWgt.h \
    svm/AiSvm.h \
    svm/BLL_SVM_UI.h \
    baseWgt/BASE-zoomAbleTableWgt.h


SOURCES += \
    main.cpp \
    Gui-colorswatch.cpp \
    Gui-mainwindow.cpp \
    Gui-toolbar.cpp \
    BLL-ParameterTab.cpp \
    BLL-MesgManager.cpp \
    BLL-ProjectsManagerTree.cpp \
    BLL-CentralShowTabWgt.cpp \
    BLL-CentralShowTabWgt.cpp \
    BLL-MesgManager.cpp \
    BLL-ParameterTab.cpp \
    BLL-ProjectsManagerTree.cpp \
    Gui-colorswatch.cpp \
    Gui-mainwindow.cpp \
    Gui-toolbar.cpp \
    main.cpp \
    svm/svm.cpp \
    baseWgt/BASE-DataTableWgt.cpp \
    baseWgt/BASE-Plot.cpp \
    baseWgt/BASE-QCustomPlot.cpp \
    baseWgt/BASE-TextDataWgt.cpp \
    Common.cpp \
    GlobalVars.cpp \
    BLL-ProgressWgt.cpp \
    svm/AiSvm.cpp \
    svm/BLL_SVM_UI.cpp \
    baseWgt/BASE-zoomAbleTableWgt.cpp

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

RESOURCES += mainwindow.qrc

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/mainwindow

target.path =$$[ProjectDir]/mainwindows
INSTALLS += target

DISTFILES +=

FORMS +=


