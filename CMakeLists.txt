cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(dreamchess++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#-----------------------
# DOCUMENTATION SECTION
#-----------------------
find_package(Doxygen)

option(BUILD_DOC "Build documentation" ${DOXYGEN_FOUND})

if(BUILD_DOC)
	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen not found!")
	endif()

	set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
	set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	message("Doxygen build started...")

	add_custom_target(
		doc ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
		VERBATIM
	)
endif()

#--------------
# MAIN SECTION
#--------------

set(SRC
	${PROJECT_SOURCE_DIR}/main.cpp
	${PROJECT_SOURCE_DIR}/src/Game.cpp
	${PROJECT_SOURCE_DIR}/src/History.cpp
	${PROJECT_SOURCE_DIR}/src/Board.cpp
	${PROJECT_SOURCE_DIR}/src/Piece.cpp
	${PROJECT_SOURCE_DIR}/src/Move.cpp
)

set(INC
	${PROJECT_SOURCE_DIR}/include/Board.hpp
	${PROJECT_SOURCE_DIR}/include/Game.hpp
	${PROJECT_SOURCE_DIR}/include/History.hpp
	${PROJECT_SOURCE_DIR}/include/Piece.hpp
	${PROJECT_SOURCE_DIR}/include/Move.hpp
)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(main_${PROJECT_NAME} ${INC} ${SRC})

target_include_directories(main_${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

#------------------
# CLEANING SECTION
#------------------

add_custom_target(clean_all
	COMMAND ${CMAKE_COMMAND} -E echo "Cleaning doc..."
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${PROJECT_SOURCE_DIR}/doc
	COMMAND ${CMAKE_COMMAND} -E echo "Cleaning bin..."
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${PROJECT_SOURCE_DIR}/bin/*
	COMMAND ${CMAKE_COMMAND} -E echo "Cleaning build..."
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${PROJECT_SOURCE_DIR}/build/*
	COMMAND ${CMAKE_COMMAND} -E echo "Done!"
)
