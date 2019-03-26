#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <string>
#include <iostream>

#include "error.h"


void window_loop(void);

LRESULT CALLBACK window_proc_test(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


template <typename WindowType>
class BasicWindow
{
	HWND window_id = 0;
	std::string window_name;
	std::string window_text;

	WindowType window_type;
	
public:
	BasicWindow() = delete;
	BasicWindow(std::string window_name, std::string window_text) 
		: window_name(window_name), window_text(window_text) {};
	bool create(int width, int height);
	auto get_window_id() { return window_id; }

	static LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


template <typename WindowType>
bool BasicWindow<WindowType>::create(int width, int height)
{
	auto tmp_name = std::wstring(window_name.begin(), window_name.end());
	auto class_name = static_cast<LPCWSTR>(tmp_name.c_str());

	auto tmp_window_text = std::wstring(window_text.begin(), window_text.end());
	auto window_text = static_cast<LPCWSTR>(tmp_window_text.c_str());

	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = BasicWindow<WindowType>::window_proc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = class_name;

	auto rc = RegisterClassEx(&wc);

	auto hwnd = CreateWindowEx(
		0,
		class_name,
		window_text,
		WS_OVERLAPPEDWINDOW,
		width, height, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		this
	);
	return (hwnd ? true : false);
}


template <typename WindowType>
LRESULT CALLBACK BasicWindow<WindowType>::window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BasicWindow<WindowType>* pThis = nullptr;
	if (uMsg == WM_CREATE) {
		auto create_struct = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<BasicWindow<WindowType>*>(create_struct->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

		pThis->window_id = hwnd;
	}
	else if (uMsg == WM_CLOSE) {
		PostQuitMessage(0);
		return 0;
	}
	else {
		pThis = reinterpret_cast<BasicWindow<WindowType>*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pThis) {
		return pThis->window_type.handle_msg(hwnd, uMsg, wParam, lParam);
	}
	else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}


class DxSimpleWindow
{
	LRESULT resize();
public:
	LRESULT handle_msg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};