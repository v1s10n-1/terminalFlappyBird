find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(main
    flappyBird.cc
    )

target_link_libraries(main ${CURSES_LIBRARIES})
