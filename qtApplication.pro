QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CharFrequencyTable.cpp \
    Compression.cpp \
    FrequencyTable.cpp \
    Util.cpp \
    WordFrequencyTable.cpp \
    consistency.cpp \
    formatter.cpp \
    main.cpp \
    mainwindow.cpp \
    tree.cpp

HEADERS += \
    CharFrequencyTable.h \
    Compression.h \
    Dict.h \
    FrequencyTable.h \
    Util.h \
    WordFrequencyTable.h \
    consistency.h \
    formatter.h \
    mainwindow.h \
    tree.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
