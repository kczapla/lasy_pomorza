#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <Windows.h>
#include <dxgi1_3.h>
#include <d3d11_4.h>
#include <wrl.h>

#include <utility>
#include <memory>


class DeviceResources
{
public:
	DeviceResources() {};

	void create_swapchain(HWND window_id, std::pair<std::size_t, std::size_t> window_resolution);
	void create_device();
	void create_render_traget();

	Microsoft::WRL::ComPtr<ID3D11Texture2D> get_back_buffer() const;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> get_render_target_view() const;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> get_device_context() const;
	Microsoft::WRL::ComPtr<ID3D11Device> get_device() const;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> get_swapchain() const;

private:
	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgi_factory{ nullptr };
	Microsoft::WRL::ComPtr<IDXGIAdapter> dxgi_adapter{ nullptr };
	Microsoft::WRL::ComPtr<ID3D11Device> device{ nullptr };
	Microsoft::WRL::ComPtr<IDXGISwapChain1> dxgi_swapchain{ nullptr };
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context{ nullptr };

	Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer{ nullptr };
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view{ nullptr };
};


template <typename DeviceResources, typename Window>
std::shared_ptr<DeviceResources> make_device_resources(std::shared_ptr<Window> window)
{
	auto device_resources = std::make_shared<DeviceResources>();
	device_resources->create_device();
	device_resources->create_swapchain(window->get_window_id(), window->get_window_resolution());
	device_resources->create_render_traget();

	return device_resources;
}