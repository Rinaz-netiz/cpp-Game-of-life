cmake_minimum_required(VERSION 3.29)
project(Game_life)

set(CMAKE_CXX_STANDARD 17)


#yaml
add_subdirectory(libs/yaml-cpp)
include_directories(${CMAKE_SOURCE_DIR}/libs/yaml-cpp/include)

# SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

add_executable(Game_life
        src/main.cpp src/Game.cpp src/Field.cpp src/Cell.cpp)

target_link_libraries(Game_life
        PUBLIC sfml-graphics-d sfml-window-d sfml-system-d
        PRIVATE
        yaml-cpp)

set(DLL_FILES
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-graphics-d-3.dll
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-window-d-3.dll
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-system-d-3.dll
)

foreach(DLL ${DLL_FILES})
    add_custom_command(TARGET Game_life POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL} $<TARGET_FILE_DIR:Game_life>
            COMMENT "Copying ${DLL} to output directory"
    )
endforeach()


add_custom_command(TARGET Game_life POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SFML_DIR}/bin $<TARGET_FILE_DIR:Game_life>)
