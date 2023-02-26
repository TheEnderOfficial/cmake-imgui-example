cmake_minimum_required(VERSION 3.16)
project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(app src/main.cpp src/app/ui.cpp src/app/ui.h src/app/config.h src/app/app.h src/utils/utils.h src/utils/randint.cpp)

add_subdirectory("./imgui-cmake/")
target_link_libraries(app IMGUI)
