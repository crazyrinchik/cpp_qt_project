TEMPLATE = app

QT       += core gui widgets network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinanceMaster
TEMPLATE = app

SOURCES += \
    analysisdialog.cpp \
    cashback.cpp \
    currency_rate.cpp \
    listview.cpp \
    loggingcategory.cpp \
    main.cpp \
    mainwindow.cpp \
    sortdialog.cpp \
    start_page.cpp \
    tableview.cpp

HEADERS += \
    analysisdialog.h \
    cashback.h \
    currency_rate.h \
    listview.h \
    loggingcategory.h \
    mainwindow.h \
    proxymodel.h \
    sortdialog.h \
    start_page.h \
    tableview.h

FORMS += \
    analysisdialog.ui \
    cashback.ui \
    currency_rate.ui \
    listview.ui \
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
    resource.qrc

DISTFILES += \
    _17fc8ee5-7037-4e75-9cf4-348f010e09c0.jpeg
    
GTEST_DIR = ..somepath/googletest/googletest
GMOCK_DIR = ..somepath/googletest/googlemock

INCLUDEPATH += $$GTEST_DIR/include
INCLUDEPATH += $$GMOCK_DIR/include

LIBS += -L..somepath/googletest/build/lib -lgtest -lgtest_main
LIBS += -L..somepath/googletest/build/lib -lgmock -lgmock_main
