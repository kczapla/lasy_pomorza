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


		template <typename SwapchainType>
		class Swapchain
		{
			Microsoft::WRL::ComPtr<SwapchainType> _swapchain{ nullptr };

		public:
			Swapchain(Microsoft::WRL::ComPtr<SwapchainType> swapchain) : _swapchain(swapchain) {};

			template <typename BufferType>
			Microsoft::WRL::ComPtr<BufferType> get_buffer();

			void present(unsigned int sync_interval, unsigned int flags);
		};

		template<typename SwapchainType>
		template<typename BufferType>
		inline Microsoft::WRL::ComPtr<BufferType> Swapchain<SwapchainType>::get_buffer()
		{
			Microsoft::WRL::ComPtr<BufferType> buffer{ nullptr };
			_swapchain->GetBuffer(
				0,
				__uuidof(BufferType),
				reinterpret_cast<void**>(buffer.GetAddressOf())
			);
			return buffer;
		}

		template <typename DXGISwapChain, typename DXGIDevice, typename DXGIFactory, typename SwapchainDescType,
			typename = EnableIfDXGISwapChain<DXGISwapChain>,
			typename = EnableIfDXGIDevice2<DXGIDevice>,
			typename = EnableIfDXGIFactory2<DXGIFactory>>
		Swapchain<DXGISwapChain> make_swapchain_for_win32_wnd(
			Microsoft::WRL::ComPtr<DXGIDevice> device,
			Microsoft::WRL::ComPtr<DXGIFactory> factory,
			HWND wnd_id, 
			SwapchainDescType swapchain_desc)
		{
			Microsoft::WRL::ComPtr<DXGISwapChain> dxgi_swapchain = nullptr;
			auto desc = swapchain_desc.convert();
			auto hr = factory->CreateSwapChainForHwnd(
				reinterpret_cast<IUnknown*>(device.Get()),
				wnd_id,
				&desc,
				nullptr,
				nullptr,
				&dxgi_swapchain
			);

			Swapchain<DXGISwapChain> swapchain(dxgi_swapchain);
			return swapchain;
		}

		template<typename SwapchainType>
		inline void Swapchain<SwapchainType>::present(unsigned int sync_interval, unsigned int flags)
		{
			auto hr = _swapchain->Present(sync_interval, flags);
		}
}
}