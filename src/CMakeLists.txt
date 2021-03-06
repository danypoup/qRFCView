#
# qRFCView, A smart IETF RFC viewer based on the Qt4 library.
# Copyright (C) 2015 Ľubomír Carik <Lubomir.Carik@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#


# just to show heders in some IDE's; otherwice redundant
set(${PROJECT_NAME}_HEADERS
    MainWindow.h
    RfcDocument.h
    RfcView.h
    TitleItem.h
    TitleModel.h
    cdialogfind.h
    cdialogsetdirectory.h
    rfcloader.h
)

set(${PROJECT_NAME}_SOURCES
    MainWindow.cpp
    RfcDocument.cpp
    RfcView.cpp
    TitleItem.cpp
    TitleModel.cpp
    cdialogfind.cpp
    cdialogsetdirectory.cpp
    main.cpp
    rfcloader.cpp
)

# just to show heders in some IDE's; otherwice redundant
set(${PROJECT_NAME}_FORMS
    MainWindow.ui
    find_dlg.ui
    setdirectory_dlg.ui
)

set(${PROJECT_NAME}_RESOURCES
    rfcview.qrc
)
if(WIN32)
    list(APPEND ${PROJECT_NAME}_RESOURCES
        rfcview.rc
    )
endif()

# generate version/revision information
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    @ONLY
    NEWLINE_STYLE LF
)
list(APPEND ${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_FORMS}
    ${${PROJECT_NAME}_RESOURCES}
)

if(Qt5_FOUND)
    target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Network
        Qt5::PrintSupport
    )
else()
    target_link_libraries(${PROJECT_NAME}
        Qt4::QtGui
        Qt4::QtNetwork
    )
endif()
