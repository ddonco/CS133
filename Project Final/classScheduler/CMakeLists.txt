cmake_minimum_required(VERSION 3.1.0)
project (sgl VERSION 2021.04.03 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# tell CMake to run moc when necessary
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

# as moc files are generated in the binary dir, tell CMake
# to always look for includes there:
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Configure flags for the C++ compiler
# (In general, many warnings/errors are enabled to tighten compile-time checking.
# A few overly pedantic/confusing errors are turned off to avoid confusion.)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(
	-g
	-Wall
	-Wextra
	-Werror=return-type
	-Werror=uninitialized
	-Wunused-parameter
	-Wmissing-field-initializers
	-Wno-old-style-cast
	-Wno-sign-compare
	-Wno-sign-conversion
)

# source / header files specific to this project
FILE(GLOB ProjectSources
	src/*.cpp
)

FILE(GLOB ProjectHeaders
	src/*.h
)

# resource files (images, input files, etc.) for this project
FILE(GLOB ProjectResources
	res/*
)

set(sgl_HDRS
	${ProjectHeaders}
)

set(sgl_SRCS
	${ProjectSources}
)


add_executable(ClassScheduler
	${sgl_SRCS}
)



# copy resource files from res/ folder over to the build destination folder
foreach(resFile ${ProjectResources})
	get_filename_component(resFileName ${resFile} NAME)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/${resFileName} ${CMAKE_CURRENT_BINARY_DIR}/${resFileName} COPYONLY)
endforeach()

target_include_directories(ClassScheduler
	PRIVATE
	src/
)


