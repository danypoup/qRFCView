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

add_executable(qRFCView
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
)

if(Qt5_FOUND)
    target_link_libraries(qRFCView
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Network
    )
else()
    target_link_libraries(qRFCView
        Qt4::QtGui
        Qt4::QtNetwork
    )
endif()
