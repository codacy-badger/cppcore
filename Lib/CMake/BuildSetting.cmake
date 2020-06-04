function(exclude_from_list SOURCES_LIST EXPRESSION)
	file(GLOB_RECURSE EXCLUDE ${EXPRESSION})	
	if(EXCLUDE)
		list(REMOVE_ITEM ${SOURCES_LIST} ${EXCLUDE})
	endif()
	set(${SOURCES_LIST} ${${SOURCES_LIST}} PARENT_SCOPE)
endfunction(exclude_from_list)

function(include_to_list SOURCES_LIST EXPRESSION)
	file(GLOB_RECURSE INCLUDE ${EXPRESSION})	
	if(INCLUDE)
		list(APPEND ${SOURCES_LIST} ${INCLUDE})
	endif()
	set(${SOURCES_LIST} ${${SOURCES_LIST}} PARENT_SCOPE)
endfunction(include_to_list)

macro(set_build_directory OUTPUT_DIRECTORY)
	if(MSVC)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/x64Release)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/x64Release)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/x64Release)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/x64Debug)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/x64Debug)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/x64Debug)
		set(${OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR}/Build/x64${CMAKE_BUILD_TYPE})
	elseif(APPLE)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/x64MacOSRelease)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/x64MacOSRelease)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/x64MacOSRelease)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/x64MacOSDebug)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/x64MacOSDebug)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/x64MacOSDebug)
		set(${OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR}/Build/x64MacOS${CMAKE_BUILD_TYPE})
	else() #UNIX
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/x64Linux${CMAKE_BUILD_TYPE})
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/x64Linux${CMAKE_BUILD_TYPE})
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/x64Linux${CMAKE_BUILD_TYPE})
		set(${OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR}/Build/x64Linux${CMAKE_BUILD_TYPE})
	endif()
endmacro(set_build_directory)

macro(set_test_build_directory OUTPUT_DIRECTORY)
	if(MSVC)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/Test/x64Release)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/Test/x64Release)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/Test/x64Release)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/Test/x64Debug)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/Test/x64Debug)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/Test/x64Debug)
		set(${OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR}/Build/Test/x64${CMAKE_BUILD_TYPE})
	elseif(APPLE)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/Test/x64MacOSRelease)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/Test/x64MacOSRelease)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Build/Test/x64MacOSRelease)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/Test/x64MacOSDebug)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/Test/x64MacOSDebug)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Build/Test/x64MacOSDebug)
		set(${OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR}/Build/Test/x64MacOS${CMAKE_BUILD_TYPE})
	else() #UNIX
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/Test/x64Linux${CMAKE_BUILD_TYPE})
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/Test/x64Linux${CMAKE_BUILD_TYPE})
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Build/Test/x64Linux${CMAKE_BUILD_TYPE})
		set(${OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR}/Build/Test/x64Linux${CMAKE_BUILD_TYPE})
	endif()
endmacro(set_test_build_directory)