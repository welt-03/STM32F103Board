cmake_minimum_required(VERSION 3.22)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/hal/u8g2 UI_HAL)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/hal UI_HAL)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${UI_HAL})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hal/u8g2)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hal)
