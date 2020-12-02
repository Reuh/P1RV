cmake_minimum_required(VERSION 3.16)
project(P1RV)

set(CMAKE_CXX_STANDARD 14)

add_executable(P1RV main.cpp CubeRenderer.cpp GameObject.cpp Scene.cpp TestScene.cpp MeshRenderer.cpp ModelRenderer.cpp Shader.cpp)

target_link_libraries(P1RV sfml-graphics sfml-system sfml-window GLU assimp GLEW)
if (WIN32)
	target_link_libraries(P1RV opengl32)
    set_target_properties(P1RV PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
else()
	target_link_libraries(P1RV GL)
endif()
