#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <wrl.h>

#include <dxgi1_3.h>
#include <d3d11_4.h>

#include <vector>


namespace dx
{
	namespace graphics_interface
	{
		template <typename T, typename U>
		using EnableIfTypesAreTheSame = std::enable_if_t<std::is_same_v<T, U>>;

		template <typename FactoryType>
		using EnableIfDXGIFactory2 = EnableIfTypesAreTheSame<FactoryType, IDXGIFactory2>;

		template <typename AdapterType>
		using EnableIfDXGIAdapter = EnableIfTypesAreTheSame<AdapterType, IDXGIAdapter>;

		template <typename DXGIDeviceType>
		using EnableIfDXGIDevice2 = EnableIfTypesAreTheSame<DXGIDeviceType, IDXGIDevice2>;

		template <typename D3D11DeviceType>
		using EnableIfD3D11Device = EnableIfTypesAreTheSame<D3D11DeviceType, ID3D11Device>;

		template <typename DXGISwapChain>
		using EnableIfDXGISwapChain = EnableIfTypesAreTheSame<DXGISwapChain, IDXGISwapChain1>;


		template<typename FactoryType, typename = EnableIfDXGIFactory2<FactoryType>>
		Microsoft::WRL::ComPtr<FactoryType> make_factory()
		{
			Microsoft::WRL::ComPtr<FactoryType> factory;
			auto hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, __uuidof(FactoryType), (void**)(&factory));

			return factory;
		}

		template<typename FactoryType, typename AdapterType, typename = EnableIfDXGIFactory2<FactoryType>, typename = EnableIfDXGIAdapter<AdapterType>>
		std::vector<Microsoft::WRL::ComPtr<AdapterType>> make_adapters_list(Microsoft::WRL::ComPtr<FactoryType> factory)
		{
			int i = 0;
			Microsoft::WRL::ComPtr<AdapterType> adapter;
			std::vector<Microsoft::WRL::ComPtr<AdapterType>> adapters;
			DXGI_ADAPTER_DESC ada_desc;
			while (factory->EnumAdapters(i, adapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND)
			{
				auto x = adapter->GetDesc(&ada_desc);
				adapters.push_back(adapter);
				++i;
			}

			return adapters;
		}

		template <typename DXGIDevice, typename D3DDevice, typename = EnableIfDXGIDevice2<DXGIDevice>, typename = EnableIfD3D11Device<D3DDevice>>
		Microsoft::WRL::ComPtr<DXGIDevice> get_dxgi_device_from(Microsoft::WRL::ComPtr<D3DDevice> device)
		{
			Microsoft::WRL::ComPtr<DXGIDevice> dxgi_device;
			auto hr = device->QueryInterface(__uuidof(DXGIDevice), reinterpret_cast<void**>(dxgi_device.GetAddressOf()));

			return dxgi_device;
		}

		template <typename DXGISwapChain, typename DXGIDevice, typename DXGIFactory, 
				  typename = EnableIfDXGISwapChain<DXGISwapChain>,
				  typename = EnableIfDXGIDevice2<DXGIDevice>, 
				  typename = EnableIfDXGIFactory2<DXGIFactory>>
		Microsoft::WRL::ComPtr<DXGISwapChain>
			make_swapchain_for_win32_wnd(
				Microsoft::WRL::ComPtr<DXGIDevice> device,
				Microsoft::WRL::ComPtr<DXGIFactory> factory,
				HWND wnd_id, int width, int height)
		{
			DXGI_SWAP_CHAIN_DESC1 desc{ 0 };
			desc.Width = width;
			desc.Height = height;
			desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			desc.BufferCount = 2;
			desc.Scaling = DXGI_SCALING_STRETCH;
			desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
			desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
			desc.Flags = 0;

			Microsoft::WRL::ComPtr<DXGISwapChain> swapchain = nullptr;
			auto hr = factory->CreateSwapChainForHwnd(
				reinterpret_cast<IUnknown*>(device.Get()),
				wnd_id,
				&desc,
				nullptr,
				nullptr,
				&swapchain
			);

			return swapchain;
		}
	}
}