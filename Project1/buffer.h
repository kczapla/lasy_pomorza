#pragma once
#pragma comment(lib, "d3d11.lib")

#include <wrl.h>
#include <memory>

#include <type_traits>

#include <d3d11_4.h>

#include "error.h"


namespace dx
{
	namespace resources
	{
		template <typename DeviceType, typename BufferPropertiesType, typename SubresourcesDataType>
		class BufferFactory
		{
			Microsoft::WRL::ComPtr<DeviceType> _device_context{ nullptr };
		public:
			BufferFactory() = default;
			BufferFactory(Microsoft::WRL::ComPtr<DeviceType> device_context) : _device_context(device_context) {}
			Microsoft::WRL::ComPtr<ID3D11Buffer> make_buffer(BufferPropertiesType buffer_properties, SubresourcesDataType subresources_data);
		};


		template <typename DeviceType, typename BufferPropertiesType, typename SubresourcesDataType>
		Microsoft::WRL::ComPtr<ID3D11Buffer>
			BufferFactory<DeviceType, BufferPropertiesType, SubresourcesDataType>::make_buffer(BufferPropertiesType buffer_properties, SubresourcesDataType subresources_data)
		{
			Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{ nullptr };
			auto hr = _device_context->CreateBuffer(&buffer_properties, &subresources_data, buffer.GetAddressOf());
			windows_infrastructure::throw_if_failed(hr);

			return buffer;
		}
	}
}