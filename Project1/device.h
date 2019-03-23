#pragma once
#pragma comment(lib, "d3d11.lib")

#include <Windows.h>
#include <wrl.h>

#include <d3d11_4.h>

#include <utility>


namespace dx
{
	namespace resources
	{
		template<
			typename D3DDevice,
			typename D3DDeviceContext,
			typename DXGIAdapter>
			std::pair<
			Microsoft::WRL::ComPtr<D3DDevice>,
			Microsoft::WRL::ComPtr<D3DDeviceContext>>
			make_device(Microsoft::WRL::ComPtr<DXGIAdapter> adapter);


		template<
			typename D3DDevice,
			typename D3DDeviceContext,
			typename DXGIAdapter>
			std::pair<
			Microsoft::WRL::ComPtr<D3DDevice>,
			Microsoft::WRL::ComPtr<D3DDeviceContext>>
			make_device(Microsoft::WRL::ComPtr<DXGIAdapter> adapter)
		{
			D3D_FEATURE_LEVEL features[] = {
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1,
			};

			Microsoft::WRL::ComPtr<D3DDevice> device = nullptr;
			Microsoft::WRL::ComPtr<D3DDeviceContext> device_context = nullptr;
			D3D_FEATURE_LEVEL current_feature_level;
			auto hr = D3D11CreateDevice(
				adapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
				features,
				std::size(features),
				D3D11_SDK_VERSION,
				&device,
				&current_feature_level,
				&device_context
			);
			return std::make_pair(device, device_context);
		}
	}
}