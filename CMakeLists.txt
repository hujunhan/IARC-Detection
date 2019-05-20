cmake_minimum_required(VERSION 3.14)
project(IARC_Detection)

set(CMAKE_CXX_STANDARD 11)
set(OpenCV_DIR "C:\\Users\\hu\\PortableProgram\\OpenCV\\precomplied\\build")
find_package(OpenCV REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/testFaceDetection.cpp)
if ( MSVC )
    set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin )
    set_target_properties( ${PROJECT_NAME}  PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin )
    set_target_properties( ${PROJECT_NAME}  PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin )
endif ( MSVC )

target_link_libraries(IARC_Detection ${OpenCV_LIBS})