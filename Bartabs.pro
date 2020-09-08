QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix:INCLUDEPATH += "/usr/local/Cellar/boost/1.73.0/include/"
unix:LIBPATH += "/usr/local/Cellar/boost/1.73.0/lib/"

LIBS += -lsqlite3 -lboost_filesystem

SOURCES += \
    src/database.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/database.h \
    src/mainwindow.h \
    #include/catch2.hpp \
    include/sqlite_orm.h

FORMS += \
    src/mainwindow.ui

TRANSLATIONS += \
    src/Bartabs_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
