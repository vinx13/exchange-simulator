cmake_minimum_required(VERSION 3.3)
project(ExchangeSimulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

set(SERVER_SOURCE_FILES
        server/src/main.cpp
        server/src/Master.cpp
        server/src/Worker.cpp
        server/src/MessageHandler.cpp
        server/src/ConnectionFactory.cpp
        server/src/OrderBook.cpp
        server/src/Config.cpp
        server/src/APIUtil.cpp
        )

set(FIX42_SOURCE_FILES
        fix4.2/src/FieldValue.cpp
        fix4.2/src/Message.cpp
        fix4.2/src/RepeatGroup.cpp
        fix4.2/src/MessageParser.cpp
        fix4.2/src/FieldTypeMap.cpp
        )

set(TEST_FIX42_SOURCE_FILES
        fix4.2/test/test_FieldValue.cpp
        fix4.2/test/test_FieldGroup.cpp
        fix4.2/test/test_RepeatGroup.cpp
        fix4.2/test/test_Message.cpp
        fix4.2/test/test_MessageParser.cpp
        )


add_library(fix42 ${FIX42_SOURCE_FILES})
add_library(gtestmain gtest/src/gtest_main.cc)
add_library(gtest gtest/src/gtest-all.cc)

add_executable(testFix42 ${TEST_FIX42_SOURCE_FILES})
add_executable(server ${SERVER_SOURCE_FILES})

target_include_directories(fix42 PUBLIC fix4.2/include)
target_include_directories(gtest PUBLIC gtest/include PUBLIC gtest)
target_include_directories(gtestmain PUBLIC gtest/include PUBLIC gtest)
target_include_directories(testFix42 PUBLIC fix4.2 PUBLIC gtest/include)
target_include_directories(server PUBLIC fix4.2/)

target_link_libraries(testFix42 gtestmain gtest fix42)
target_link_libraries(server fix42 libevent_core.a mysqlcppconn.a)
