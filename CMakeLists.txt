CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(medicalxml)

include_directories(vendor/rapidxml)
include_directories(vendor/fsm)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_subdirectory(schemavalidator)