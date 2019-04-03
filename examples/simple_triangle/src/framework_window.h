#pragma once

#include "window.h"


class FrameworkWindow
{
	LRESULT resize();
public:
	LRESULT handle_msg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};