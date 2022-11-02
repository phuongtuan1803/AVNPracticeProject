cmake_minimum_required(VERSION 3.5)

project(serviceb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(serviceb main.cpp database.cpp ../ipc/shm/shmem.cpp )
add_executable(serviceb_mq_a main_mq_a_test.cpp database.cpp ../ipc/shm/shmem.cpp ./ipc/mq/mq.cpp)
add_executable(serviceb_mq_b main_mq_b_test.cpp database.cpp ../ipc/shm/shmem.cpp ./ipc/mq/mq.cpp)
add_executable(serviceb_mq_c main_mq_c_test.cpp database.cpp ../ipc/shm/shmem.cpp ./ipc/mq/mq.cpp)

add_library(servicebS SHARED
    ../ipc/shm/shmem.cpp
)

target_link_libraries(serviceb PRIVATE Threads::Threads)
target_link_libraries(serviceb PRIVATE rt)

install(TARGETS serviceb servicebS serviceb_mq_a serviceb_mq_b serviceb_mq_c
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
