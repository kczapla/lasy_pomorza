#pragma once
#include <initializer_list>


namespace dx 
{
	template <typename Storage>
	struct VertexPostionColor
	{
		Storage point_coords;
		Storage color;

		//VertexPostionColor(Storage pc, Storage c) : point_coords(pc), color(c) {};
	};


	template <typename Storage>
	struct VertexPostionColorLight
	{
		Storage point_coords;
		Storage color;
		Storage light;

		//VertexPostionColor(Storage pc, Storage c, Storage l) : point_coords(pc), color(c), light(l) {};
	};
}
