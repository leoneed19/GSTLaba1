cmake_minimum_required(VERSION 3.13)
project(gstLaba_2 C)

set(CMAKE_C_STANDARD 11)
#set_target_properties( PROPERTIES LINK_FLAGS "-fopenmp")

#SET(MYCOMPILE_FLAGS "-fopenmp")
#add_definitions(${MYCOMPILE_FLAGS})
add_executable(gstLaba_2 main.c)
add_executable(gstLaba_2_g generator.c)

#set_target_properties(gstLaba_2 PROPERTIES LINK_FLAGS "-fopenmp")
#set_target_properties(gstLaba_2 PROPERTIES LINK_FLAGS_DEBUG "-fopenmp")
#set_target_properties(gstLaba_2 PROPERTIES LINK_FLAGS_RELEASE "-fopenmp")