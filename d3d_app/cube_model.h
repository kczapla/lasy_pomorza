#pragma once

#include <directxmath.h>

#include "vertex.h"
#include "mesh.h"

#include <vector>


template <typename T = dx::VertexPostionColor<DirectX::XMFLOAT3>>
dx::Mesh<T> build_simeple_cube_model()
{
	std::vector<T> simple_cube_vertices{
		{ DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0,   0,   0), },
		{ DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0,   0,   1), },
		{ DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0,   1,   0), },
		{ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0,   1,   1), },

		{ DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(1,   0,   0), },
		{ DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(1,   0,   1), },
		{ DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(1,   1,   0), },
		{ DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(1,   1,   1), },
	};
	
	std::vector<int> simple_cube_indices{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,


		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
	};

	dx::Mesh<T> cube_model; 
	cube_model.vertices = simple_cube_vertices;
	cube_model.indices = simple_cube_indices;

	return cube_model;
}


std::vector<dx::VertexPostionColor<DirectX::XMFLOAT3>> triangle_vertcies
{
	{ DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.0f,   0.0f,   1.0f), },
	{ DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), },
	{ DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f), DirectX::XMFLOAT3(0.0f,   0.0f,   1.0f), },
};