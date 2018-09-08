FILE(GLOB_RECURSE MyLib_Sources "./*.cpp" "./*.c")

add_executable (ahmi ${MyLib_Sources})

target_include_directories (ahmi PUBLIC ../include)
target_include_directories (ahmi PUBLIC ../include/tnet)
add_definitions(-DHAS_SOCKLEN_T) # if we dont define this, under some linux distros it will not compile.