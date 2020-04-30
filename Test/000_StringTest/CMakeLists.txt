set(TARGET_NAME 000_StringTest)

file(GLOB_RECURSE SOURCES *.cpp)

message(STATUS "TARGET- " ${TARGET_NAME})
foreach(SOURCE IN LISTS SOURCES)
	message(STATUS "SOURCE- " ${SOURCE})
endforeach(SOURCE)

add_executable(${TARGET_NAME} ${SOURCES} "CStrSafeTest.cpp")
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} WORKING_DIRECTORY ${OUTPUT_DIRECTORY})

# Project options
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
target_link_libraries(${TARGET_NAME} 
    ${DEFAULT_LINKER_OPTIONS} gtest_main gtest 000_String
)
