QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
0
CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Compression.cpp \
    Consistency.cpp \
    GraphDrawing.cpp \
    Prettify.cpp \
    Xml_to_Json.cpp \
    check_errors.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    minify.cpp

HEADERS += \
    Compression.h \
    Consistency.h \
    GraphDrawing.h \
    Prettify.h \
    Xml_to_Json.h \
    check_errors.h \
    graph.h \
    mainwindow.h \
    minify.h

FORMS += \
    graph.ui \
    mainwindow.ui



GRAPHVIZ_PATH = "C:/Program Files/Graphviz"
DEFINES += WIN32_DLL
DEFINES += GVDLL
INCLUDEPATH += $$GRAPHVIZ_PATH/include/graphviz
LIBS += -L$$GRAPHVIZ_PATH/lib -lgvc -lcgraph  -lcdt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc
RC_ICONS =application_icon.ico

