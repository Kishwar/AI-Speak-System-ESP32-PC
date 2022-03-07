##
 # @file CMakeLists.txt
 #
 # @brief CMake file for interface directory
 #
 # @author Kishwar Kumar
 # Contact: kumar.kishwar@gmail.com
 # 
 # @date 05/03/2022
 #
 ##

file(GLOB_RECURSE SOURCE_FILES *.cpp)

set(INCLUDES "../_core")

idf_component_register(SRCS ${SOURCE_FILES}
                       INCLUDE_DIRS ${INCLUDES})
