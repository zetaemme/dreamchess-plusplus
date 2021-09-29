cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(dreamchess++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#--------------
# MAIN SECTION
#--------------

set(SRC
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/src/Board.cpp
    ${PROJECT_SOURCE_DIR}/src/Game.cpp
    ${PROJECT_SOURCE_DIR}/src/History.cpp
    ${PROJECT_SOURCE_DIR}/src/Move.cpp
    ${PROJECT_SOURCE_DIR}/src/Piece.cpp
)

set(INC
    ${PROJECT_SOURCE_DIR}/include/Board.hpp
    ${PROJECT_SOURCE_DIR}/include/Game.hpp
    ${PROJECT_SOURCE_DIR}/include/History.hpp
    ${PROJECT_SOURCE_DIR}/include/Move.hpp
    ${PROJECT_SOURCE_DIR}/include/Piece.hpp
)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(${PROJECT_NAME} ${INC} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

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
find_package(Doxygen QUIET)

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