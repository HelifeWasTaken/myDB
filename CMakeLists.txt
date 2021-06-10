cmake_minimum_required(VERSION 3.12)
project(myDB VERSION 0.0.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)
file(GLOB PROJECT_FILES
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/Json/Deserializer/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/Json/Value/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/Json/Parser/*.cpp"
	"${PROJECT_SOURCE_DIR}/main.cpp"
)

add_executable(myDB ${PROJECT_FILES})
