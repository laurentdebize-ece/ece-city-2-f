cmake_minimum_required(VERSION 3.23)
project(ece_city_2_f C)

set(CMAKE_C_STANDARD 99)



add_executable(ece_city_2_f main.c menu.c menu.h routes.c routes.h)


IF(WIN32)
    target_link_libraries(ece_city_2_f -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.8.0_2/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.8.0_2/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.8.0_2/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(ece_city_2_f ${LIBRARIES})
ENDIF(WIN32)
