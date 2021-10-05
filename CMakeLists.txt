cmake_minimum_required(VERSION 3.1)
project(state_machine)

set(CMAKE_CXX_STANDARD 20)


# Define version
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)


include_directories(src)

set(THIRD_PARTY_LIB_DIR ${CMAKE_SOURCE_DIR}/third_party_libs)
set(GTEST_DIR ${THIRD_PARTY_LIB_DIR}/googletest)

add_subdirectory(${GTEST_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# ---------------------------
# Tests
# ---------------------------

enable_testing()
set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
add_executable( transmitters_test test/transmitters_test.cc )
add_test( transmitters_test transmitters_test)
target_link_libraries(transmitters_test gtest gtest_main gmock_main)
set_property(TARGET transmitters_test PROPERTY CXX_STANDARD 20)

add_executable( transitions_test test/transitions_test.cc )
add_test( transitions_test transitions_test)
target_link_libraries(transitions_test gtest gtest_main gmock_main)
set_property(TARGET transitions_test PROPERTY CXX_STANDARD 20)

add_executable( states_test test/states_test.cc )
add_test( states_test states_test)
target_link_libraries(states_test gtest gtest_main gmock_main)
set_property(TARGET states_test PROPERTY CXX_STANDARD 20)
