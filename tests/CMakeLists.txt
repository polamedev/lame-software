enable_language(C CXX)

# Используется фреймворк CppUTest для тестирования
find_package(CppUTest REQUIRED)

# Подключение cmake CTest для тестирования, добавляет определение BUILD_TESTING
include(CTest)

add_executable(EventTest ${CMAKE_CURRENT_SOURCE_DIR}/EventTest.cpp)
target_link_libraries(EventTest lame::software CppUTest::CppUTest CppUTest::CppUTestExt)
add_test(EventTest EventTest)
