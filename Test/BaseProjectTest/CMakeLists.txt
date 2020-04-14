set(TARGET_NAME BaseProjectTest)

file(GLOB_RECURSE SOURCES *.cpp)
include_to_list(SOURCES ${PROJECT_SOURCE_DIR}/Src/BaseProject/*.cpp)
exclude_from_list(SOURCES ${PROJECT_SOURCE_DIR}/Src/BaseProject/main.cpp)

message(STATUS "TARGET- " ${TARGET_NAME})
foreach(SOURCE IN LISTS SOURCES)
	message(STATUS "SOURCE- " ${SOURCE})
endforeach(SOURCE)

add_executable(${TARGET_NAME} ${SOURCES})
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} WORKING_DIRECTORY ${OUTPUT_DIRECTORY})

# Project options
set_target_properties(${TARGET_NAME}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        # /wd4996       # -> disable warning: non-Standard std::tr1 namespace and TR1-only machinery (because of gtest)		
        -Wno-unused-variable
        )
endif()
target_compile_options(${TARGET_NAME}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)
target_compile_definitions(${TARGET_NAME}
    PRIVATE
)

target_link_libraries(${TARGET_NAME} ${DEFAULT_LINKER_OPTIONS} gtest_main gtest)
