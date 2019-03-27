#pragma once

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <wrl.h>

#include <string>
#include <vector>

#include "error.h"


namespace dx
{
	namespace graphics_pipeline
	{
		namespace input_assembler
		{
			template <typename ElementDescriptionType>
			struct LayoutData
			{
				std::vector<ElementDescriptionType> input_elems_description;
				Microsoft::WRL::ComPtr<ID3DBlob> vertex_shader_code;
			};


			template <typename D3DDeviceType, typename D3DInputLayout, typename D3DInputLayoutData>
			class Factory
			{
				Microsoft::WRL::ComPtr<D3DDeviceType> _device{ nullptr };
			public:
				Factory(Microsoft::WRL::ComPtr<D3DDeviceType> device) : _device(device) {};
				Microsoft::WRL::ComPtr<D3DInputLayout> create(D3DInputLayoutData layout_data) const;
			};


			template <typename D3DDeviceType, typename D3DInputLayout, typename D3DInputLayoutData>
			inline Microsoft::WRL::ComPtr<D3DInputLayout> Factory<D3DDeviceType, D3DInputLayout, D3DInputLayoutData>::create(D3DInputLayoutData layout_data) const
			{
				Microsoft::WRL::ComPtr<D3DInputLayout> input_layout{ nullptr };
				auto hr = _device->CreateInputLayout(
					layout_data.input_elems_description.data(),
					layout_data.input_elems_description.size(),
					layout_data.vertex_shader_code->GetBufferPointer(),
					layout_data.vertex_shader_code->GetBufferSize(),
					input_layout.GetAddressOf()
				);
				windows_infrastructure::throw_if_failed(hr);
				return input_layout;
			}

			template <typename D3DDeviceType, typename D3DInputLayout, typename D3DInputElemDesc>
			using D3DFactory = Factory<D3DDeviceType, D3DInputLayout, LayoutData<D3DInputElemDesc>>;
		}
	}
}
