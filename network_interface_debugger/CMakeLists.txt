set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Network REQUIRED)

add_executable(
  ce30_network_interface_debugger
    main.cpp
    main_window.h
    main_window.cpp
    main_window.ui
    abstract_socket.h
    abstract_socket.cpp
    async_network_server.h
    async_network_server.cpp
    udp_socket.h
    udp_socket.cpp
    tcp_socket.h
    tcp_socket.cpp
    text_sender.h
    text_sender.cpp
    text_receiver.h
    text_receiver.cpp
    text_display.h
    text_display.cpp
    incoming_packet_sampler.h
    incoming_packet_sampler.cpp
)

target_link_libraries(
  ce30_network_interface_debugger
    Qt5::Widgets
    Qt5::Network
)

install(TARGETS ce30_network_interface_debugger
  RUNTIME DESTINATION bin)
