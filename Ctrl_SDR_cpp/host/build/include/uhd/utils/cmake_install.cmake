# Install script for directory: /root/uhd/host/include/uhd/utils

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/uhd/utils" TYPE FILE FILES
    "/root/uhd/host/include/uhd/utils/algorithm.hpp"
    "/root/uhd/host/include/uhd/utils/assert_has.hpp"
    "/root/uhd/host/include/uhd/utils/assert_has.ipp"
    "/root/uhd/host/include/uhd/utils/byteswap.hpp"
    "/root/uhd/host/include/uhd/utils/byteswap.ipp"
    "/root/uhd/host/include/uhd/utils/cast.hpp"
    "/root/uhd/host/include/uhd/utils/csv.hpp"
    "/root/uhd/host/include/uhd/utils/fp_compare_delta.ipp"
    "/root/uhd/host/include/uhd/utils/fp_compare_epsilon.ipp"
    "/root/uhd/host/include/uhd/utils/gain_group.hpp"
    "/root/uhd/host/include/uhd/utils/log.hpp"
    "/root/uhd/host/include/uhd/utils/log_add.hpp"
    "/root/uhd/host/include/uhd/utils/math.hpp"
    "/root/uhd/host/include/uhd/utils/msg_task.hpp"
    "/root/uhd/host/include/uhd/utils/noncopyable.hpp"
    "/root/uhd/host/include/uhd/utils/paths.hpp"
    "/root/uhd/host/include/uhd/utils/pimpl.hpp"
    "/root/uhd/host/include/uhd/utils/platform.hpp"
    "/root/uhd/host/include/uhd/utils/safe_call.hpp"
    "/root/uhd/host/include/uhd/utils/safe_main.hpp"
    "/root/uhd/host/include/uhd/utils/scope_exit.hpp"
    "/root/uhd/host/include/uhd/utils/static.hpp"
    "/root/uhd/host/include/uhd/utils/tasks.hpp"
    "/root/uhd/host/include/uhd/utils/thread_priority.hpp"
    "/root/uhd/host/include/uhd/utils/thread.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/uhd/utils" TYPE FILE FILES
    "/root/uhd/host/include/uhd/utils/thread_priority.h"
    "/root/uhd/host/include/uhd/utils/log.h"
    )
endif()

