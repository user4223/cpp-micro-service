project(micro.service)

aux_source_directory(source PROJECT_SOURCE)
file(GLOB PROJECT_INCLUDES "include/*.h")
file(GLOB PROJECT_ETC "etc/*")

#set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${PROJECT_INCLUDES} ${PROJECT_ETC})
target_link_libraries(${PROJECT_NAME} 
   micro.api
   micro.common 
   micro.utility
#   dl
)
