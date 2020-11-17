cmake_minimum_required(VERSION 3.0.0)
project(unix-icp VERSION 0.1.0)

set(client_sources
    ## ENTRY POINT
    src/simple/client.cpp
    # src/interact/client.cpp
    # src/head-on/client.cpp
    ## FILES
    src/channel.cpp
    src/message.cpp
    src/channel.hpp
    src/message.hpp
)

set(server_sources
    ## ENTRY POINT
    src/simple/server.cpp
    # src/interact/server.cpp
    # src/head-on/server.cpp
    ## FILES
    src/channel.cpp
    src/message.cpp
    src/channel.hpp
    src/message.hpp
)

add_executable(Client ${client_sources})
add_executable(Server ${server_sources})

set_target_properties(
    Client Server
    PROPERTIES CXX_STANDARD 17
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
