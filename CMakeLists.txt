#
# qRFCView, A smart IETF RFC viewer based on the Qt library.
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


project(qRFCView CXX)
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

message(STATUS "Using cmake v${CMAKE_VERSION}")
message(STATUS "Started on ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_VERSION})")

# setup project strings
set(PROJECT_ORG_NAME "TrollSoft")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Common/Includes/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Common/Modules/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Includes/")

# Enable info gathering for final summary
include(FeatureSummary)

# Check compiler supported features.
include(ProjectCompilerFlags)
# Various project user friendly configuration settings and options.
include(ProjectSetup)
# Check VCS-id of root project
include(ProjectVCS-id)
# Look for and setup dependencies like 3rd party libraries etc.
include(ProjectDependencies)


# set project version number
set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "64")
set(PROJECT_VERSION_DOTPATCH "")
if(NOT ${VCS_BRANCH_NAME} STREQUAL "")
    set(PROJECT_VERSION_DOTPATCH "${PROJECT_VERSION_DOTPATCH}-${VCS_BRANCH_NAME}")
endif()
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}${PROJECT_VERSION_DOTPATCH}")
message(STATUS "Configuring '${PROJECT_NAME}' v${PROJECT_VERSION} project")


# Local project settings
set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_subdirectory(src)
if(DOXYGEN_FOUND)
    add_subdirectory(Documentation)
endif()


# Generate summary of required/optional/runtime packages, enabled/disabled features.
include(ProjectSummary)


if(OPT_PRINTSYSINFO)
    include(CMakePrintSystemInformation)
endif(OPT_PRINTSYSINFO)
