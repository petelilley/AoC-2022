cmake_minimum_required(VERSION 3.1)

project(AoC-2022 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE COMMON_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp")
file(GLOB_RECURSE COMMON_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/common/*.hpp")
add_library(common STATIC ${COMMON_SOURCES})
target_include_directories(common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/common")
target_precompile_headers(common PUBLIC ${COMMON_HEADERS})

find_package(fmt CONFIG REQUIRED)
target_link_libraries(common PUBLIC fmt::fmt)

set(DAYS "")

file(GLOB CHILDREN RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*")
foreach(CHILD ${CHILDREN})
  if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${CHILD}")
    if("${CHILD}" MATCHES "^[0-9]+$")
      list(APPEND DAYS ${CHILD})
      message(STATUS "Found day ${CHILD}")
    endif()
  endif()
endforeach()

foreach(DAY ${DAYS})
  file(GLOB_RECURSE DAY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${DAY}/*.cpp")
  add_executable(${DAY} ${DAY_SOURCES})
  target_link_libraries(${DAY} common)
  target_precompile_headers(${DAY} REUSE_FROM common)
endforeach()