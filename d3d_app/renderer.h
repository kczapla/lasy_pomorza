#pragma once

#include <wrl.h>

#include <memory>

#include "device_resources.h"
#include "shader.h"
#include "input_assembler.h"
#include "buffer.h"
#include "render_target.h"


class Renderer
{
	using InputAsmFactory = dx::graphics_pipeline::input_assembler::D3DFactory<ID3D11Device, ID3D11InputLayout, D3D11_INPUT_ELEMENT_DESC>;
	using BufferFactory = dx::resources::BufferFactory<ID3D11Device, D3D11_BUFFER_DESC, D3D11_SUBRESOURCE_DATA>;

public:
	Renderer(std::shared_ptr<DeviceResources> device_resurces) :
		_device_resources(device_resurces)

	{ };

	void setup();
	void create_resources();
	void update();
	void render();
	void present();

private:
	std::shared_ptr<DeviceResources> _device_resources{ nullptr };
	dx::shader::Compiler<ID3D11Device> _shader_compiler;
	dx::shader::Factory<ID3D11Device> _shader_factory;
	InputAsmFactory _input_asm_factory;
	BufferFactory _buffer_factory;
};


template <typename Renderer, typename DeviceResources>
std::shared_ptr<Renderer> make_renderer(std::shared_ptr<DeviceResources> device_resources)
{
	auto renderer = std::make_shared<Renderer>(device_resources);
	renderer->setup();
	renderer->create_resources();
	return renderer;
}