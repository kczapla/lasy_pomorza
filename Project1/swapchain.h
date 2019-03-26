#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <wrl.h>

#include <dxgi1_3.h>
//#include <d3d11_4.h>
#include "graphics_interface.h"


namespace dx
{
	namespace graphics_interface
	{
		template <typename SampleDescType>
		struct SampleDescription
		{
			unsigned int count{ 0 };
			unsigned int quality{ 0 };

			operator SampleDescType() const;
		};

		template <typename SampleDescType>
		inline SampleDescription<SampleDescType>::operator SampleDescType() const
		{
			SampleDescType desc{
				count, quality,
			};
			return desc;
		}


		template <typename SwapchainDescType, typename SampleDescType>
		struct SwapchainDesc
		{
			std::size_t width{ 0 };
			std::size_t height{ 0 };
			DXGI_FORMAT format{ 0 };
			bool stereo{ 0 };
			SampleDescType sample_desc{ 0 };
			DXGI_USAGE usage{ 0 };
			unsigned int buffer_count{ 0 };
			DXGI_SCALING scaling{ 0 };
			DXGI_SWAP_EFFECT swap_effect{ 0 };
			DXGI_ALPHA_MODE alpha_mode{ 0 };
			unsigned int flags{ 0 };

			SwapchainDescType convert() const;
		};


		template<typename SwapchainDescType, typename SampleDescType>
		inline SwapchainDescType SwapchainDesc<SwapchainDescType, SampleDescType>::convert() const
		{
			SwapchainDescType desc{
				width,
				height,
				format,
				stereo,
				sample_desc,
				usage,
				buffer_count,
				scaling,
				swap_effect,
				alpha_mode,
				flags,
			};
			return desc;
		}

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
			auto desc = swapchain_desc.convert();
			auto hr = factory->CreateSwapChainForHwnd(
				reinterpret_cast<IUnknown*>(device.Get()),
				wnd_id,
				&desc,
				nullptr,
				nullptr,
				&dxgi_swapchain
			);

			return dxgi_swapchain;
		}
	}
}