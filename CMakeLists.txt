cmake_minimum_required(VERSION 3.1)
project(ts3query)
set(CMAKE_CXX_STANDARD 11)
include(CTest)
set(${CTEST_MEMORYCHECK_COMMAND} "/usr/bin/valgrind")

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/base
    ${PROJECT_SOURCE_DIR}/communication
    ${PROJECT_SOURCE_DIR}/connection
    ${PROJECT_SOURCE_DIR}/connection/transport
    ${PROJECT_SOURCE_DIR}/error
)

set(ts3query_src
    "src/communication/TS3Command.cpp"
    "src/communication/TS3Response.cpp"
    "src/communication/TS3ResponseValue.cpp"
    "src/connection/TS3ServerConnection.cpp"
    "src/connection/transport/NetworkTools.cpp"
    "src/connection/transport/TelnetTransport.cpp"
    "src/connection/transport/TS3BaseTransport.cpp"
    "src/error/TS3Error.cpp"
    "src/error/TS3LogicError.cpp"
    "src/error/TS3TransportError.cpp"
)

set(ts3query_testsrc "test/gtest_main.cpp")

add_library(ts3query SHARED ${ts3query_src})
add_executable(ts3query_test ${ts3query_testsrc})

target_link_libraries(ts3query_test ts3query gtest pthread)

if (BUILD_TESTING)
    enable_testing()
    add_test(NAME ts3query_test COMMAND ts3query_test)
endif()

install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/"
    DESTINATION "include/libts3query"
    FILES_MATCHING PATTERN "*.hpp"
)
install(TARGETS ts3query DESTINATION lib)
