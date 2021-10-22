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

add_executable(
        ${APP_NAME}
        main.cpp
        except.cpp
        except.h)

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

# Boost
set(BOOST_ROOT C:/boost_1_77_0)
set(Boost_USE_STATIC_LIBS ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON)  # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED)
if (Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#
#    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
#    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
#    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    target_link_libraries(${APP_NAME} ${Boost_LIBRARIES})
endif ()