# just to show heders in some IDE's; otherwice redundant
set(HEADERS
    mainwindow.h
    mdichild.h
    TitleModel.h
    TitleItem.h
    qrfceditor.h
    cdialogsetdirectory.h
    rfcloader.h
    cdialogfind.h
    cprintdialog.h
)

set(SOURCES
    rfcview.cpp
    mainwindow.cpp
    mdichild.cpp
    TitleModel.cpp
    TitleItem.cpp
    qrfceditor.cpp
    cdialogsetdirectory.cpp
    rfcloader.cpp
    cdialogfind.cpp
    cprintdialog.cpp
)
set(RESOURCES
    rfcview.qrc
)
if(WIN32)
    list(APPEND RESOURCES src.rc)
endif()

# Qt4 stuff
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt4 4.8.6 REQUIRED QtGui QtNetwork)

add_executable(qRFCView
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
)

target_link_libraries(qRFCView
    Qt4::QtGui
    Qt4::QtNetwork
)
