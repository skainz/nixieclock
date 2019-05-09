cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#find_package(Qt5 REQUIRED Core Widgets Xml X11Extras)
#add_definitions(-std=c++11)
add_executable(nclock
  nclock.c )

target_link_libraries(nclock
   X11 Xpm
  )

