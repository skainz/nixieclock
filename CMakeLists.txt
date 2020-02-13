project(nixieclock)
cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(nclock
  nclock.c )

target_link_libraries(nclock
   X11 Xpm
  )

