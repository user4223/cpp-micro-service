project(micro.test)

aux_source_directory(source PROJECT_SOURCE)
file(GLOB PROJECT_INCLUDES "include/*.h")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${PROJECT_INCLUDES}) 
target_link_libraries(${PROJECT_NAME} 
	micro.api
	micro.common 
  micro.testsupport
	CONAN_PKG::gtest
)

add_test(NAME micro.test COMMAND micro.test --gtest_output=xml:micro.test.result.xml)
