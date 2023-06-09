# Install script for directory: /root/uhd/host/include/uhd/types

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/uhd/types" TYPE FILE FILES
    "/root/uhd/host/include/uhd/types/byte_vector.hpp"
    "/root/uhd/host/include/uhd/types/clock_config.hpp"
    "/root/uhd/host/include/uhd/types/device_addr.hpp"
    "/root/uhd/host/include/uhd/types/dict.ipp"
    "/root/uhd/host/include/uhd/types/dict.hpp"
    "/root/uhd/host/include/uhd/types/direction.hpp"
    "/root/uhd/host/include/uhd/types/endianness.hpp"
    "/root/uhd/host/include/uhd/types/io_type.hpp"
    "/root/uhd/host/include/uhd/types/mac_addr.hpp"
    "/root/uhd/host/include/uhd/types/metadata.hpp"
    "/root/uhd/host/include/uhd/types/otw_type.hpp"
    "/root/uhd/host/include/uhd/types/ranges.hpp"
    "/root/uhd/host/include/uhd/types/ref_vector.hpp"
    "/root/uhd/host/include/uhd/types/sensors.hpp"
    "/root/uhd/host/include/uhd/types/serial.hpp"
    "/root/uhd/host/include/uhd/types/sid.hpp"
    "/root/uhd/host/include/uhd/types/stream_cmd.hpp"
    "/root/uhd/host/include/uhd/types/time_spec.hpp"
    "/root/uhd/host/include/uhd/types/tune_request.hpp"
    "/root/uhd/host/include/uhd/types/tune_result.hpp"
    "/root/uhd/host/include/uhd/types/wb_iface.hpp"
    "/root/uhd/host/include/uhd/types/filters.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/uhd/types" TYPE FILE FILES
    "/root/uhd/host/include/uhd/types/metadata.h"
    "/root/uhd/host/include/uhd/types/ranges.h"
    "/root/uhd/host/include/uhd/types/sensors.h"
    "/root/uhd/host/include/uhd/types/string_vector.h"
    "/root/uhd/host/include/uhd/types/tune_request.h"
    "/root/uhd/host/include/uhd/types/tune_result.h"
    "/root/uhd/host/include/uhd/types/usrp_info.h"
    )
endif()

