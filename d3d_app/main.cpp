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

#include "file_operations.h"

#include <string>
#include <vector>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	return 0;
}
