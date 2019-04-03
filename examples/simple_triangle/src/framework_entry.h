#pragma once

#include <memory>

#include "renderer.h"
#include "error.h"


template <typename DeviceResources, typename Renderer, typename Window>
class Framework
{
	std::shared_ptr<DeviceResources> _device_resources{ nullptr };
	std::shared_ptr<Renderer> _renderer{ nullptr };
	std::shared_ptr<Window> _window{ nullptr };

public:
	Framework(std::shared_ptr<DeviceResources> device_resources, std::shared_ptr<Renderer> renderer, std::shared_ptr<Window> window)
		: _device_resources(device_resources), _renderer(renderer), _window(window) 
	{};

	void run();
};


template<typename DeviceResources, typename Renderer, typename Window>
inline void Framework<DeviceResources, Renderer, Window>::run()
{
	bool got_msg;
	MSG  msg;
	msg.message = WM_NULL;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		got_msg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		if (got_msg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			_renderer->update();
			_renderer->render();
			_renderer->present();
		}
	}
}
