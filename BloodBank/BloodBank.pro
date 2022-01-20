QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddonor.cpp \
    adminlogin.cpp \
    bloodstock.cpp \
    deletedonor.cpp \
    homepage.cpp \
    main.cpp \
    login.cpp \
    newpatient.cpp \
    newuser.cpp \
    searchdonor.cpp \
    searchpatient.cpp \
    updatedonor.cpp \
    updatepatient.cpp

HEADERS += \
    adddonor.h \
    adminlogin.h \
    bloodstock.h \
    deletedonor.h \
    homepage.h \
    login.h \
    newpatient.h \
    newuser.h \
    searchdonor.h \
    searchpatient.h \
    updatedonor.h \
    updatepatient.h

FORMS += \
    adddonor.ui \
    adminlogin.ui \
    bloodstock.ui \
    deletedonor.ui \
    homepage.ui \
    login.ui \
    newpatient.ui \
    newuser.ui \
    searchdonor.ui \
    searchpatient.ui \
    updatedonor.ui \
    updatepatient.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
