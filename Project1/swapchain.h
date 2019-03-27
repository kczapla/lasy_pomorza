#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <wrl.h>

#include <dxgi1_3.h>
#include "graphics_interface.h"

#include "error.h"


namespace dx
{
	namespace graphics_interface
	{
		template<typename DXGISwapchain, typename BufferInterface>
		Microsoft::WRL::ComPtr<BufferInterface> get_back_buffer(Microsoft::WRL::ComPtr<DXGISwapchain> swapchain)
		{
			Microsoft::WRL::ComPtr<BufferInterface> buffer{ nullptr };
			swapchain->GetBuffer(
				0,
				__uuidof(BufferInterface),
				reinterpret_cast<void**>(buffer.GetAddressOf())
			);
			return buffer;
		}

		template <typename DXGISwapchain, typename DXGIDevice, typename DXGIFactory, typename SwapchainDescType,
			typename = EnableIfDXGISwapChain<DXGISwapchain>,
			typename = EnableIfDXGIDevice2<DXGIDevice>,
			typename = EnableIfDXGIFactory2<DXGIFactory>>
		Microsoft::WRL::ComPtr<DXGISwapchain> make_swapchain_for_win32_wnd(
			Microsoft::WRL::ComPtr<DXGIDevice> device,
			Microsoft::WRL::ComPtr<DXGIFactory> factory,
			HWND wnd_id, 
			SwapchainDescType swapchain_desc)
		{
			Microsoft::WRL::ComPtr<DXGISwapchain> dxgi_swapchain = nullptr;
			auto hr = factory->CreateSwapChainForHwnd(
				reinterpret_cast<IUnknown*>(device.Get()),
				wnd_id,
				&swapchain_desc,
				nullptr,
				nullptr,
				&dxgi_swapchain
			);
			windows_infrastructure::throw_if_failed(hr);
			return dxgi_swapchain;
		}
	}
}