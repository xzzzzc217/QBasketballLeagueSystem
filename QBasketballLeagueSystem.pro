QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addmatchdialog.cpp \
    addplayerdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    match.cpp \
    matchplayersmanagerdialog.cpp \
    newteamdialog.cpp \
    player.cpp \
    playerperformance.cpp \
    removematchdialog.cpp \
    removeteamdialog.cpp \
    showallmatchdialog.cpp \
    showallteamdialog.cpp \
    team.cpp

HEADERS += \
    addmatchdialog.h \
    addplayerdialog.h \
    mainwindow.h \
    match.h \
    matchplayersmanagerdialog.h \
    newteamdialog.h \
    player.h \
    playerperformance.h \
    removematchdialog.h \
    removeteamdialog.h \
    showallmatchdialog.h \
    showallteamdialog.h \
    team.h

FORMS += \
    addmatchdialog.ui \
    addplayerdialog.ui \
    mainwindow.ui \
    matchplayersmanagerdialog.ui \
    newteamdialog.ui \
    removematchdialog.ui \
    removeteamdialog.ui \
    showallmatchdialog.ui \
    showallteamdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
