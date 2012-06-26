cmake_minimum_required(VERSION 2.8)
project(sdl_and_tk_demo)

add_executable(sdl_and_tk_demo sdl_and_tk.c ball.c ballscreen.c tkwin.c)

find_package(TCL)
find_package(SDL)

include_directories(${TK_INCLUDE_PATH})
include_directories(${SDL_INCLUDE_DIR})

target_link_libraries(sdl_and_tk_demo ${SDL_LIBRARY} ${TCL_LIBRARY} ${TK_LIBRARY})
