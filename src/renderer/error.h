#pragma once

#pragma once

#include <windows.h>
#include <strsafe.h>

namespace windows_infrastructure
{
	void throw_if_failed(HRESULT hr);
}
