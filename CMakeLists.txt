cmake_minimum_required(VERSION 3.17)
project(word-counter)

set(CMAKE_CXX_STANDARD 17)

if(NOT ANDROID_NDK)
    add_subdirectory(3rdparty)
    add_subdirectory(tests)
endif()

if(NOT DEFINED $ENV{CLION_IDE})
    add_subdirectory(user)
endif()
