##
 # @file CMakeLists.txt
 #
 # @brief CMake file for project directory
 #
 # @author Kishwar Kumar
 # Contact: kumar.kishwar@gmail.com
 # 
 # @date 04/03/2022
 #
 ##

cmake_minimum_required(VERSION 3.16.0)

list(APPEND EXTRA_COMPONENT_DIRS "src"
                                 "_core"
                                 "_crypt"
                                 "app")
                                
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(AI-Speak-System-ESP32-PC)