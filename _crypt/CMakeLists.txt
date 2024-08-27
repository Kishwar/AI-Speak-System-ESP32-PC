##
 # @file CMakeLists.txt
 #
 # @brief CMake file for _crypt directory
 #
 # @author Kishwar Kumar
 # Contact: kumar.kishwar@gmail.com
 # 
 # @date 04/03/2022
 #
 ##

cmake_minimum_required(VERSION 3.16.0)

idf_component_register(SRCS "SD.cpp"
                       INCLUDE_DIRS ""
                       REQUIRES mbedtls)
