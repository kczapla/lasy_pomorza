#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#ifndef UNICODE
#define UNICODE
#endif

#include <dxgi1_3.h>
#include <d3d11_4.h>

#include "graphics_interface.h"
#include "window.h"
#include "device.h"
#include "buffer.h"
#include "cube_model.h"
#include "shader.h"
#include "input_assembler.h"

#include <string>
#include <vector>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	std::string window_name = "learn to program win";
	std::string window_text = "ebebe";
	BasicWindow<DxSimpleWindow> win(window_name, window_text);

	auto width{ 640 }, height{ 480 };

	if (!win.create(width, height))
	{
		return 0;
	}

	ShowWindow(win.get_window_id(), nCmdShow);

	auto factory = dx::graphics_interface::make_factory<IDXGIFactory2>();
	auto adapters = dx::graphics_interface::make_adapters_list<IDXGIFactory2, IDXGIAdapter>(factory);
	auto adapter = adapters[0];

	auto[device, device_context] = dx::resources::make_device<ID3D11Device, ID3D11DeviceContext, IDXGIAdapter>(adapter);

	auto dxgi_device = dx::graphics_interface::get_dxgi_device_from<IDXGIDevice2, ID3D11Device>(device);
	auto swapchain = dx::graphics_interface::make_swapchain_for_win32_wnd<IDXGISwapChain1, IDXGIDevice2, IDXGIFactory2>(dxgi_device, factory, win.get_window_id(), width, height);

	struct vs_constant_buffer
	{
		float x = 4;
		float y = 5;
		float u = 6;
		float z = 7;
	};

	auto vcb_data = std::make_unique<vs_constant_buffer>();

	dx::resources::BufferProperties cbp;
	cbp.size = sizeof(vs_constant_buffer);
	cbp.usage = D3D11_USAGE_DYNAMIC;
	cbp.bind_flags = D3D11_BIND_CONSTANT_BUFFER;
	cbp.cpu_access_flags = D3D11_CPU_ACCESS_WRITE;
	cbp.misc_flags = 0;
	cbp.structure_byte_stride = 0;

	dx::resources::SubresourcesData<vs_constant_buffer> sdcb;
	sdcb.buffer_data = vcb_data.get();

	dx::resources::BufferFactory<ID3D11Device, dx::resources::BufferProperties, dx::resources::SubresourcesData<vs_constant_buffer>> const_buffer_factory(device);
	auto const_buffer = const_buffer_factory.make_buffer(cbp, sdcb);
	device_context->VSSetConstantBuffers(0, 1, const_buffer.GetAddressOf());

	auto cube_model = build_simeple_cube_model();

	auto shader_compiler = dx::shader::Compiler<ID3D11Device>(device);
	
	std::wstring vertex_shader_path = L"simple_vertex_shader.hlsl";
	auto vertex_shader_code = shader_compiler.compile(vertex_shader_path, "main", "vs_5_0");

	std::vector<dx::graphics_pipeline::input_assembler::D3D11ElementDescription> input_asm_elems_desc{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	dx::graphics_pipeline::input_assembler::D3D11LayoutData input_layout_data{
		input_asm_elems_desc,
		vertex_shader_code
	};

	dx::graphics_pipeline::input_assembler::D3D11Factory<ID3D11Device> input_asm_factory(device);
	auto input_layout = input_asm_factory.create(input_layout_data);
	device_context->IASetInputLayout(input_layout.Get());

	std::wstring pixel_shader_path = L"simple_pixel_shader.hlsl";
	auto pixel_shader_code = shader_compiler.compile(pixel_shader_path, "main", "ps_5_0");
	
	dx::shader::Factory<ID3D11Device> shader_factory(device);
	auto vertex_shader = shader_factory.create_vertex_shader(vertex_shader_code);
	device_context->VSSetShader(vertex_shader.Get(), nullptr, 0);
	auto pixel_shader = shader_factory.create_pixel_shader(pixel_shader_code);
	device_context->PSSetShader(pixel_shader.Get(), nullptr, 0);


	window_loop();

	return 0;
}
