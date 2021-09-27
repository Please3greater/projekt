TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        BossBullet.cpp \
        bonus.cpp \
        bonus2.cpp \
        bonus3.cpp \
        boss.cpp \
        bullet.cpp \
        enemy.cpp \
        explosion.cpp \
        game.cpp \
        main.cpp \
        player.cpp

INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    BossBullet.h \
    bonus.h \
    bonus2.h \
    bonus3.h \
    boss.h \
    bullet.h \
    enemy.h \
    explosion.h \
    game.h \
    player.h
