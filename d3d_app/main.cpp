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
#include "swapchain.h"
#include "render_target.h"

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

	dx::graphics_interface::SampleDescription<DXGI_SAMPLE_DESC> sd{ 1, 0 };
	dx::graphics_interface::SwapchainDesc<DXGI_SWAP_CHAIN_DESC1, DXGI_SAMPLE_DESC> scd{
		width,
		height,
		DXGI_FORMAT_B8G8R8A8_UNORM,
		false,
		sd,
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_STRETCH,
		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		DXGI_ALPHA_MODE_IGNORE,
		0,
	};

	auto swapchain = dx::graphics_interface::make_swapchain_for_win32_wnd<IDXGISwapChain1, IDXGIDevice2, IDXGIFactory2, dx::graphics_interface::SwapchainDesc<DXGI_SWAP_CHAIN_DESC1, DXGI_SAMPLE_DESC>>(dxgi_device, factory, win.get_window_id(), scd);

	auto cube_model = build_simeple_cube_model();

	auto shader_compiler = dx::shader::Compiler<ID3D11Device>(device);
	
	std::wstring vertex_shader_path = L"simple_vertex_shader.hlsl";
	auto vertex_shader_code = shader_compiler.compile(vertex_shader_path, "main", "vs_5_0");
	
	std::vector<dx::graphics_pipeline::input_assembler::D3D11ElementDescription> input_asm_elems_desc{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	dx::graphics_pipeline::input_assembler::D3D11LayoutData input_layout_data{
		input_asm_elems_desc,
		vertex_shader_code
	};

	dx::graphics_pipeline::input_assembler::D3D11Factory<ID3D11Device> input_asm_factory(device);
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	auto input_layout = input_asm_factory.create(input_layout_data);
	device_context->IASetInputLayout(input_layout.Get());

	dx::resources::BufferProperties vbp{
		triangle_vertcies.size() * sizeof(dx::VertexPostionColor<DirectX::XMFLOAT3>),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		0, 0
	};

	dx::resources::SubresourcesData<dx::VertexPostionColor<DirectX::XMFLOAT3>> vbsd{
		triangle_vertcies.data()
	};
	
	dx::resources::BufferFactory<ID3D11Device, dx::resources::BufferProperties, dx::resources::SubresourcesData<dx::VertexPostionColor<DirectX::XMFLOAT3>>> vertex_buffer_factory(device);
	auto vertex_buffer = vertex_buffer_factory.make_buffer(vbp, vbsd);
	UINT stride = sizeof(dx::VertexPostionColor<DirectX::XMFLOAT3>);
	UINT offset = 0;
	device_context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);

	std::wstring pixel_shader_path = L"simple_pixel_shader.hlsl";
	auto pixel_shader_code = shader_compiler.compile(pixel_shader_path, "main", "ps_5_0");
	
	dx::shader::Factory<ID3D11Device> shader_factory(device);
	auto vertex_shader = shader_factory.create_vertex_shader(vertex_shader_code);
	device_context->VSSetShader(vertex_shader.Get(), nullptr, 0);
	auto pixel_shader = shader_factory.create_pixel_shader(pixel_shader_code);
	device_context->PSSetShader(pixel_shader.Get(), nullptr, 0);

	auto back_buffer = dx::graphics_interface::get_back_buffer<IDXGISwapChain1, ID3D11Texture2D>(swapchain);
	D3D11_TEXTURE2D_DESC tex2d_desc;
	back_buffer->GetDesc(&tex2d_desc);

	D3D11_VIEWPORT view_port{
		0, 0, tex2d_desc.Width, tex2d_desc.Height, 0, 1,
	};
	device_context->RSSetViewports(1, &view_port);

	dx::graphics_pipeline::render_target::Factory<ID3D11Device, IDXGISwapChain1, ID3D11RenderTargetView> render_traget_view_factory(device, swapchain);
	auto render_target_view = render_traget_view_factory.create<ID3D11Texture2D, D3D11_TEXTURE2D_DESC>({ 0 });

	const float teal[] = { 0.098f, 0.439f, 0.439f, 1.000f };
	device_context->ClearRenderTargetView(render_target_view.Get(), teal);
	device_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), nullptr);
	device_context->Draw(3, 0);
	swapchain->Present(1, 0);

	window_loop();

	return 0;
}
