cmake_minimum_required(VERSION 3.14)
project(FMOD-CMake-macOS)

set(CMAKE_CXX_STANDARD 17)

add_executable(
	FMOD-CMake-macOS
	main.cc
)

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../fmod/inc)


# target_link_libraries(${PROJECT_NAME} -L${PROJECT_SOURCE_DIR}/../fmod/lib/fmod -lfmod -lfmodL)
# При запуске программы выдаёт:
# dyld: Library not loaded: @rpath/libfmod.dylib
#   Referenced from: FMOD-Cmake/cmake-build-debug/FMOD-CMake
#   Reason: image not found

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../fmod/lib/fmod/libfmod.dylib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../fmod/lib/fmod/libfmodL.dylib)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/83538__zgump__bell-0101.wav
        ${CMAKE_CURRENT_BINARY_DIR}/83538__zgump__bell-0101.wav)
