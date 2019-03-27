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
		struct BufferProperties
		{
			UINT size{ 0 };
			D3D11_USAGE usage;
			UINT bind_flags{ 0 };
			UINT cpu_access_flags{ 0 };
			UINT misc_flags{ 0 };
			UINT structure_byte_stride{ 0 };
		};


		template <typename DataType>
		struct SubresourcesData
		{
			DataType* buffer_data;
			UINT sys_mem_pitch{ 0 };
			UINT sys_mem_slice_pitch{ 0 };
		};


		template <typename DeviceType, typename BufferPropertiesType, typename SubresourcesDataType>
		class BufferFactory
		{
			Microsoft::WRL::ComPtr<DeviceType> _device_context{ nullptr };
		public:
			BufferFactory(Microsoft::WRL::ComPtr<DeviceType> device_context) : _device_context(device_context) {}
			Microsoft::WRL::ComPtr<ID3D11Buffer> make_buffer(BufferPropertiesType buffer_properties, SubresourcesDataType subresources_data);
		};


		template <typename DeviceType, typename BufferPropertiesType, typename SubresourcesDataType>
		Microsoft::WRL::ComPtr<ID3D11Buffer>
			BufferFactory<DeviceType, BufferPropertiesType, SubresourcesDataType>::make_buffer(BufferPropertiesType buffer_properties, SubresourcesDataType subresources_data)
		{
			D3D11_BUFFER_DESC buffer_desc;
			buffer_desc.ByteWidth = buffer_properties.size;
			buffer_desc.Usage = buffer_properties.usage;
			buffer_desc.BindFlags = buffer_properties.bind_flags;
			buffer_desc.CPUAccessFlags = buffer_properties.cpu_access_flags;
			buffer_desc.MiscFlags = buffer_properties.misc_flags;
			buffer_desc.StructureByteStride = buffer_properties.structure_byte_stride;

			D3D11_SUBRESOURCE_DATA init_data;
			init_data.pSysMem = subresources_data.buffer_data;
			init_data.SysMemPitch = subresources_data.sys_mem_pitch;
			init_data.SysMemSlicePitch = subresources_data.sys_mem_slice_pitch;

			Microsoft::WRL::ComPtr<ID3D11Buffer> buffer{ nullptr };
			auto hr = _device_context->CreateBuffer(&buffer_desc, &init_data, buffer.GetAddressOf());
			windows_infrastructure::throw_if_failed(hr);

			return buffer;
		}
	}
}