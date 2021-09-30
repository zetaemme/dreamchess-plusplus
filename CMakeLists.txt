cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(dreamchess++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#--------------
# MAIN SECTION
#--------------

set(SRC
    main.cpp
    src/Board.cpp
    src/Game.cpp
    src/History.cpp
    src/Move.cpp
    src/Piece.cpp
)

set(INC
    include/Board.hpp
    include/Game.hpp
    include/History.hpp
    include/Move.hpp
    include/Piece.hpp
)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_library(${PROJECT_NAME} ${INC} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_main main.cpp)

target_link_libraries(${PROJECT_NAME}_main PRIVATE ${PROJECT_NAME})

#------------------
# CLEANING SECTION
#------------------

add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning doc..."
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${PROJECT_SOURCE_DIR}/doc
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning bin..."
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${PROJECT_SOURCE_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E echo "Done!"
)

#-----------------
# INSTALL SECTION
#-----------------

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#-----------------------
# DOCUMENTATION SECTION
#-----------------------
find_package(Doxygen QUIET REQUIRED)

if(DOXYGEN_FOUND)
    set(DOXYGEN_PROJECT_NAME "Dreamchess++")
    set(DOXYGEN_PROJECT_BRIEF "A porting of dreamchess in modern C++")
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc)

    doxygen_add_docs(
        doc
        ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include
        COMMENT "Generating documentation..."
    )
endif(DOXYGEN_FOUND)

#-----------------
# TESTING SECTION
#-----------------
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(dreamchess_test test/board_test.cpp)
target_include_directories(dreamchess_test PRIVATE include)

target_link_libraries(dreamchess_test PRIVATE gtest_main ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(dreamchess_test)