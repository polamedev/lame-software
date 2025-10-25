cmake_minimum_required(VERSION 3.22)

# Основные настройки проекта
project(
    lame-software
    VERSION 1.0.0
    DESCRIPTION
        "Lame software lib"
    LANGUAGES C
)

# set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_C_EXTENSIONS ON)

# Установка типа сборки
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Добавление библиотеки
add_library(lame-soft STATIC)
add_library(lame::soft ALIAS lame-soft)
target_include_directories(lame-soft PUBLIC include PRIVATE include/lame)
target_sources(lame-soft PRIVATE src/Event.c)
