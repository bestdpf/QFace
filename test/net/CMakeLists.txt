project(testnet CXX) 
set(NET_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/net)
include_directories(${NET_INCLUDE_DIR})

add_executable(server server.cpp)
target_link_libraries(server net)
add_executable(client client.cpp)
target_link_libraries(client net)
