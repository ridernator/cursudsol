cmake_minimum_required(VERSION 3.10)

project(cursudsol VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ..)

set(SRC_DIR src)
set(INC_DIR include)
set(APPLICATION_INC_DIR ../../include)

##################################################
# Plugin                                         #
##################################################
set(PLUGIN_NAME CandidateRemoval)

add_library(${PLUGIN_NAME} MODULE ${SRC_DIR}/CandidateRemoval.cc)

target_include_directories(${PLUGIN_NAME} PUBLIC ${INC_DIR}
                                                 ${APPLICATION_INC_DIR})

target_compile_options(${PLUGIN_NAME} PUBLIC -Wall
                                             -Wextra
                                             -pedantic
                                             -Werror
                                             # -ggdb)
                                             -s -O3)
