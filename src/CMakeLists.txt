########################################################################
# Build libraries and executables
########################################################################
# commodity libraries
# consider -fvisibility=hidden
# Proper object library type was only introduced with CMake 2.8.8
add_library(r_433 STATIC
    abuf.c
    am_analyze.c
    baseband.c
    bit_util.c
    bitbuffer.c
    compat_paths.c
    compat_time.c
    confparse.c
    data.c
    data_tag.c
    decoder_util.c
    fileformat.c
    http_server.c
    jsmn.c
    list.c
    logger.c
    mongoose.c
    optparse.c
    output_file.c
    output_influx.c
    output_log.c
    output_mqtt.c
    output_rtltcp.c
    output_trigger.c
    output_udp.c
    pulse_analyzer.c
    pulse_data.c
    pulse_detect.c
    pulse_detect_fsk.c
    pulse_slicer.c
    r_api.c
    r_util.c
    raw_output.c
    rfraw.c
    samp_grab.c
    sdr.c
    term_ctl.c
    write_sigrok.c
    devices/flex.c
    devices/random_switch.c
    devices/random_remote.c
)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
    # untouched upstream code, disable all warnings
    set_source_files_properties(mongoose.c PROPERTIES COMPILE_FLAGS "-w")
endif()

add_executable(rtl_433 rtl_433.c)
target_link_libraries(rtl_433 r_433)

# target_compile_definitions was only added with CMake 2.8.11
if(THREADS_HAVE_PTHREAD_ARG)
    set_target_properties(r_433 PROPERTIES COMPILE_OPTIONS "-pthread")
    set_target_properties(r_433 PROPERTIES INTERFACE_COMPILE_OPTIONS "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(rtl_433 "${CMAKE_THREAD_LIBS_INIT}")
endif()

if(MSVC)
    # needs CMake 3.1 but Windows builds should have that
    target_sources(rtl_433 PRIVATE getopt/getopt.c)
endif()

add_library(data data.c abuf.c)
target_link_libraries(data ${NET_LIBRARIES})

target_link_libraries(rtl_433
    ${SDR_LIBRARIES}
    ${NET_LIBRARIES}
)

set(INSTALL_TARGETS rtl_433)
if(UNIX)
target_link_libraries(rtl_433 m)
endif()

# Explicitly say that we want C99
set_target_properties(rtl_433 r_433 PROPERTIES C_STANDARD 99)

########################################################################
# Install built library files & utilities
########################################################################
install(TARGETS ${INSTALL_TARGETS}
    RUNTIME DESTINATION bin              # .dll file
)
