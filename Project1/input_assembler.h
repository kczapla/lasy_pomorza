#pragma once

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <wrl.h>

#include <string>
#include <vector>


namespace dx
{
	namespace graphics_pipeline
	{
		namespace input_assembler
		{
			template <typename ApiElementDescType, typename InputClassificationType>
			struct ElementDescription
			{
				std::string semantic_name;
				unsigned int semantic_index;
				DXGI_FORMAT  format;
				unsigned int input_slot;
				unsigned int aligned_byte_offset;
				InputClassificationType input_slot_class;
				unsigned int instance_data_step_rate;

				operator ApiElementDescType() const { return convert(); };
			private:
				ApiElementDescType convert() const;
			};

			
			template <typename ApiElementDescType, typename InputClassificationType>
			ApiElementDescType ElementDescription<ApiElementDescType, InputClassificationType>::convert() const
			{
				ApiElementDescType desc{
					semantic_name.c_str(),
					semantic_index,
					format,
					input_slot,
					aligned_byte_offset,
					input_slot_class,
					instance_data_step_rate
				};
				return desc;
			}
			

			template <typename ElementDescriptionType>
			struct LayoutData
			{
				std::vector<ElementDescriptionType> input_elems_description;
				Microsoft::WRL::ComPtr<ID3DBlob> vertex_shader_code;
			};


			template <typename DeviceType, typename LayoutType, typename LayoutDataType, typename ElementDescriptionType>
			class Factory
			{
				Microsoft::WRL::ComPtr<DeviceType> _device{ nullptr };
			public:
				Factory(Microsoft::WRL::ComPtr<DeviceType> device) : _device(device) {};
				Microsoft::WRL::ComPtr<LayoutType> create(LayoutDataType layout_data) const;
			};


			template<typename DeviceType, typename LayoutType, typename LayoutDataType, typename ElementDescriptionType>
			inline Microsoft::WRL::ComPtr<LayoutType> Factory<DeviceType, LayoutType, LayoutDataType, ElementDescriptionType>::create(LayoutDataType layout_data) const
			{
				std::vector<ElementDescriptionType> elems(layout_data.input_elems_description.begin(), layout_data.input_elems_description.end());
				Microsoft::WRL::ComPtr<LayoutType> input_layout{ nullptr };
				auto hr = _device->CreateInputLayout(
					elems.data(),
					elems.size(),
					layout_data.vertex_shader_code->GetBufferPointer(),
					layout_data.vertex_shader_code->GetBufferSize(),
					input_layout.GetAddressOf()
				);
				return input_layout;
			}
			
			using D3D11ElementDescription = ElementDescription<D3D11_INPUT_ELEMENT_DESC, D3D11_INPUT_CLASSIFICATION>;
			using D3D11LayoutData = LayoutData<D3D11ElementDescription>;

			template <typename DeviceType>
			using D3D11Factory = Factory<DeviceType, ID3D11InputLayout, D3D11LayoutData, D3D11_INPUT_ELEMENT_DESC>;
		}
	}
}
