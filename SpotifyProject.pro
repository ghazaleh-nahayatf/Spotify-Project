QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        account.cpp \
        accountservice.cpp \
        album.cpp \
        albumfilemanger.cpp \
        albumrepository.cpp \
        artist.cpp \
        artistfilemanger.cpp \
        artistrepository.cpp \
        artistservice.cpp \
        commonservice.cpp \
        entryservice.cpp \
        fileexception.cpp \
        listener.cpp \
        listenerfilemanger.cpp \
        listenerrepository.cpp \
        listenerservice.cpp \
        main.cpp \
        playlist.cpp \
        playlistfilemanger.cpp \
        playlistrepository.cpp \
        song.cpp \
        songfilemanager.cpp \
        songrepository.cpp \
        spotifyexception.cpp

TRANSLATIONS += \
    SpotifyProject_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    abstractrepository.h \
    account.h \
    accountrepository.h \
    accountservice.h \
    album.h \
    albumfilemanger.h \
    albumrepository.h \
    artist.h \
    artistfilemanger.h \
    artistrepository.h \
    artistservice.h \
    commonservice.h \
    entryservice.h \
    fileexception.h \
    listener.h \
    listenerfilemanger.h \
    listenerrepository.h \
    listenerservice.h \
    playlist.h \
    playlistfilemanger.h \
    playlistrepository.h \
    song.h \
    songfilemanager.h \
    songrepository.h \
    spotifyexception.h
