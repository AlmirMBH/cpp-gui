set(POS_NAME PoS)				#Naziv prvog projekta u solution-u

file(GLOB POS_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB POS_INCS  ${CMAKE_CURRENT_LIST_DIR}/src/*.h)
set(POS_PLIST  ${CMAKE_CURRENT_LIST_DIR}/src/Info.plist)

# add executable
add_executable(${POS_NAME} ${POS_INCS} ${POS_SOURCES})

source_group("inc"            FILES ${POS_INCS})
source_group("src"            FILES ${POS_SOURCES})


target_link_libraries(${POS_NAME}	debug ${MU_LIB_DEBUG}   	optimized ${MU_LIB_RELEASE}
									debug ${NATGUI_LIB_DEBUG}   optimized ${NATGUI_LIB_RELEASE}
									debug ${DP_LIB_DEBUG} 		optimized ${DP_LIB_RELEASE}
									debug ${DIALOGS_LIB_NAME}   optimized ${DIALOGS_LIB_NAME})


setTargetPropertiesForGUIApp(${POS_NAME} ${POS_PLIST})
setIDEPropertiesForGUIExecutable(${POS_NAME} ${CMAKE_CURRENT_LIST_DIR})

setPlatformDLLPath(${POS_NAME})


#MU_DEBUG, MU_RELEASE, MU_64BIT, MU_32BIT
addMUCompileDefinitions(${POS_NAME})


