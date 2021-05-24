QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += $$PWD

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(utils/utils.pri)

SOURCES += \
    main.cpp \
    dialog.cpp \

HEADERS += \
    dialog.h \

FORMS += \
    dialog.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    cli.qrc

ios{

LIBS += -F$$PWD/libs/ios/ -framework NodeMobile

INCLUDEPATH += $$PWD/libs/ios
DEPENDPATH += $$PWD/libs/ios

IOS_FRAMEWORK.files = $$PWD/libs/ios/NodeMobile.framework  # For example /Library/aSharedLibrary/exampleLibrary.dylib
IOS_FRAMEWORK.path = Frameworks   # This is the essential keyword for qmake to add the desired Framework as "embedded Framework"
QMAKE_BUNDLE_DATA += IOS_FRAMEWORK

}

android{
#https://doc.qt.io/qt-5/qmake-variable-reference.html
LIBS += -L$$PWD/libs/android/bin/x86/ -lnode
LIBS += -L$$PWD/libs/android/bin/armeabi-v7a/ -lnode

INCLUDEPATH += $$PWD/libs/android/include/node
DEPENDPATH += $$PWD/libs/android/include/node

ANDROID_EXTRA_LIBS += $$PWD/libs/android/bin/x86/libnode.so
ANDROID_EXTRA_LIBS += $$PWD/libs/android/bin/armeabi-v7a/libnode.so

}

