QT += gui quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AppController.cpp \
        EmployeeInfoModel.cpp \
        EmployeeListModel.cpp \
        ../common/ipc/mq/mq.cpp \
        ../common/ipc/shm/shmem.cpp \
        main.cpp \
        SortFilterProxyModel.cpp \
        mq_a.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    AppController.h \
    EmployeeInfoModel.h \
    ../common/avnDefs.h \
    EmployeeListModel.h \
    ../common/ipc/mq/mq.h \
    ../common/ipc/shm/shmem.h \
    SortFilterProxyModel.h \
    mq_a.h

LIBS += -lrt
