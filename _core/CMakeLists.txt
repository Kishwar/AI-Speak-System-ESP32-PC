##
 # @file CMakeLists.txt
 #
 # @brief CMake file for _core directory
 #
 # @author Kishwar Kumar
 # Contact: kumar.kishwar@gmail.com
 # 
 # @date 05/03/2022
 #
 ##

cmake_minimum_required(VERSION 3.16.0)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

set(INCLUDES "."
             "fs"
             "hal/flash"
             "hal/wifi")

idf_component_register(SRCS ${SOURCE_FILES}
                        INCLUDE_DIRS ${INCLUDES}
                        PRIV_REQUIRES fatfs spiffs nvs_flash)
