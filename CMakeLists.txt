cmake_minimum_required(VERSION 3.23)
project(ece_city_2_f C)

set(CMAKE_C_STANDARD 99)



add_executable(ece_city_2_f main.c menu.c menu.h routes.c routes.h menu.c menu.h maison.c maison.h chateauEau.c chateauEau.h usine.c usine.h TDG.c TDG.h)

target_link_libraries(ece_city_2_f -lmingw32 -lallegro-5.0.10-monolith-md-debug)
