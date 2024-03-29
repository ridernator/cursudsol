cmake_minimum_required(VERSION 3.10)

project(cursudsol VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR src)
set(INC_DIR include)
set(RULES_DIR rules)

##################################################
# Main application                               #
##################################################
set(APPLICATION_NAME cursudsol)

add_executable(${APPLICATION_NAME} ${SRC_DIR}/Cell.cc
                                   ${SRC_DIR}/CurSudSol.cc
                                   ${SRC_DIR}/Drawer.cc
                                   ${SRC_DIR}/Grid.cc
                                   ${SRC_DIR}/NDLoop.cc
                                   ${SRC_DIR}/Order.cc
                                   ${SRC_DIR}/Solver.cc
                                   ${SRC_DIR}/Rule.cc
                                   ${SRC_DIR}/${RULES_DIR}/EmptyRule.cc
                                   ${SRC_DIR}/${RULES_DIR}/HiddenN.cc
                                   ${SRC_DIR}/${RULES_DIR}/HiddenSingle.cc
                                   ${SRC_DIR}/${RULES_DIR}/NakedN.cc
                                   ${SRC_DIR}/${RULES_DIR}/IntersectionRemoval.cc
                                   ${SRC_DIR}/${RULES_DIR}/NakedSingle.cc
                                   ${SRC_DIR}/${RULES_DIR}/XWing.cc)

target_include_directories(${APPLICATION_NAME} PUBLIC ${INC_DIR}
                                                      ${INC_DIR}/${RULES_DIR})

target_link_libraries(${APPLICATION_NAME} PUBLIC ncurses dl)

target_link_options(${APPLICATION_NAME} PUBLIC -rdynamic)

target_compile_options(${APPLICATION_NAME} PUBLIC -Wall
                                                  -Wextra
                                                  -pedantic
                                                  -Werror
                                                  -ggdb)
                                                  # -s -O3)

file(GLOB plugins "${CMAKE_CURRENT_SOURCE_DIR}/plugins/*")
foreach(plugin ${plugins})
    add_subdirectory(${plugin})
endforeach()
