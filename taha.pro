QT       += core gui sql widgets
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    editemployee.cpp \
    employee.cpp \
    main.cpp \
    mainwindow.cpp \
    searchemployee.cpp

HEADERS += \
    connection.h \
    editemployee.h \
    employee.h \
    mainwindow.h \
    searchemployee.h

FORMS += \
    editemployee.ui \
    mainwindow.ui \
    searchemployee.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    logo.png

RESOURCES += \
    resources.qrc
