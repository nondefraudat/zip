cmake_minimum_required(VERSION 3.13)

set(TEST_EXECUTABLE tests)
set(EXEC_MAIN_SRC testmain.cpp)

create_test_sourcelist(TEST_SRC_LIST
		${EXEC_MAIN_SRC}
		correctEntryDataReading.cpp
		correctEntryNamesReading.cpp)

add_executable(${TEST_EXECUTABLE} ${TEST_SRC_LIST})

set_property(TARGET ${TEST_EXECUTABLE} PROPERTY CXX_STANDARD 20)

target_include_directories(${TEST_EXECUTABLE} PRIVATE ../src)
target_link_libraries(${TEST_EXECUTABLE} PRIVATE oozip)

set(TEST_SRC_LIST_TO_RUN ${TEST_SRC_LIST})
remove(TEST_SRC_LIST_TO_RUN ${EXEC_MAIN_SRC})

foreach(TEST_SRC ${TEST_SRC_LIST_TO_RUN})
	get_filename_component(METHOD_NAME ${TEST_SRC} NAME_WE)
	add_test(NAME ${METHOD_NAME} 
			COMMAND ${TEST_EXECUTABLE} ${METHOD_NAME} ${CMAKE_CURRENT_SOURCE_DIR})
endforeach() 