# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_FREEBSD "")
SET(CPACK_BINARY_IFW "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_PRODUCTBUILD "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_BUILD_SOURCE_DIRS "/root/uhd/host;/root/uhd/host/build")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMPONENTS_ALL "libraries;pythonapi;headers;utilities;examples;manual;doxygen;readme;images")
SET(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
SET(CPACK_COMPONENT_DOXYGEN_DESCRIPTION "API documentation (html)")
SET(CPACK_COMPONENT_DOXYGEN_DISPLAY_NAME "Doxygen")
SET(CPACK_COMPONENT_DOXYGEN_GROUP "Documentation")
SET(CPACK_COMPONENT_EXAMPLES_DEPENDS "libraries")
SET(CPACK_COMPONENT_EXAMPLES_DESCRIPTION "Example executables")
SET(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples")
SET(CPACK_COMPONENT_EXAMPLES_GROUP "Runtime")
SET(CPACK_COMPONENT_HEADERS_DESCRIPTION "C++ development headers")
SET(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")
SET(CPACK_COMPONENT_HEADERS_GROUP "Development")
SET(CPACK_COMPONENT_IMAGES_DESCRIPTION "FPGA and firmware images")
SET(CPACK_COMPONENT_IMAGES_DISPLAY_NAME "Images")
SET(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Dynamic link library")
SET(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
SET(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
SET(CPACK_COMPONENT_MANUAL_DESCRIPTION "Manual/application notes (rst and html)")
SET(CPACK_COMPONENT_MANUAL_DISPLAY_NAME "Manual")
SET(CPACK_COMPONENT_MANUAL_GROUP "Documentation")
SET(CPACK_COMPONENT_PYTHONAPI_DESCRIPTION "UHD Python API")
SET(CPACK_COMPONENT_PYTHONAPI_DISPLAY_NAME "UHD Python API")
SET(CPACK_COMPONENT_PYTHONAPI_GROUP "Development")
SET(CPACK_COMPONENT_README_DESCRIPTION "Readme files (txt)")
SET(CPACK_COMPONENT_README_DISPLAY_NAME "Readme")
SET(CPACK_COMPONENT_README_GROUP "Documentation")
SET(CPACK_COMPONENT_README_REQUIRED "TRUE")
SET(CPACK_COMPONENT_TESTS_DEPENDS "libraries")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_COMPONENT_UTILITIES_DEPENDS "libraries")
SET(CPACK_COMPONENT_UTILITIES_DESCRIPTION "Utility executables and python scripts")
SET(CPACK_COMPONENT_UTILITIES_DISPLAY_NAME "Utilities")
SET(CPACK_COMPONENT_UTILITIES_GROUP "Runtime")
SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "/root/uhd/host/build/debian/preinst;/root/uhd/host/build/debian/postinst;/root/uhd/host/build/debian/prerm;/root/uhd/host/build/debian/postrm")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-all-dev, python-requests")
SET(CPACK_DEBIAN_PACKAGE_RECOMMENDS "python, python-tk")
SET(CPACK_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_IGNORE_FILES "\\.git*;\\.swp$")
SET(CPACK_INSTALLED_DIRECTORIES "/root/uhd/host;/")
SET(CPACK_INSTALL_CMAKE_PROJECTS "")
SET(CPACK_INSTALL_PREFIX "/usr/local")
SET(CPACK_MODULE_PATH "/root/uhd/host/cmake/Modules")
SET(CPACK_NSIS_DISPLAY_NAME "UHD 3.15.0.main-0-ee6805b3")
SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
    WriteRegStr HKLM \"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment\" \"UHD_PKG_PATH\" \"$INSTDIR\"
")
SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
    DeleteRegValue HKLM \"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment\" \"UHD_PKG_PATH\"
")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_MODIFY_PATH "ON")
SET(CPACK_NSIS_PACKAGE_NAME "UHD 3.15.0.main-0-ee6805b3")
SET(CPACK_OUTPUT_CONFIG_FILE "/root/uhd/host/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_CONTACT "Ettus Research <support@ettus.com>")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.10/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Ettus Research - USRP Hardware Driver")
SET(CPACK_PACKAGE_FILE_NAME "uhd-3.15.0.main-0-ee6805b3")
SET(CPACK_PACKAGE_FILE_NAME "uhd-3.15.0.main-0-ee6805b3")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "UHD 3.15.0.main-0-ee6805b3")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "UHD 3.15.0.main-0-ee6805b3")
SET(CPACK_PACKAGE_NAME "UHD")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Ettus Research (National Instruments)")
SET(CPACK_PACKAGE_VERSION "3.15.0.main-0-ee6805b3")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_RESOURCE_FILE_LICENSE "/root/uhd/host/LICENSE")
SET(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.10/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "/root/uhd/host/README.md")
SET(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/share/man;/usr/share/man/man1;/usr/lib64/pkgconfig;/usr/lib64/cmake;/usr/lib64/python2.7;/usr/lib64/python2.7/site-packages")
SET(CPACK_RPM_PACKAGE_REQUIRES "boost-devel, python-requests")
SET(CPACK_RPM_PACKAGE_SOURCES "ON")
SET(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "/root/uhd/host/build/redhat/post_install")
SET(CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE "/root/uhd/host/build/redhat/post_uninstall")
SET(CPACK_RPM_PRE_INSTALL_SCRIPT_FILE "/root/uhd/host/build/redhat/pre_install")
SET(CPACK_RPM_PRE_UNINSTALL_SCRIPT_FILE "/root/uhd/host/build/redhat/pre_uninstall")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_SOURCE_IGNORE_FILES "\\.git*;\\.swp$")
SET(CPACK_SOURCE_INSTALLED_DIRECTORIES "/root/uhd/host;/")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/root/uhd/host/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "uhd-3.15.0.main-0-ee6805b3")
SET(CPACK_SOURCE_RPM "OFF")
SET(CPACK_SOURCE_TBZ2 "ON")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
SET(CPACK_SOURCE_TXZ "ON")
SET(CPACK_SOURCE_TZ "ON")
SET(CPACK_SOURCE_ZIP "OFF")
SET(CPACK_STRIP_FILES "")
SET(CPACK_SYSTEM_NAME "Linux")
SET(CPACK_TOPLEVEL_TAG "Linux-Source")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/root/uhd/host/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
