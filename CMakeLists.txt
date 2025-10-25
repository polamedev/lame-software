cmake_minimum_required(VERSION 3.21)

# Основные настройки проекта
project(
    lame-software
    VERSION 1.0.0
    DESCRIPTION
        "Lame software lib"
    LANGUAGES C
)

# Определяем является ли текущий проектом верхнего уровня. Для fetch проектов, gitsubmodule или просто вложенных проектов это неверно
# string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)
# Но в новых версиях 3.21 можно использовать ${PROJECT_IS_TOP_LEVEL}

# -----------------------------------------------------------------------------------------------------------------------------------
# Настройка сборки библиотеки
# -----------------------------------------------------------------------------------------------------------------------------------

# Опции сборки
option(Lame_Software_BUILD_TESTS    "Build lame::software tests"         OFF)  # Нужно ли собирать тесты для библиотеки
# option(Lame_Software_BUILD_EXAMPLES "Build lame::software examples"      OFF)  # Нужно ли собирать примеры
# option(Lame_Software_BUILD_DOCS     "Build lame::software documentation" OFF)  # Нужно ли собирать документацию

# Установка типа сборки
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()


# Добавление суфикса в имя дебажной библиотеки, нужно чтобы установить различия в названии. Возможно от этого стоит отказаться
set(CMAKE_DEBUG_POSTFIX -dev)


# -----------------------------------------------------------------------------------------------------------------------------------
# Настройка таргета библиотеки
# -----------------------------------------------------------------------------------------------------------------------------------

# Добавление библиотеки
add_library(lame-software STATIC)

# Добавляем alias для библиотеки, полезно для избежания конфликта имен
add_library(lame::software ALIAS lame-software)

# VERSION - Устанавливаем версию библиотеки из версии проекта
# SOVERSION - Версия совместимости - определяет версию API стоит изменять, когда меняется API, поведение или используемый интерфейс
set_target_properties(
    lame-software
    PROPERTIES VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_sources(lame-software 
    PRIVATE 
    src/Event.c
    include/lame/Event.h
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

# -----------------------------------------------------------------------------------------------------------------------------------
# Добавление других таргетов
# -----------------------------------------------------------------------------------------------------------------------------------

if(Lame_Software_BUILD_TESTS)
    message(STATUS "Включено тестирование библиотеки")
    enable_testing()
    add_subdirectory(tests)
endif()
