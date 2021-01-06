cmake_minimum_required(VERSION 3.16)
project(P1RV)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.hpp *.cpp)
file(GLOB COMPONENTS component/*.hpp component/*.cpp)
file(GLOB SCENES scene/*.hpp scene/*.cpp)

add_executable(P1RV ${SOURCES} ${COMPONENTS} ${SCENES})

target_include_directories(P1RV PRIVATE .)

#target_link_libraries(P1RV debug sfml-graphics-d sfml-system-d sfml-window-d sfml-audio-d)
target_link_libraries(P1RV general sfml-graphics sfml-system sfml-window sfml-audio)

if (WIN32)
	target_include_directories(P1RV PRIVATE $ENV{SFML_DIR}/include)
	target_link_directories(P1RV PRIVATE $ENV{SFML_DIR}/lib)

	target_include_directories(P1RV PRIVATE $ENV{GLEW_INCLUDE_DIR})
	target_link_directories(P1RV PRIVATE $ENV{GLEW_LIB_DIR})

	target_include_directories(P1RV PRIVATE $ENV{GLM_DIR})

	target_include_directories(P1RV PRIVATE $ENV{ASSIMP_DIR}/include)
	target_include_directories(P1RV PRIVATE $ENV{ASSIMP_DIR}/build/include)
	target_link_directories(P1RV PRIVATE $ENV{ASSIMP_LIB_DIR})

	target_link_libraries(P1RV opengl32 glu32 glew32 assimp-vc142-mtd)
else()
	target_link_libraries(P1RV GL GLU GLEW assimp)
endif()
