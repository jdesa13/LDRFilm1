set(GUI_SRCS
    ${GREGAR_INCLUDE_DIR}/Gregar_v.01/gui.h gui.cpp)


SET(LIB_TYPE STATIC)

add_library(gui ${LIB_TYPE} ${GUI_SRCS})

include_directories(
	${GLFW_INCLUDE_DIR} 
	${GLAD_INCLUDE_DIR} 
	${NANOVG_INCLUDE_DIR} 
	${NANOGUI_INCLUDE_DIR}
	${GREGAR_INCLUDE_DIR} 
	)

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)

set(GUI_DEPENDENCIES glfw nanogui core)
ADD_DEPENDENCIES(gui ${GUI_DEPENDENCIES})

add_executable(GUI_TESTER unit_test_gui.cpp)


target_link_libraries(GUI_TESTER  gui ${GUI_DEPENDENCIES})
ADD_DEPENDENCIES(GUI_TESTER gui ${GUI_DEPENDENCIES})