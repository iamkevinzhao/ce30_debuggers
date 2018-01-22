set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Network REQUIRED)

add_executable(
  ce30_testing_assistant
    main.cpp
    main_window.h
    main_window.cpp
    main_window.ui
    abstract_socket.h
    abstract_socket.cpp
    udp_socket.h
    udp_socket.cpp
    text_sender.h
    text_sender.cpp
    text_receiver.h
    text_receiver.cpp
)

target_link_libraries(
  ce30_testing_assistant
    Qt5::Widgets
    Qt5::Network
)

install(TARGETS ce30_testing_assistant
  RUNTIME DESTINATION bin)
