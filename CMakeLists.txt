cmake_minimum_required(VERSION 3.0.0)
project(high-on-speed VERSION 0.1.0)

add_link_options(-municode)

add_executable(high-on-speed src/main.c src/car.c src/entity.c src/matrix.c src/mesh.c src/vector.c)

target_link_libraries(high-on-speed -lGdi32 -lMsimg32)

