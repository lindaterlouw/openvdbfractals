cmake_minimum_required (VERSION 2.8)

#Created by Linda Terlouw 
set(APPNAME "openvdbfractals")
project(${APPNAME})

#specify your local directory
set(LOCALDIR "/workdir/openvdbfractals/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LOCALDIR}/bin)

include_directories(	/workdir 
			/usr/include
			/opt/intel/tbb2017_20170412oss/include
		)	

message(STATUS "Using CMake version ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.")

set(TARGET_NAME ${APPNAME}) 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_executable(${APPNAME} src/main.cc)
target_link_libraries(${APPNAME} /workdir/openvdb/libopenvdb.so)
target_link_libraries(${APPNAME} /usr/local/lib/libHalf.so)
target_link_libraries(${APPNAME} /opt/intel/tbb2017_20170412oss/lib/intel64/gcc4.1/libtbb.so)
target_link_libraries(${APPNAME} /usr/lib64/libgflags.so)
