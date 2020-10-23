cmake_minimum_required(VERSION 3.16)
project(P1RV)

set(CMAKE_CXX_STANDARD 14)

add_executable(P1RV main.cpp Component.h Renderer.h CubeRenderer.cpp GameObject.cpp GameObject.h CubeRenderer.h Scene.cpp Scene.h TestScene.cpp TestScene.h MeshRenderer.cpp MeshRenderer.h ModelRenderer.cpp ModelRenderer.h)

target_link_libraries(P1RV sfml-graphics sfml-system sfml-window GLU assimp GLEW)
if (WIN32)
	target_link_libraries(P1RV opengl32)
    set_target_properties(P1RV PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
else()
	target_link_libraries(P1RV GL)
endif()
