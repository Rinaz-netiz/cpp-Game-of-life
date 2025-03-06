cmake_minimum_required(VERSION 3.29)
project(Game_life)

set(CMAKE_CXX_STANDARD 17)

# Устанавливаем мультиконфигурацию, если это поддерживается (например, в Visual Studio)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# yaml-cpp
add_subdirectory(libs/yaml-cpp)
include_directories(${CMAKE_SOURCE_DIR}/libs/yaml-cpp/include)

# SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

# Добавляем исполняемый файл
add_executable(Game_life
        src/main.cpp src/Game.cpp src/Field.cpp src/Cell.cpp)

# Линкуем библиотеки в зависимости от конфигурации
target_link_libraries(Game_life
        PRIVATE
        yaml-cpp
        $<$<CONFIG:Debug>:sfml-graphics-d sfml-window-d sfml-system-d>
        $<$<CONFIG:Release>:sfml-graphics sfml-window sfml-system>)

# Копируем DLL файлы в зависимости от конфигурации
set(DLL_FILES_DEBUG
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-graphics-d-3.dll
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-window-d-3.dll
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-system-d-3.dll
)

set(DLL_FILES_RELEASE
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-graphics-3.dll
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-window-3.dll
        ${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-system-3.dll
)

foreach(DLL ${DLL_FILES_DEBUG})
    add_custom_command(TARGET Game_life POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL} $<TARGET_FILE_DIR:Game_life>
            COMMENT "Copying ${DLL} to output directory"
    )
endforeach()

# Копируем DLL файлы для Debug
foreach(DLL ${DLL_FILES_DEBUG})
    add_custom_command(TARGET Game_life POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL} $<TARGET_FILE_DIR:Game_life>
            COMMENT "Copying ${DLL} to output directory"
    )
endforeach()

# Копируем DLL файлы для Release
foreach(DLL ${DLL_FILES_RELEASE})
    add_custom_command(TARGET Game_life POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL} $<TARGET_FILE_DIR:Game_life>
            COMMENT "Copying ${DLL} to output directory"
    )
endforeach()