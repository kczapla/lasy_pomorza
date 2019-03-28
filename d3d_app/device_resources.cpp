
#include "device_resources.h"

#include "device.h"
#include "render_target.h"
#include "graphics_interface.h"


void DeviceResources::create_swapchain(HWND window_id, std::pair<std::size_t, std::size_t> window_resolution)
{
	auto dxgi_device = dx::graphics_interface::get_dxgi_device_from<IDXGIDevice2, ID3D11Device>(device);

	DXGI_SWAP_CHAIN_DESC1 scd{
		window_resolution.first,
		window_resolution.second,
		DXGI_FORMAT_B8G8R8A8_UNORM,
		false,
		{ 1 , 0 },
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_STRETCH,
		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		DXGI_ALPHA_MODE_IGNORE,
		0,
	};
	auto swapchain = dx::graphics_interface::make_swapchain_for_win32_wnd<IDXGISwapChain1, IDXGIDevice2, IDXGIFactory2, DXGI_SWAP_CHAIN_DESC1>(dxgi_device, dxgi_factory, window_id, scd);
}

void DeviceResources::create_device()
{
	dxgi_factory = dx::graphics_interface::make_factory<IDXGIFactory2>();
	auto dxgi_adapters = dx::graphics_interface::make_adapters_list<IDXGIFactory2, IDXGIAdapter>(dxgi_factory);
	auto adapter = dxgi_adapters[0];
	auto[device, device_context] = dx::resources::make_device<ID3D11Device, ID3D11DeviceContext, IDXGIAdapter>(adapter);
}

void DeviceResources::create_render_traget()
{
	back_buffer = dx::graphics_interface::get_back_buffer<IDXGISwapChain1, ID3D11Texture2D>(dxgi_swapchain);
	D3D11_TEXTURE2D_DESC tex2d_desc;
	back_buffer->GetDesc(&tex2d_desc);

	D3D11_VIEWPORT view_port{
		0, 0, tex2d_desc.Width, tex2d_desc.Height, 0, 1,
	};
	device_context->RSSetViewports(1, &view_port);

	dx::graphics_pipeline::render_target::Factory<ID3D11Device, IDXGISwapChain1, ID3D11RenderTargetView> render_traget_view_factory(device, dxgi_swapchain);
	render_target_view = render_traget_view_factory.create<ID3D11Texture2D, D3D11_TEXTURE2D_DESC>({ 0 });
}

Microsoft::WRL::ComPtr<ID3D11Texture2D> DeviceResources::get_back_buffer() const
{
	return back_buffer;
}

Microsoft::WRL::ComPtr<ID3D11RenderTargetView> DeviceResources::get_render_target_view() const
{
	return render_target_view;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceResources::get_device_context() const
{
	return device_context;
}

Microsoft::WRL::ComPtr<ID3D11Device> DeviceResources::get_device() const
{
	return device;
}
