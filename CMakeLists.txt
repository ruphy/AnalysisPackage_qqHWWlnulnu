#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(AnalysisPackage_qqHWWlnulnu)

set(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/
    ${CMAKE_MODULE_PATH})

find_package(ROOT REQUIRED)

set(NTUPLE_DIR "${PROJECT_SOURCE_DIR}/../NtuplePackage/")
set(ADDITIONAL_LIBS TMVA GenVector Event)

include_directories(${ROOT_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/interface ${NTUPLE_DIR}/interface/)
link_directories("${NTUPLE_DIR}/lib")

file(GLOB sorgenti "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

set(LIB_ANALYSIS src/Variables.cc src/qqHWWlnulnuUtils.cc)
add_library(main_lib SHARED ${LIB_ANALYSIS})

foreach(file ${sorgenti})
  get_filename_component(exname ${file} NAME_WE)
  add_executable("${exname}.exe" ${file})
  target_link_libraries("${exname}.exe" ${ROOT_LIBRARIES} ${ADDITIONAL_LIBS} main_lib)
endforeach()

