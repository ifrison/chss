add_library(file_utils INTERFACE)

target_include_directories(file_utils
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:file_utils>)
