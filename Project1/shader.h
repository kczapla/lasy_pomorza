#pragma once
#pragma comment(lib, "d3dcompiler.lib")

#include <d3dcompiler.h>
#include <wrl.h>

#include <string>


namespace dx
{
	namespace shader
	{
		template <typename Device>
		class Compiler
		{
			Microsoft::WRL::ComPtr<Device> _device{ nullptr };
		public:
			Compiler(Microsoft::WRL::ComPtr<Device> device) : _device(device) {};

			Microsoft::WRL::ComPtr<ID3DBlob> compile(std::wstring shader_path, std::string entry_point, std::string target);
		};

		template<typename Device>
		inline Microsoft::WRL::ComPtr<ID3DBlob> Compiler<Device>::compile(std::wstring shader_path, std::string entry_point, std::string target)
		{
			UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
			flags |= D3DCOMPILE_DEBUG;
#endif

			const D3D_SHADER_MACRO defines[] =
			{
				"EXAMPLE_DEFINE", "1",
				nullptr, nullptr
			};


			Microsoft::WRL::ComPtr<ID3DBlob> compiled_code{ nullptr };
			Microsoft::WRL::ComPtr<ID3DBlob> compilation_errors{ nullptr };

			auto hr = D3DCompileFromFile(
				static_cast<LPCWSTR>(shader_path.c_str()),
				defines,
				nullptr,
				static_cast<LPCSTR>(entry_point.c_str()),
				static_cast<LPCSTR>(target.c_str()),
				flags,
				0,
				compiled_code.GetAddressOf(),
				compilation_errors.GetAddressOf()
			);

			if (FAILED(hr))
			{
				if (compilation_errors)
				{
					OutputDebugStringA(reinterpret_cast<char*>(compilation_errors->GetBufferPointer()));
				}
			}

			return compiled_code;
		}


		template<typename DeviceType>
		class Factory
		{
			Microsoft::WRL::ComPtr<DeviceType> _device{ nullptr };
		public:
			Factory(Microsoft::WRL::ComPtr<DeviceType> device) : _device(device) {};
			Microsoft::WRL::ComPtr<ID3D11PixelShader> create_pixel_shader(Microsoft::WRL::ComPtr<ID3DBlob> shader_code);
			Microsoft::WRL::ComPtr<ID3D11VertexShader> create_vertex_shader(Microsoft::WRL::ComPtr<ID3DBlob> shader_code);
		};

		template<typename DeviceType>
		inline Microsoft::WRL::ComPtr<ID3D11PixelShader> Factory<DeviceType>::create_pixel_shader(Microsoft::WRL::ComPtr<ID3DBlob> shader_code)
		{
			Microsoft::WRL::ComPtr<ID3D11PixelShader> shader{ nullptr };
			auto hr = _device->CreatePixelShader(
				shader_code->GetBufferPointer(),
				shader_code->GetBufferSize(),
				nullptr,
				shader.GetAddressOf()
			);
			return shader;
		}

		template<typename DeviceType>
		inline Microsoft::WRL::ComPtr<ID3D11VertexShader> Factory<DeviceType>::create_vertex_shader(Microsoft::WRL::ComPtr<ID3DBlob> shader_code)
		{
			Microsoft::WRL::ComPtr<ID3D11VertexShader> shader{ nullptr };
			auto hr = _device->CreateVertexShader(
				shader_code->GetBufferPointer(),
				shader_code->GetBufferSize(),
				nullptr,
				shader.GetAddressOf()
			);
			return shader;
		}
	}
}