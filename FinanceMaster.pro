QT       += core gui widgets
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sortdialog.cpp \
    start_page.cpp \
    tableview.cpp

HEADERS += \
    mainwindow.h \
    proxymodel.h \
    sortdialog.h \
    start_page.h \
    tableview.h

FORMS += \
    mainwindow.ui \
    sortdialog.ui \
    start_page.ui \
    tableview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    _17fc8ee5-7037-4e75-9cf4-348f010e09c0.jpeg
