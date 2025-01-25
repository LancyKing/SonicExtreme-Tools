#pragma once
#include "global.hpp"



constexpr Vector3 CubeCorners[8]{
	Vector3{-.5f,-.5f,-.5f},
	Vector3{-.5f, .5f,-.5f},
	Vector3{-.5f,-.5f, .5f},
	Vector3{-.5f, .5f, .5f},
	Vector3{ .5f,-.5f,-.5f},
	Vector3{ .5f, .5f,-.5f},
	Vector3{ .5f,-.5f, .5f},
	Vector3{ .5f, .5f, .5f}
};



struct Block {
	bool Collision{ false };
	Color Col{ BLACK };

	Block(bool Collision, Color Col);
	Block();
};



struct DynamicMesh {
	std::vector<Vector3>Vertices;
	std::vector<unsigned short>TriangleIndices;

	void AddTriangle(Vector3 a, Vector3 b, Vector3 c);
	Mesh GetMesh();

	void Draw();
	void DrawWires();

	DynamicMesh();
};



struct World {
	unsigned int Width;
	unsigned int Height;
	unsigned int Length;
	lancy::Array3<Block>Blocks;
	Model WorldModel{};
	DynamicMesh DMesh{};

	Block* CastRay(Vector3 Pos, Vector3 Dir);

	void Draw();

	World(unsigned int Width, unsigned int Height, unsigned int Length);
	World(const char* ImagePath);
};