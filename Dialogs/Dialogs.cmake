set(DIALOGS_LIB_NAME Dialogs)	

file(GLOB DIALOGS_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB DIALOGS_INCS  ${CMAKE_CURRENT_LIST_DIR}/src/*.h)
file(GLOB DIALOGS_GLOBAL_INCS  ${CMAKE_CURRENT_LIST_DIR}/../common_files/include/DialogsLib.h)


add_library(${DIALOGS_LIB_NAME} SHARED  ${DIALOGS_SOURCES} ${DIALOGS_INCS} ${DIALOGS_GLOBAL_INCS})

target_link_libraries(${DIALOGS_LIB_NAME} 		debug ${MU_LIB_DEBUG} 		optimized ${MU_LIB_RELEASE} 
												debug ${NATGUI_LIB_DEBUG}   optimized ${NATGUI_LIB_RELEASE}
												debug ${DP_LIB_DEBUG} 		optimized ${DP_LIB_RELEASE})


source_group("inc"            FILES ${DIALOGS_INCS}   )
source_group("inc_dll"        FILES ${DIALOGS_GLOBAL_INCS}   )
source_group("src"            FILES ${DIALOGS_SOURCES}	)

#MU_DEBUG, MU_RELEASE, MU_64BIT, MU_32BIT
addMUCompileDefinitions(${DIALOGS_LIB_NAME})
							
if (WIN32)
	target_compile_definitions(${DIALOGS_LIB_NAME} PUBLIC DIALOGS_LIB_EXPORTS MU_WINDOWS)
elseif(APPLE)                                             
	target_compile_definitions(${DIALOGS_LIB_NAME} PUBLIC DIALOGS_LIB_EXPORTS MU_MACOS)
else()                                                    
	target_compile_definitions(${DIALOGS_LIB_NAME} PUBLIC DIALOGS_LIB_EXPORTS MU_LINUX)
endif()

