#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#ifndef UNICODE
#define UNICODE
#endif

#include <dxgi1_3.h>
#include <d3d11_4.h>

#include <memory>

#include "framework_entry.h"
#include "framework_window.h"
#include "window.h"
#include "device_resources.h"
#include "renderer.h"

#include "logging.hpp"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	logging::_logging::add_file<logging::LoguruLogger>("example.log");
	log(logging::Level::info) << "dziala";

	/*auto window = std::make_shared<BasicWindow<FrameworkWindow>>("D3D11 Framework", "dev");
	if (!window->create(640, 480))
	{
		return 0;
	}
	ShowWindow(window->get_window_id(), nCmdShow);

	auto device_resources = make_device_resources<DeviceResources, BasicWindow<FrameworkWindow>>(window);
	auto renderer = make_renderer<Renderer, DeviceResources>(device_resources);

	Framework<DeviceResources, Renderer, BasicWindow<FrameworkWindow>> framework(device_resources, renderer, window);
	framework.run();*/

	return 0;
}
