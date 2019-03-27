CONFIG += c++11

QT += network

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \  
    $$PWD/src/question.cpp \
    $$PWD/src/answer.cpp \
    $$PWD/src/questiongroup.cpp \
    $$PWD/src/game.cpp \
    $$PWD/src/connectionlistener.cpp \
    $$PWD/src/tcpconnectionlistener.cpp \
    $$PWD/src/player.cpp \
    $$PWD/src/playerbackend.cpp \
    $$PWD/src/playertcpbackend.cpp

RESOURCES += \
    $$PWD/mathquiz.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

HEADERS += \
    $$PWD/src/question.h \
    $$PWD/src/answer.h \
    $$PWD/src/questiongroup.h \
    $$PWD/src/game.h \
    $$PWD/src/connectionlistener.h \
    $$PWD/src/tcpconnectionlistener.h \
    $$PWD/src/player.h \
    $$PWD/src/playerbackend.h \
    $$PWD/src/playertcpbackend.h

