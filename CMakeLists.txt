cmake_minimum_required(VERSION 3.16)
project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(FindPkgConfig)
pkg_check_modules(CURL libcurl REQUIRED)
pkg_check_modules(JSONCPP jsoncpp REQUIRED)


file(GLOB SRC CONFIGURE_DEPENDS "inc/**/*.h" "src/**/*.cpp")

include_directories(
        SYSTEM ${CURL_INCLUDE_DIRS}
        SYSTEM ${JSONCPP_INCLUDE_DIRS}
)

# add_executable(app ${SRC})
add_executable(app ./src/app/main.cpp ./src/app/ui.cpp ./inc/app/app.h ./inc/app/config.h ./inc/app/ui.h ./inc/services/RandomService.h ./inc/utils/utils.h src/services/RandomService.cpp inc/services/ApiService.h src/services/ApiService.cpp)

add_subdirectory("./imgui-cmake/")

target_link_libraries(app IMGUI ${CURL_LIBRARIES} jsoncpp)
