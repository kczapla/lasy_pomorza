#pragma once

#include <vector>
#include <initializer_list>


namespace dx
{
	template <typename VertexType>
	struct Mesh
	{
		std::vector<int> indices;
		std::vector<VertexType> vertices;
	};
}