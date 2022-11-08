cmake_minimum_required(VERSION 3.23)
project(ece_city_2_f C)

set(CMAKE_C_STANDARD 11)

add_executable(ece_city_2_f
        main.c)

cmake_minimum_required(VERSION 3.23)
project(grille2 C)

set(CMAKE_C_STANDARD 99)
add_executable(grille2 main.c)


INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.8.0_2/include)
LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.8.0_2/lib)
file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.8.0_2/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")
TARGET_LINK_LIBRARIES(grille2 ${LIBRARIES})

