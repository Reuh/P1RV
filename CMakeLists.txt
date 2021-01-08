cmake_minimum_required(VERSION 3.16)
project(P1RV)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES *.hpp *.cpp)
file(GLOB COMPONENTS component/*.hpp component/*.cpp)
file(GLOB SCENES scene/*.hpp scene/*.cpp)

add_executable(P1RV ${SOURCES} ${COMPONENTS} ${SCENES})

target_include_directories(P1RV PRIVATE .)

find_package(OpenGL REQUIRED)
target_link_libraries(P1RV OpenGL::GL)

find_package(GLEW REQUIRED)
target_link_libraries(P1RV GLEW::GLEW)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
target_link_libraries(P1RV sfml-graphics sfml-system sfml-window sfml-audio)

if(DEFINED ENV{GLM_DIR})
	set(GLM_DIR $ENV{GLM_DIR})
endif()
target_include_directories(P1RV PRIVATE ${GLM_DIR})

if(DEFINED ENV{ASSIMP_DIR})
	set(ASSIMP_DIR $ENV{ASSIMP_DIR})
endif()
if(DEFINED ENV{ASSIMP_LIB_DIR})
	set(ASSIMP_LIB_DIR $ENV{ASSIMP_LIB_DIR})
endif()
target_include_directories(P1RV PRIVATE ${ASSIMP_DIR}/include)
target_include_directories(P1RV PRIVATE ${ASSIMP_DIR}/build/include)
target_link_directories(P1RV PRIVATE ${ASSIMP_LIB_DIR})

if (WIN32)
	target_link_libraries(P1RV assimp-vc142-mtd)
else()
	target_link_libraries(P1RV assimp)
endif()
