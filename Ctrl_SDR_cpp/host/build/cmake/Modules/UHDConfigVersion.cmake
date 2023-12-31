#
# Copyright 2014 Ettus Research LLC
# Copyright 2018 Ettus Research, a National Instruments Company
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# When "find_package" is provided with UHD and a version, this file is
# called to try to determine if the requested version matches that
# provided by this UHD install.  All version checking is done herein.
########################################################################

# set that this file was found, for use in GNU Radio's FindUHD.cmake.
# Have to use the ENV, since this file might not allow CACHE changes.

set(ENV{UHD_CONFIG_VERSION_USED} TRUE)

# version values as set in cmake/Modules/UHDVersion.cmake, placed
# statically in here to avoid using Python all over again.

set(MAJOR_VERSION 3)
set(API_VERSION 15)
set(ABI_VERSION 0)
set(PATCH_VERSION main)
set(DEVEL_VERSION TRUE)

set(PACKAGE_VERSION "3.15.0.main-0-33359f8a")
set(ENV{UHD_PACKAGE_VERSION} ${PACKAGE_VERSION})

# There is a bug in CMake whereby calling "find_package(FOO)" within
# "find_package(FOO)" results in the version being checked in the
# second version no matter if it was set.  To get around this, check
# "PACKAGE_FIND_VERSION" and if empty set return variables to TRUE to
# make CMake happy.  Not the best solution, but it does the trick.

if(NOT PACKAGE_FIND_VERSION)
  set(PACKAGE_VERSION_COMPATIBLE TRUE)
  set(PACKAGE_VERSION_EXACT TRUE)
  return()
endif(NOT PACKAGE_FIND_VERSION)

# Development branches of UHD don't have a patch version. This is a hack
# to add a fake patch version that should be higher than anything the user
# requests.
if(DEVEL_VERSION)
    set(PACKAGE_VERSION "${MAJOR_VERSION}.${API_VERSION}.${ABI_VERSION}.999")
endif(DEVEL_VERSION)

# assume incorrect versioning by default
set(PACKAGE_VERSION_COMPATIBLE FALSE)
set(PACKAGE_VERSION_EXACT FALSE)

# do not use ABI for now
set(UHD_USE_ABI FALSE)

# leave the ABI checking in, for now, just in case it is wanted in the
# future.  This code works nicely to find the ABI compatibility
# version from <uhd/version.hpp>.
if(UHD_USE_ABI)

  # find ABI compatible version from <uhd/version.hpp>

  set(UHD_INCLUDE_HINTS)
  set(UHD_DIR $ENV{UHD_DIR})

  if(UHD_DIR)
    list(APPEND UHD_INCLUDE_HINTS ${UHD_DIR}/include)
  endif()

  include(FindPkgConfig)
  if(PKG_CONFIG_FOUND)
    if(NOT ${CMAKE_VERSION} VERSION_LESS "2.8.0")
      set(UHD_QUIET "QUIET")
    endif()
    if(PACKAGE_VERSION_EXACT)
      PKG_CHECK_MODULES(PC_UHD ${UHD_QUIET} uhd=${UHD_FIND_VERSION})
    else()
      PKG_CHECK_MODULES(PC_UHD ${UHD_QUIET} uhd>=${UHD_FIND_VERSION})
    endif()
    if(PC_UHD_FOUND)
      list(APPEND UHD_INCLUDE_HINTS ${PC_UHD_INCLUDEDIR})
    endif()
  endif()

  list(APPEND UHD_INCLUDE_HINTS ${CMAKE_INSTALL_PREFIX}/include)

  # Verify that <uhd/config.hpp> and libuhd are available, and, if a
  # version is provided, that UHD meets the version requirements -- no
  # matter what pkg-config might think.

  find_path(
    UHD_INCLUDE_DIR
    NAMES uhd/version.hpp
    HINTS ${UHD_INCLUDE_HINTS}
    PATHS /usr/local/include
          /usr/include
  )

  if(UHD_INCLUDE_DIR)

    # extract the UHD API version from the installed header

    file(STRINGS "${UHD_INCLUDE_DIR}/uhd/version.hpp"
      UHD_STRING_VERSION REGEX "UHD_VERSION_ABI_STRING")
    string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+"
      UHD_ABI_VERSION_CONCISE ${UHD_STRING_VERSION})

    # convert UHD_FIND_VERSION into concise #.#.# format for comparison

    string(REGEX REPLACE "([^\\.]*)\\.([^\\.]*)\\.([^\\.]*)"
      "\\1.\\2.\\3" UHD_ABI_VERSION_TMP ${UHD_ABI_VERSION_CONCISE})

    string(REPLACE "0" "" UHD_ABI_MAJOR ${CMAKE_MATCH_1})
    string(REPLACE "0" "" UHD_ABI_MINOR ${CMAKE_MATCH_2})
    string(REPLACE "0" "" UHD_ABI_PATCH ${CMAKE_MATCH_3})

    # fix the case where the version number is "000"

    if(NOT UHD_ABI_MAJOR)
      set(UHD_ABI_MAJOR "0")
    endif()
    if(NOT UHD_ABI_MINOR)
      set(UHD_ABI_MINOR "0")
    endif()
    if(NOT UHD_ABI_PATCH)
      set(UHD_ABI_PATCH "0")
    endif()

    set(UHD_ABI_VERSION_CONCISE ${UHD_ABI_MAJOR}.${UHD_ABI_MINOR}.${UHD_ABI_PATCH})

  else(UHD_INCLUDE_DIR)

    # no header found ... not a good sign!  Assume ABI version is the
    # same as that known internally here.  Let UHDConfig.cmake fail if
    # it cannot find <uhd/config.hpp> or "libuhd" ...

    set(UHD_ABI_VERSION_CONCISE ${PACKAGE_VERSION})

  endif(UHD_INCLUDE_DIR)

  # check for ABI compatibility, both:
  #   ACTUAL VERSION >= DESIRED VERSION >= ABI VERSION

  if(NOT ${PACKAGE_FIND_VERSION} VERSION_LESS ${UHD_ABI_VERSION_CONCISE} AND
     NOT ${PACKAGE_FIND_VERSION} VERSION_GREATER ${PACKAGE_VERSION})
    set(PACKAGE_VERSION_COMPATIBLE TRUE)
  endif()

else(UHD_USE_ABI)

  # use API only, and assume compatible of requested <= actual
  # which is the same as "not >"

  if(NOT ${PACKAGE_FIND_VERSION} VERSION_GREATER ${PACKAGE_VERSION})
    set(PACKAGE_VERSION_COMPATIBLE TRUE)
  endif()

endif(UHD_USE_ABI)

# check for exact version

if(${PACKAGE_FIND_VERSION} VERSION_EQUAL ${PACKAGE_VERSION})
  set(PACKAGE_VERSION_EXACT TRUE)
endif()

# Undo our patch-version-number hack
set(PACKAGE_VERSION 3.15.0.main-0-33359f8a)
