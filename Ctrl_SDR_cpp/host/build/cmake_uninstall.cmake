# http://www.vtk.org/Wiki/CMake_FAQ#Can_I_do_.22make_uninstall.22_with_CMake.3F

if(NOT EXISTS "/root/uhd/host/build/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/root/uhd/host/build/install_manifest.txt\"")
endif(NOT EXISTS "/root/uhd/host/build/install_manifest.txt")

file(READ "/root/uhd/host/build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if(EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif(NOT "${rm_retval}" STREQUAL 0)
  elseif(NOT "${CMAKE_VERSION}" STRLESS "2.8.1")
    if(IS_SYMLINK "$ENV{DESTDIR}${file}")
      exec_program(
        "/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
        OUTPUT_VARIABLE rm_out
        RETURN_VALUE rm_retval
        )
      if(NOT "${rm_retval}" STREQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
      endif(NOT "${rm_retval}" STREQUAL 0)
    endif(IS_SYMLINK "$ENV{DESTDIR}${file}")
  else(EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif(EXISTS "$ENV{DESTDIR}${file}")
endforeach(file)
