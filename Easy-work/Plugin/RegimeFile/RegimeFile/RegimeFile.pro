#-------------------------------------------------
#
# Project created by QtCreator 2012-10-26T09:48:28
#
#-------------------------------------------------

TARGET = RegimeFile
TEMPLATE = lib

DEFINES += REGIMEFILE_LIBRARY

SOURCES += regimefile.cpp \
    installationPlugins.cpp \
    savesettings.cpp

HEADERS += regimefile.h\
        RegimeFile_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE2DF4087
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = RegimeFile.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix: {
    target.path = /usr/lib/EasyWork

    INSTALLS += target
}

INCLUDEPATH += $$PWD/../Plugin/OpenFile/
INCLUDEPATH += $$PWD/../Plugin/StatisticForRegimeFile/

DESTDIR = $$PWD/../../../Easy-work/lib/EasyWork

FORMS += \
    regimefile.ui \
    infoPrint.ui

RESOURCES += \
    icon.qrc
