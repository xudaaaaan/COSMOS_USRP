# CMakelist for Brian test. 

set(example_sources
    tx_waveforms_Brian.cpp
    rx_samples_to_file_Brian.cpp
)


#for each source: build an executable and install
foreach(example_source ${example_sources})
    get_filename_component(example_name ${example_source} NAME_WE)
    add_executable(${example_name} ${example_source})
    target_link_libraries(${example_name} uhd ${Boost_LIBRARIES})
    UHD_INSTALL(TARGETS ${example_name} RUNTIME DESTINATION ${PKG_LIB_DIR}/examples COMPONENT examples)
endforeach(example_source)



########################################################################
# ASCII Art DFT - requires curses, so this part is optional
########################################################################
find_package(Curses)

if(CURSES_FOUND)
    include_directories(${CURSES_INCLUDE_DIR})
    add_executable(rx_ascii_art_dft rx_ascii_art_dft.cpp)
    target_link_libraries(rx_ascii_art_dft uhd ${CURSES_LIBRARIES} ${Boost_LIBRARIES})
    UHD_INSTALL(TARGETS rx_ascii_art_dft RUNTIME DESTINATION ${PKG_LIB_DIR}/examples COMPONENT examples)

    add_executable(twinrx_freq_hopping twinrx_freq_hopping.cpp)
    target_link_libraries(twinrx_freq_hopping uhd ${CURSES_LIBRARIES} ${Boost_LIBRARIES})
    UHD_INSTALL(TARGETS twinrx_freq_hopping RUNTIME DESTINATION ${PKG_LIB_DIR}/examples COMPONENT examples)
endif(CURSES_FOUND)




if(ENABLE_PYTHON_API)
    add_subdirectory(python)
endif(ENABLE_PYTHON_API)