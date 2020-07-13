project(service.front)

aux_source_directory(source PROJECT_SOURCE)
file(GLOB PROJECT_INCLUDES "include/*.h")
file(GLOB PROJECT_ETC "etc/*")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${PROJECT_INCLUDES} ${PROJECT_ETC})
target_link_libraries(${PROJECT_NAME}  
   micro.utility
   CONAN_PKG::cpprestsdk
)

configure_file(etc/run.sh run.sh COPYONLY)
