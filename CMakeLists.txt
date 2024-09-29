cmake_minimum_required(VERSION 3.5)

project(ImGuiPI)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

include_directories(${CMAKE_SOURCE_DIR}/imgui)
include_directories(${CMAKE_SOURCE_DIR}/imgui/backends)
#include_directories(filter_lib/include)
#add_subdirectory(filter_lib)

add_executable(AproximacionesDePi 
    main.cpp 
    imgui/imgui.cpp 
    imgui/imgui_draw.cpp 
    imgui/imgui_demo.cpp 
    imgui/imgui_widgets.cpp 
    imgui/imgui_tables.cpp 
    imgui/backends/imgui_impl_glfw.cpp 
    imgui/backends/imgui_impl_opengl3.cpp
)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(AproximacionesDePi OpenGL::GL glfw )
