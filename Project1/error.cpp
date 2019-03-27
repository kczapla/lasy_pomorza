#include <comdef.h>
#include <stdexcept>

#include "error.h"

namespace windows_infrastructure
{
	void throw_if_failed(HRESULT hr)
	{
		if (hr != S_OK)
		{
			_com_error err(hr);
			auto err_msg = err.ErrorMessage();
			throw std::runtime_error(err_msg);
		}
	}
}