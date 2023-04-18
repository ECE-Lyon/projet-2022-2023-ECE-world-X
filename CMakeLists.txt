cmake_minimum_required(VERSION 3.24)
project(osu C)
set(CMAKE_C_STANDARD 11)

add_executable(osu main.c beatmap.c beatmap.h beatmap.c music.c music.h music.c music.c)
target_link_libraries(osu -lmingw32 -lallegro-5.0.10-monolith-md-debug)
