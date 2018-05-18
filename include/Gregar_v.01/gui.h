#include "include/nanogui/opengl.h"
#include "include/nanogui/glutil.h"
#include "include/nanogui/screen.h"
#include "include/nanogui/window.h"
#include "include/nanogui/layout.h"
#include "include/nanogui/label.h"
#include "include/nanogui/checkbox.h"
#include "include/nanogui/button.h"
#include "include/nanogui/toolbutton.h"
#include "include/nanogui/popupbutton.h"
#include "include/nanogui/combobox.h"
#include "include/nanogui/progressbar.h"
#include "include/nanogui/entypo.h"
#include "include/nanogui/messagedialog.h"
#include "include/nanogui/textbox.h"
#include "include/nanogui/slider.h"
#include "include/nanogui/imagepanel.h"
#include "include/nanogui/imageview.h"
#include "include/nanogui/vscrollpanel.h"
#include "include/nanogui/colorwheel.h"
#include "include/nanogui/colorpicker.h"
#include "include/nanogui/graph.h"
#include "include/nanogui/tabwidget.h"
#include <iostream>
#include <string>

#pragma once
#ifndef _J_GUI
#define _J_GUI
class gui{
public:

	unsigned int mWidth, mHeight;

	gui();
	gui(int width, int height);
	~gui();
};
#endif