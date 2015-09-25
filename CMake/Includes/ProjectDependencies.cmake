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


# Find the Qt libraries
find_package(Qt4 4.8.6 REQUIRED QtGui QtNetwork)
set_package_properties(Qt4 PROPERTIES
    TYPE REQUIRED
    DESCRIPTION "cross-platform application framework"
    URL "http://qt-project.org/"
)

#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(Qt4
#    DEFAULT_MSG
#    Qt4_FOUND
#)


# -------------------------------------------------------------------------------------------------
# Doxygen tool
# -------------------------------------------------------------------------------------------------
find_package(Doxygen 1.8.9)
set_package_properties(Doxygen PROPERTIES
    TYPE OPTIONAL
    DESCRIPTION "documentation generator, a tool for writing software reference documentation"
    URL "http://www.doxygen.org"
)
if(DOXYGEN_FOUND)
    message(STATUS "Reference manual can be created by using the 'doc' target")
else()
    message(WARNING "Doxygen not found - Reference manual will not be created")
endif()
