cmake_minimum_required(VERSION 3.10)
project(passwordSafetyAnalyser)

set(CMAKE_CXX_STANDARD 17)

add_executable(pwrdSA 
	main.cpp
	password_utils.cpp
)

configure_file(${CMAKE_SOURCE_DIR}/Pwdb_top-10000000.txt 
		${CMAKE_BINARY_DIR}/Pwdb_top-10000000.txt
		COPYONLY)

