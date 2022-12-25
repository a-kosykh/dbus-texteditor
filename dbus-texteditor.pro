QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbusconnector.cpp \
    main.cpp \
    maindbusservice.cpp \
    mainwindow.cpp

HEADERS += \
    dbusconnector.h \
    defs.h \
    maindbusservice.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

DBUS_ADAPTORS += org.example.dbustexteditor.xml
DBUS_INTERFACES += org.example.dbustexteditor.xml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    org.example.dbustexteditor.xml
