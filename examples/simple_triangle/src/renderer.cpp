#include <directxmath.h>
#include "renderer.h"
#include "cube_model.h"
#include "vertex.h"


void Renderer::setup()
{
	auto device = _device_resources->get_device();
	_shader_compiler = dx::shader::Compiler<ID3D11Device>(device);
	_input_asm_factory = InputAsmFactory(device),
	_buffer_factory = BufferFactory(device);
	_shader_factory = dx::shader::Factory<ID3D11Device>(device);
}

void Renderer::create_resources()
{
	std::wstring vertex_shader_path = L"resources/shaders/simple_vertex_shader.hlsl";
	auto vertex_shader_code = _shader_compiler.compile(vertex_shader_path, "main", "vs_5_0");
	std::vector<D3D11_INPUT_ELEMENT_DESC> input_asm_elems_desc{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	dx::graphics_pipeline::input_assembler::LayoutData<D3D11_INPUT_ELEMENT_DESC> input_layout_data{
		input_asm_elems_desc,
		vertex_shader_code
	};

	auto device_context = _device_resources->get_device_context();
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	auto input_layout = _input_asm_factory.create(input_layout_data);
	device_context->IASetInputLayout(input_layout.Get());

	D3D11_BUFFER_DESC vbp{
		triangle_vertcies.size() * sizeof(dx::VertexPostionColor<DirectX::XMFLOAT3>),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		0, 0
	};
	
	D3D11_SUBRESOURCE_DATA vbsd{
		triangle_vertcies.data()
	};
	
	auto vertex_buffer = _buffer_factory.make_buffer(vbp, vbsd);
	UINT stride = sizeof(dx::VertexPostionColor<DirectX::XMFLOAT3>);
	UINT offset = 0;
	device_context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);


	std::wstring pixel_shader_path = L"resources/shaders/simple_pixel_shader.hlsl";
	auto pixel_shader_code = _shader_compiler.compile(pixel_shader_path, "main", "ps_5_0");

	auto vertex_shader = _shader_factory.create_vertex_shader(vertex_shader_code);
	device_context->VSSetShader(vertex_shader.Get(), nullptr, 0);
	auto pixel_shader = _shader_factory.create_pixel_shader(pixel_shader_code);
	device_context->PSSetShader(pixel_shader.Get(), nullptr, 0);
}

void Renderer::update()
{

}

void Renderer::render()
{
	const float teal[] = { 0.098f, 0.439f, 0.439f, 1.000f };
	auto render_target_view = _device_resources->get_render_target_view();
	auto device_context = _device_resources->get_device_context();
	device_context->ClearRenderTargetView(render_target_view.Get(), teal);
	device_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), nullptr);
	device_context->Draw(3, 0);
}

void Renderer::present()
{
	_device_resources->get_swapchain()->Present(1, 0);
}
