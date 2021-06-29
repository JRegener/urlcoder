cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project("urlcoder" CXX C)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)
set_property (GLOBAL PROPERTY CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)

	option(ENABLE_STATIC_LINK "Собирать проект с флагом /MT" ON)
	mark_as_advanced(ENABLE_STATIC_LINK)
	if (ENABLE_STATIC_LINK STREQUAL ON)
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
		set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
		set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
	endif ()

else ()

	option(ENABLE_STATIC_LINK "Линковать библиотеки статически" ON)
	mark_as_advanced(ENABLE_STATIC_LINK)

endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (SRC_FILES
	src/urlencoder.h
	src/urldecoder.h
	src/urlcoder.cpp
)


add_executable (urlcoder "${SRC_FILES}")

