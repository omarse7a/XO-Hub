QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/connect4.cpp \
    src/mainwindow.cpp \
    src/pyramid_xo.cpp \
    src/tictactoe.cpp \
    src/tictactoe5x5.cpp

HEADERS += \
    BoardGames_Classes.hpp \
    include/connect4.h \
    include/mainwindow.h \
    include/pyramid_xo.h \
    include/tictactoe.h \
    include/tictactoe5x5.h

FORMS += \
    ui/connect4.ui \
    ui/mainwindow.ui \
    ui/pyramid_xo.ui \
    ui/tictactoe.ui \
    ui/tictactoe5x5.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
    RC_ICONS = icons/Tictactoe.ico
