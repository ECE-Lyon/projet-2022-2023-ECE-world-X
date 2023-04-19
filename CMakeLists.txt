cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 99)

add_executable(PROJET main.c Snake/interface.c Snake/snake.c Snake/miam.h Snake/miam.c Snake/plateau.c Snake/plateau.h Snake/game.c)

IF(WIN32)
    target_link_libraries(PROJET -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.8.0_2/include)
LINK_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.8.0_2/lib)
file(GLOB LIBRARIES "/opt/homebrew/Cellar/allegro/5.2.8.0_2/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")
TARGET_LINK_LIBRARIES(PROJET ${LIBRARIES})
ENDIF(WIN32)