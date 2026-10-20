cmake_minimum_required(VERSION 3.22)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Src CODE_SRC)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${CODE_SRC})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)