include(CheckCXXCompilerFlag)

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(Azienda CXX)

CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
IF (COMPILER_SUPPORTS_CXX14)
	ADD_COMPILE_OPTIONS("-std=c++14")
ELSE()
	MESSAGE(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
ENDIF()

IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
	# "Debug" mode
	ADD_COMPILE_OPTIONS("-g")
	ADD_COMPILE_OPTIONS("-O1")
	IF (CMAKE_COMPILER_IS_GNUCXX)
		# if compiler is gcc
		ADD_COMPILE_OPTIONS("-ggdb3")
			ELSEIF (CMAKE_CXX_COMPILER_ID EQUAL "Clang") # if compiler is clang
			ADD_COMPILE_OPTIONS("-fsanitize=address")
			ADD_COMPILE_OPTIONS("-fno-omit-frame-pointer")
		ENDIF()
	ELSEIF (CMAKE_BUILD_TYPE STREQUAL "Release") # "Release" mode
	ADD_COMPILE_OPTIONS("-O2")
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

FILE(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)

ADD_EXECUTABLE(azienda ${SRCS})
target_compile_definitions(azienda PUBLIC -DINSTALLATION_ROOT_DIR=\"${CMAKE_BINARY_DIR}\")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)

ADD_EXECUTABLE(Test_Azienda test/test.cpp src/source.cpp)
target_compile_definitions(Test_Azienda PUBLIC -DINSTALLATION_ROOT_DIR=\"${CMAKE_BINARY_DIR}\")
ENABLE_TESTING()

ADD_TEST(NAME Test_Azienda
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
				COMMAND ./Test_Azienda)

ADD_CUSTOM_TARGET(doc COMMAND doxygen Doxyfile)
ADD_CUSTOM_TARGET(instal COMMAND mv azienda bin)
ADD_CUSTOM_TARGET(valgrind COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./bin/azienda)
ADD_CUSTOM_TARGET(analysis COMMAND cppcheck --enable=warning,performance,style,portability,information src/main.cpp src/source.cpp test/test.cpp include/header.hpp)
ADD_CUSTOM_TARGET(tidy COMMAND vera++ src/main.cpp src/source.cpp test/test.cpp include/header.hpp)
ADD_CUSTOM_TARGET(stats COMMAND cloc \"${CMAKE_BINARY_DIR}\")
ADD_CUSTOM_TARGET(cyclo COMMAND lizard \"${CMAKE_BINARY_DIR}\")
