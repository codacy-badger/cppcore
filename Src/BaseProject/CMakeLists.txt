set(TARGET_NAME BaseProject)

file(GLOB_RECURSE SOURCES *.cpp)

message(STATUS "TARGET- " ${TARGET_NAME})
foreach(SOURCE IN LISTS SOURCES)
	message(STATUS "SOURCE- " ${SOURCE})
endforeach(SOURCE)
message(STATUS "OUTPUT- " ${OUTPUT_DIRECTORY})

add_executable(${TARGET_NAME} ${SOURCES})