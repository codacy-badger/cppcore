
function(load_gtest)
	configure_file(${PROJECT_SOURCE_DIR}/Lib/CMake/CMakeLists.txt.in
				   ${PROJECT_SOURCE_DIR}/Lib/googletest-build/CMakeLists.txt)
	
	if (EXISTS ${PROJECT_SOURCE_DIR}/Lib/googletest-build/CMakeCache.txt)
		file(REMOVE ${PROJECT_SOURCE_DIR}/Lib/googletest-build/CMakeCache.txt)
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
					RESULT_VARIABLE   ERROR
					WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib/googletest-build)
	if(ERROR)
		message(FATAL_ERROR "Cmake step for googletest generation failed")
	endif()
	
	file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/Build)
	execute_process(COMMAND ${CMAKE_COMMAND} --build ${PROJECT_SOURCE_DIR}/Lib/googletest-build
					RESULT_VARIABLE   ERROR
					WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Build)
	if(ERROR)
		message(FATAL_ERROR "Cmake step for googletest build failed")
	endif()
	
	# Prevent GoogleTest from overriding our compiler/linker options
	# when building with Visual Studio
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	
	add_subdirectory(${PROJECT_SOURCE_DIR}/Lib/googletest
					${PROJECT_SOURCE_DIR}/Lib/googletest-build)
endfunction(load_gtest)
