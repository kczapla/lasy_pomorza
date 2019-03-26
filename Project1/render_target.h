#pragma once

#include <wrl.h>

#include "swapchain.h"


namespace dx
{
	namespace graphics_pipeline
	{
		namespace render_target
		{
			template <typename DeviceType, typename DXGISwapchain, typename RenderTargetView>
			class Factory
			{
				Microsoft::WRL::ComPtr<DeviceType> _device{ nullptr };
				Microsoft::WRL::ComPtr<DXGISwapchain> _swapchain{ nullptr };

			public:
				Factory(Microsoft::WRL::ComPtr<DeviceType> device, Microsoft::WRL::ComPtr<DXGISwapchain> swapchain) : _device(device), _swapchain(swapchain) {};
				
				template <typename Resource, typename ResourceDescription>
				Microsoft::WRL::ComPtr<RenderTargetView> create(ResourceDescription desc);
			};

			template <typename DeviceType, typename DXGISwapchain, typename RenderTargetView>
			template<typename Resource, typename ResourceDescription>
			inline Microsoft::WRL::ComPtr<RenderTargetView> Factory<DeviceType, DXGISwapchain, RenderTargetView>::create(ResourceDescription desc)
			{
				auto back_buffer = dx::graphics_interface::get_back_buffer<DXGISwapchain, Resource>(_swapchain);
				Microsoft::WRL::ComPtr<RenderTargetView> render_target_view;
				auto hr = _device->CreateRenderTargetView(
					back_buffer.Get(),
					nullptr,
					render_target_view.GetAddressOf()
				);
				return render_target_view;
			}
		}
	}
}