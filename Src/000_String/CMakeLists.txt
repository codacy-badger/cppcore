set(TARGET_NAME 000_String)

file(GLOB_RECURSE SOURCES *.cpp)
if(MSVC)
	exclude_from_list(SOURCES *_Mac.cpp)
	exclude_from_list(SOURCES *_Linux.cpp)
elseif(APPLE)
	exclude_from_list(SOURCES *_Win.cpp)
	exclude_from_list(SOURCES *_Linux.cpp)
	include_to_list(SOURCES *_Mac_Linux.cpp)
else()
	exclude_from_list(SOURCES *_Win.cpp)
	exclude_from_list(SOURCES *_Mac.cpp)
	include_to_list(SOURCES *_Linux_Mac.cpp)
endif()

message(STATUS "TARGET- " ${TARGET_NAME})
foreach(SOURCE IN LISTS SOURCES)
	message(STATUS "SOURCE- " ${SOURCE})
endforeach(SOURCE)
message(STATUS "OUTPUT- " ${OUTPUT_DIRECTORY})

add_library(${TARGET_NAME}A OBJECT ${SOURCES})
add_library(${TARGET_NAME}W OBJECT ${SOURCES})
add_library(${TARGET_NAME} STATIC $<TARGET_OBJECTS:${TARGET_NAME}A> $<TARGET_OBJECTS:${TARGET_NAME}W>)

set_target_properties(${TARGET_NAME}A
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)
target_compile_options(${TARGET_NAME}A
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)
target_compile_definitions(${TARGET_NAME}A
    PRIVATE
)

set_target_properties(${TARGET_NAME}W
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)
target_compile_options(${TARGET_NAME}W
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)
target_compile_definitions(${TARGET_NAME}W
    PRIVATE
    -DUNICODE
    -D_UNICODE
)

set_target_properties(${TARGET_NAME}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)
target_compile_options(${TARGET_NAME}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)
target_compile_definitions(${TARGET_NAME}
    PRIVATE
)