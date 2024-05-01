QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basiczombie.cpp \
    bucketzombie.cpp \
    cherrybomb.cpp \
    choose_plant.cpp \
    choose_plantbutton.cpp \
    conezombie.cpp \
    day.cpp \
    diggerzombie.cpp \
    doorzombie.cpp \
    footballzombie.cpp \
    grass.cpp \
    hammer.cpp \
    logon.cpp \
    logonbutton.cpp \
    main.cpp \
    mainwi.cpp \
    menu.cpp \
    mower.cpp \
    music.cpp \
    pea.cpp \
    peashooter.cpp \
    plant.cpp \
    plant_card.cpp \
    potatomine.cpp \
    screenzombie.cpp \
    seedbank.cpp \
    shop.cpp \
    snowpea.cpp \
    sokoban.cpp \
    sun.cpp \
    sunflower.cpp \
    wallnut.cpp \
    wallnutpush.cpp \
    wanttosay.cpp \
    whackgame.cpp \
    wisdom_tree.cpp \
    zombie.cpp

HEADERS += \
    basiczombie.h \
    bucketzombie.h \
    cherrybomb.h \
    choose_plant.h \
    choose_plantbutton.h \
    conezombie.h \
    day.h \
    diggerzombie.h \
    doorzombie.h \
    footballzombie.h \
    grass.h \
    hammer.h \
    init.h \
    init2.h \
    logon.h \
    logonbutton.h \
    mainwi.h \
    menu.h \
    mower.h \
    music.h \
    pea.h \
    peashooter.h \
    plant.h \
    plant_card.h \
    potatomine.h \
    screenzombie.h \
    seedbank.h \
    shop.h \
    snowpea.h \
    sokoban.h \
    sun.h \
    sunflower.h \
    wallnut.h \
    wallnutpush.h \
    wanttosay.h \
    whackgame.h \
    wisdom_tree.h \
    zombie.h

FORMS += \
    choose_plant.ui \
    day.ui \
    logon.ui \
    mainwi.ui \
    menu.ui \
    sokoban.ui \
    wanttosay.ui \
    whackgame.ui \
    wisdom_tree.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sucai.qrc

DISTFILES +=
