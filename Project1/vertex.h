#pragma once
#include <initializer_list>


namespace dx 
{
	template <typename Storage>
	struct VertexPostionColor
	{
		Storage point_coords;
		Storage color;
	};


	template <typename Storage>
	struct VertexPostionColorLight
	{
		Storage point_coords;
		Storage color;
		Storage light;
	};
}
