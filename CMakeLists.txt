cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(dreamchess++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#--------------
# MAIN SECTION
#--------------
set(SRC
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

add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -Werror -g)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE dc++)

#-----------------------
# DOCUMENTATION SECTION
#-----------------------
find_package(Doxygen QUIET REQUIRED)

if (DOXYGEN_FOUND)
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
endif (DOXYGEN_FOUND)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
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
            test/piece_test.cpp)

    target_include_directories(dc++_test PRIVATE include)
    target_link_libraries(dc++_test PRIVATE gtest_main dc++)

    include(GoogleTest)

    gtest_discover_tests(dc++_test)

    set_target_properties(gmock gmock_main PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

    add_custom_target(build_and_test
            COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR} --target dc++_test
            COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR} --target test
            )

    #------------------
    # COVERAGE SECTION
    #------------------
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
    include(CodeCoverage)

    set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

    setup_target_for_coverage(
            coverage
            dc++_test
            coverage
    )

    #------------------
    # VALGRIND SECTION
    #------------------
    find_program(VALGRIND_EXE valgrind)

    if (VALGRIND_EXE)
        add_custom_target(valgrind
                COMMAND ${CMAKE_COMMAND} --build . --target ${PROJECT_NAME}
                COMMAND ${VALGRIND_EXE} --leak-check=full --show-leak-kinds=all
                --track-fds=yes --track-origins=yes ./${PROJECT_NAME}
                )
    endif ()
endif ()

#-----------------
# INSTALL SECTION
#-----------------
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

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
