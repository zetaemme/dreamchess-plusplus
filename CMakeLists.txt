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
