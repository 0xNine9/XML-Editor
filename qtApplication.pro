QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CharFrequencyTable.cpp \
    Compressor.cpp \
    FileHandler.cpp \
    FrequencyTable.cpp \
    SString.cpp \
    SocialNetwork.cpp \
    User.cpp \
    WordFrequencyTable.cpp \
    XmlEditor.cpp \
    main.cpp \
    mainwindow.cpp \
    tree.cpp

HEADERS += \
    CharFrequencyTable.h \
    Compressor.h \
    Dict.h \
    FileHandler.h \
    FrequencyTable.h \
    SString.h \
    SocialNetwork.h \
    User.h \
    WordFrequencyTable.h \
    XmlEditor.h \
    convert.h \
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
