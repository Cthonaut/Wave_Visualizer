cmake_minimum_required(VERSION 3.10)

project(Sonar_Sim VERSION 3.5)

find_package(X11 REQUIRED)
file(GLOB_RECURSE SRC_FILES_C ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c)
file(GLOB_RECURSE SRC_FILES_CPP ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)
file(GLOB_RECURSE SRC_IMGUI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui/*.cpp)

add_executable(Sonar_Sim ${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp ${SRC_FILES_C} ${SRC_FILES_CPP} ${SRC_IMGUI_FILES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

target_include_directories(Sonar_Sim
    PUBLIC
    ${CMAKE_SOURCE_DIR}/../include/imgui
    ${CMAKE_SOURCE_DIR}/../include
)


target_link_directories(Sonar_Sim PUBLIC ${CMAKE_SOURCE_DIR}/../src/glfw)

target_link_libraries(Sonar_Sim
    PUBLIC
    glfw3
    X11::X11
)