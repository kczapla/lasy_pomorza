#include "framework_window.h"


void window_loop()
{
	MSG msg = {};
	while (PeekMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


LRESULT FrameworkWindow::handle_msg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
		return resize();
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


LRESULT FrameworkWindow::resize()
{
	return 0;
}


LRESULT CALLBACK window_proc_test(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}