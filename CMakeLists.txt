cmake_minimum_required(VERSION 3.10)
project(ADS)

set(CMAKE_CXX_STANDARD 11)

file(GLOB Praktikum_1a "Praktikum_1a/*.h" "Praktikum_1a/*.cpp")
add_executable(Praktikum_1a ${Praktikum_1a})

file(GLOB Praktikum_1b "Praktikum_1b/*.h" "Praktikum_1b/*.cpp")
add_executable(Praktikum_1b ${Praktikum_1b})

file(GLOB Praktikum_1c "Praktikum_1c/*.h" "Praktikum_1c/*.cpp")
add_executable(Praktikum_1c ${Praktikum_1c})

file(GLOB Praktikum_2a "Praktikum_2a/*.h" "Praktikum_2a/*.cpp")
add_executable(Praktikum_2a ${Praktikum_2a})

file(GLOB Praktikum_2b "Praktikum_2b/*.h" "Praktikum_2b/*.cpp")
add_executable(Praktikum_2b ${Praktikum_2b})
