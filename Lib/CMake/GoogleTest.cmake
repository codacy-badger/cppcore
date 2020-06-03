
function(load_gtest)
	set(GTEST_BUILD_DIR ${PROJECT_SOURCE_DIR}/Lib/googletest-build/${CMAKE_SYSTEM_NAME})
	configure_file(${PROJECT_SOURCE_DIR}/Lib/CMake/CMakeLists.txt.in
				   ${GTEST_BUILD_DIR}/CMakeLists.txt)
	
	if (EXISTS ${GTEST_BUILD_DIR}/CMakeCache.txt)
		file(REMOVE ${GTEST_BUILD_DIR}/CMakeCache.txt)
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
					RESULT_VARIABLE   ERROR
					WORKING_DIRECTORY ${GTEST_BUILD_DIR})
	if(ERROR)
		message(FATAL_ERROR "Cmake step for googletest generation failed")
	endif()
	
	file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/Build)
	execute_process(COMMAND ${CMAKE_COMMAND} --build ${GTEST_BUILD_DIR}
					RESULT_VARIABLE   ERROR
					WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Build)
	if(ERROR)
		message(FATAL_ERROR "Cmake step for googletest build failed")
	endif()
	
	# Prevent GoogleTest from overriding our compiler/linker options
	# when building with Visual Studio
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	
	add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/googletest/${CMAKE_SYSTEM_NAME})
	add_subdirectory(${GTEST_BUILD_DIR})

endfunction(load_gtest)
