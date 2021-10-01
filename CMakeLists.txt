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

add_library(dc++ ${INC} ${SRC})
target_include_directories(dc++ PUBLIC include)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -g)

add_executable(dc++_main main.cpp)

target_link_libraries(dc++_main PRIVATE dc++)

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

install(TARGETS dc++ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

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

#------------------
# VALGRIND SECTION
#------------------
find_program(VALGRIND_EXE valgrind)

if(VALGRIND_EXE)
    add_custom_target(valgrind
        COMMAND ${CMAKE_COMMAND} -E echo "Running valgrind test..."
        COMMAND ${CMAKE_COMMAND} --build . --target dc++_main
        COMMAND ${VALGRIND_EXE} --leak-check=full --show-leak-kinds=all 
                --track-fds=yes --track-origins=yes ./dc++_main
        COMMAND ${CMAKE_COMMAND} -E echo "Done!"
    )
endif()

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

add_executable(dc++_test 
    test/game_test.cpp
    test/board_test.cpp
)

target_include_directories(dc++_test PRIVATE include)
target_link_libraries(dc++_test PRIVATE gtest_main dc++)

include(GoogleTest)
gtest_discover_tests(dc++_test)