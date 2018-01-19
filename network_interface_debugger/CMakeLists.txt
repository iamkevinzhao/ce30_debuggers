set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(
  ce30_testing_assistant
    main.cpp
    main_window.h
    main_window.cpp
    main_window.ui
)

target_link_libraries(
  ce30_testing_assistant
    Qt5::Widgets
)

install(TARGETS ce30_testing_assistant
  RUNTIME DESTINATION bin)
