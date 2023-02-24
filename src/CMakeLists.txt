set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(main
    flappyBird.c
    )

target_link_libraries(main ${CURSES_LIBRARIES} Threads::Threads)
