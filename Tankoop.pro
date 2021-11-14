TEMPLATE = app
TARGET = Tankoop

QT = core gui
QT += widgets

SOURCES += \
    GameEntity/Basic.cpp \
    GameEntity/Block.cpp \
    GameEntity/Bullet.cpp \
    MainWindow.cpp \
    GameEntity/Tank.cpp \
    GameEntity/gameentity.cpp \
    main.cpp \

HEADERS += \
    GameEntity/Basic.h \
    GameEntity/Block.h \
    GameEntity/Bullet.h \
    MainWindow.h \
    GameEntity/Tank.h \
    GameEntity/gameentity.h

FORMS += \
    MainWindow.ui
