cmake_minimum_required(VERSION 3.18)

set(SOLUTION_NAME LabGUI)	#Solution name

#BEGIN part for all solutions
project(${SOLUTION_NAME})
set(SOURCE_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(HOME_ROOT $ENV{HOME})
if (WIN32)
	string(REPLACE "\\" "/" HOME_ROOT "${HOME_ROOT}")
endif()
set(WORK_ROOT ${HOME_ROOT}/Work)
include(${WORK_ROOT}/DevEnv/Common.cmake) 
#END  part for all solutions

if (WIN32)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PoS)
endif()

include(${WORK_ROOT}/DevEnv/natGUI.cmake)
include(${WORK_ROOT}/DevEnv/DataProvider.cmake) 

include(Dialogs/Dialogs.cmake)
include(PoS/PoS.cmake)





