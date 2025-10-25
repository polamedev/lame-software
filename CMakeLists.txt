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


# Добавление суфикса в имя дебажной библиотеки, нужно чтобы установить различия в названии. Возможно от этого стоит отказаться
set(CMAKE_DEBUG_POSTFIX d)


############## НАСТРОЙКА БИБЛИОТЕКИ ########################

# Добавление библиотеки
add_library(lame-software)

# Добавляем alias для библиотеки, полезно для избежания конфликта имен
add_library(lame::software ALIAS lame-software)

# VERSION - Устанавливаем версию библиотеки из версии проекта
# SOVERSION - Версия совместимости - определяет версию API стоит изменять, когда меняется API, поведение или используемый интерфейс
set_target_properties(
    lame-software
    PROPERTIES VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_include_directories(lame-software
    # Пути включения доступные только библиотеке
    PRIVATE src include/lame

    # Пути включения доступные самой библиотеке и пользователям
    PUBLIC
    # Используется выражения генератора
    # При сборке BUILD_INTERFACE заменится на include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    # При установке INSTALL_INTERFACE заменится на католог включения при установки
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(lame-software PRIVATE src/Event.c)
