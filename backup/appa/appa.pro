QT += gui quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../common/EmployeeInfoModel.cpp \
        ../common/EmployeeListModel.cpp \
        ../common/database.cpp \
        ../common/ipc/mq/mq_ac.cpp \
        ../common/ipc/shm/shmem.cpp \
        main.cpp \
        ../common/SortFilterProxyModel.cpp

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
    ../common/EmployeeInfoModel.h \
    ../common/avnDefs.h \
    ../common/database.h \
    ../common/EmployeeListModel.h \
    ../common/ipc/mq/mq_ac.h \
    ../common/ipc/shm/shmem.h \
    ../common/nlohmann\json.hpp \
    ../common/SortFilterProxyModel.h

LIBS += -lrt
