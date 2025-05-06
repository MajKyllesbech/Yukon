cmake_minimum_required(VERSION 3.24)
project(Yukon C)

set(CMAKE_C_STANDARD 99)

include_directories("Machine Oriented programming/scr")

add_executable(Yukon
        "Machine Oriented programming/scr/main.c"
        "Machine Oriented programming/scr/deck.c"
        "Machine Oriented programming/scr/SD.c"

)
