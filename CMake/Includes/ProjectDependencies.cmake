#
# Copyright (c) 2015, Ľubomír Carik <Lubomir.Carik@gmail.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#


# -------------------------------------------------------------------------------------------------
# Qt toolkit
# -------------------------------------------------------------------------------------------------

# Instruct CMake to run moc/uic/rrc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(OPT_ENFORCE_QT4_TXT "force Qt4-build (don't look for preferred Qt5)")
option(OPT_ENFORCE_QT4 ${OPT_ENFORCE_QT4_TXT} ON)
add_feature_info(OPT_ENFORCE_QT4 OPT_ENFORCE_QT4 ${OPT_ENFORCE_QT4_TXT})

if(NOT OPT_ENFORCE_QT4)
    find_package(Qt5Core QUIET)
endif()

# Find the Qt libraries
if(Qt5Core_FOUND)
    unset(QT_QMAKE_EXECUTABLE CACHE)
    set(PKG_NAME Qt5)
    set(PKG_VERSION 5.5)
    set(PKG_MODULE_LIST Core Widgets Gui Network PrintSupport)
else()
    set(PKG_NAME Qt4)
    set(PKG_VERSION 4.6.6)
    set(PKG_MODULE_LIST QtGui QtNetwork)
endif()
find_package(${PKG_NAME} ${PKG_VERSION} REQUIRED COMPONENTS ${PKG_MODULE_LIST})
set_package_properties(${PKG_NAME} PROPERTIES
    TYPE REQUIRED
    DESCRIPTION "cross-platform application framework"
    URL "http://qt-project.org/"
)


#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(Qt4
#    DEFAULT_MSG
#    Qt4_FOUND
#)

