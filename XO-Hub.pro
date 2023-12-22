QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connect4.cpp \
    main.cpp \
    mainwindow.cpp \
    pyramid_xo.cpp \
    tictactoe.cpp \
    tictactoe5x5.cpp

HEADERS += \
    BoardGames_Classes.hpp \
    connect4.h \
    mainwindow.h \
    pyramid_xo.h \
    tictactoe.h \
    tictactoe5x5.h

FORMS += \
    connect4.ui \
    mainwindow.ui \
    pyramid_xo.ui \
    tictactoe.ui \
    tictactoe5x5.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
    RC_ICONS = icons/Tictactoe.ico
