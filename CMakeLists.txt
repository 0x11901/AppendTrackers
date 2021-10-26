# ****************************************************************************
# Copyright (c) 2018-2021 WANG,Jingkai. All rights reserved.
#
# This code is licensed under the MIT License (MIT).
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************

cmake_minimum_required(VERSION 3.20)
set(APP_NAME AppendTrackers)
project(${APP_NAME})

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)

if (MACOSX OR APPLE)
    # NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
    # the property added to Info.plist
    #     <key>CFBundleIconFile</key>
    #     <string>logo</string>
    set(MACOSX_BUNDLE_ICON_FILE logo)

    # And this part tells CMake where to find and install the file itself
    set(myApp_ICON ${CMAKE_CURRENT_SOURCE_DIR}/Images/logo.icns)
    # set_source_files_properties would create Resources folder to store icns
    # The folder is at same path where Info.plist located
    set_source_files_properties(${myApp_ICON} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")
elseif (WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/favicon.rc")
endif ()

add_executable(
        ${APP_NAME}
        main.cpp
        except.cpp
        except.h
        ${APP_ICON_RESOURCE_WINDOWS}
)

# Disable clip examples and tests
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

# In case that you have ${PNG_LIBRARY} set to support copy/paste images on Linux
#set(CLIP_X11_PNG_LIBRARY "${PNG_LIBRARY}")

# Add clip subdirectory to compile the library
add_subdirectory(clip)

# Add Boxer subdirectory to compile the library
add_subdirectory(Boxer)

target_link_libraries(
        ${APP_NAME}
        clip
        Boxer
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})