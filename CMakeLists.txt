cmake_minimum_required(VERSION 3.0)
project(ExchangeSimulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SERVER_SOURCE_FILES
        server/src/main.cpp
        server/src/Master.cpp
        server/src/Worker.cpp
        server/src/MessageDispatcher.cpp
        server/src/OrderHandler.cpp
        server/src/SecurityStatusHandler.cpp
        server/src/ConnectionFactory.cpp
        server/src/OrderBook.cpp
        server/src/Config.cpp
        server/src/APIUtil.cpp
        server/src/Logger.cpp
        server/src/SecurityDefinitionHandler.cpp
        server/src/QuoteRequestHandler.cpp
        )

set(CLIENT_SOURCE_FILES
        client/user_main.cpp
        client/Client.cpp
        client/UserClient.cpp)

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

add_executable(testFix42 ${TEST_FIX42_SOURCE_FILES})
add_executable(server ${SERVER_SOURCE_FILES})
add_executable(client ${CLIENT_SOURCE_FILES})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_include_directories(fix42 PUBLIC fix4.2/include)
target_include_directories(server PUBLIC server/include fix4.2/)
target_include_directories(client PUBLIC fix4.2/)

target_link_libraries(testFix42 ${GTEST_BOTH_LIBRARIES} fix42)
target_link_libraries(server fix42 event_core mysqlcppconn)
target_link_libraries(client fix42)

add_test(testFix42 testFix42)