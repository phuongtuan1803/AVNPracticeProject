cmake_minimum_required(VERSION 3.5)

project(serviceb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(serviceb main.cpp database.cpp ../ipc/shm/shmem.cpp )

add_library(servicebS SHARED
    ../ipc/shm/shmem.cpp
)

target_link_libraries(serviceb PRIVATE Threads::Threads)
target_link_libraries(serviceb PRIVATE rt)

install(TARGETS serviceb
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
