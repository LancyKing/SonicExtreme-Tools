#include "world.hpp"



Block::Block(bool Collision, Color Col) : Collision(Collision), Col(Col) {}

Block::Block() {}



void DynamicMesh::AddTriangle(Vector3 a, Vector3 b, Vector3 c) {
	TriangleIndices.push_back(Vertices.size());
	Vertices.push_back(a);
	TriangleIndices.push_back(Vertices.size());
	Vertices.push_back(b);
	TriangleIndices.push_back(Vertices.size());
	Vertices.push_back(c);
}

Mesh DynamicMesh::GetMesh() {
	Mesh Result{};

	// Vertices
	Result.vertices = new float[Vertices.size() * 3];
	Result.vertexCount = Vertices.size();
	for (int i = 0; i < Vertices.size(); i++) {
		Result.vertices[i * 3] = Vertices[i].x;
		Result.vertices[i * 3 + 1] = Vertices[i].y;
		Result.vertices[i * 3 + 2] = Vertices[i].z;
	}
	// Triangles
	Result.indices = new unsigned short[TriangleIndices.size()];
	Result.triangleCount = TriangleIndices.size() / 3;
	for (int i = 0; i < TriangleIndices.size(); i++) {
		Result.indices[i] = TriangleIndices[i];
	}
	// Normals
	Result.normals = new float[Vertices.size()];
	// Tex coords
	Result.texcoords = new float[Vertices.size() * 2];

	return Result;
}

void DynamicMesh::Draw() {

}

void DynamicMesh::DrawWires() {
	int TriangleCount{ (int)TriangleIndices.size() / 3 };

	for (int i = 0; i < TriangleCount; i++) {
		Vector3 A{ Vertices[TriangleIndices[i * 3]] };
		Vector3 B{ Vertices[TriangleIndices[i * 3 + 1]] };
		Vector3 C{ Vertices[TriangleIndices[i * 3 + 2]] };
		DrawLine3D(A, B, WHITE);
		DrawLine3D(B, C, WHITE);
		DrawLine3D(C, A, WHITE);
}	}

DynamicMesh::DynamicMesh() {}



void World::Draw() {
	DrawCubeWires(Vector3{ (float)Width / 2.f, (float)Height / 2.f, (float)Length / 2.f }, Width, Height, Length, RED);

	for (unsigned int x = 0; x < Width; x++) {
		for (unsigned int y = 0; y < Height; y++) {
			for (unsigned int z = 0; z < Length; z++) {
				if (Blocks.Grid[Blocks.GetIndex(x, y, z)].Collision) {
					Vector3 DrawPos{ (float)x + .5f, (float)y + .5f, (float)z + .5f };
					DrawCube(DrawPos, 1, 1, 1, Blocks.Grid[Blocks.GetIndex(x, y, z)].Col);
}	}	}	}	}

World::World(unsigned int Width, unsigned int Height, unsigned int Length) : Width(Width), Height(Height), Length(Length), Blocks(lancy::Array3<Block>{Width, Height, Length}) {}

World::World(const char* ImagePath) : Blocks(lancy::Array3<Block>{0,0,0}) {
	Image WorldImage{ LoadImage(ImagePath) };
	Color* ImageData{ LoadImageColors(WorldImage) };

	// Get world width
	Color BlankCol{ ImageData[0] };
	for (int i = 1; i < WorldImage.width; i++) {
		if (ImageData[i] == BlankCol) {
			Width = i - 1;
			break;
	}	}
	unsigned int ChunkCountX{ WorldImage.width / (Width + 2) };

	// Get world length
	for (int i = 1; i < WorldImage.height; i++) {
		if (ImageData[i * WorldImage.width] == BlankCol) {
			Length = i - 1;
			break;
	}	}
	unsigned int ChunkCountY{ WorldImage.height / (Length + 2) };

	// Get world height
	Height = ChunkCountX * ChunkCountY;
	std::cout << Width << " : " << Height << " : " << Length << "\n";

	// World construction
	Blocks = lancy::Array3<Block>{ Width,Height,Length };
	for (unsigned int cx = 0; cx < ChunkCountX; cx++) {
		for (unsigned int cy = 0; cy < ChunkCountY; cy++) {
			unsigned int IndexOffset{ (unsigned int)WorldImage.width + 1 };
			IndexOffset += cy * (Length + 2) * WorldImage.width + cx * (WorldImage.width / ChunkCountX);
			unsigned int y{ cy * ChunkCountX + cx };
			for (int x = 0; x < Width; x++) {
				for (int z = 0; z < Length; z++) {
					unsigned int Index{ (WorldImage.width * z + x + IndexOffset) };
					Color Col{ ImageData[Index] };
					if (Col == BlankCol) {
						continue;
					}
					else {
						Blocks.Grid[Blocks.GetIndex(x, y, z)] = Block{ true, Col };
	}	}	}	}	}

	// Mesh construction
	for (unsigned int x = 0; x < Width; x++) {
		for (unsigned int y = 0; y < Height; y++) {
			for (unsigned int z = 0; z < Length; z++) {
				// Left face   : x - 1
				unsigned int cx{ x - 1 };
				unsigned int cy{ y };
				unsigned int cz{ z };
				if (cx < Width) {
					unsigned int Index{ Blocks.GetIndex(cx, cy, cz) };
					if (!Blocks.Grid[Index].Collision) {
						Vector3 Offset{ cx,cy,cz };
						DMesh.AddTriangle(Offset + CubeCorners[0], Offset + CubeCorners[1], Offset + CubeCorners[2]);
						DMesh.AddTriangle(Offset + CubeCorners[2], Offset + CubeCorners[1], Offset + CubeCorners[3]);
				}	}
				else {
					Vector3 Offset{ cx,cy,cz };
					DMesh.AddTriangle(Offset + CubeCorners[0], Offset + CubeCorners[1], Offset + CubeCorners[2]);
					DMesh.AddTriangle(Offset + CubeCorners[2], Offset + CubeCorners[1], Offset + CubeCorners[3]);
				}
				// Right face  : x + 1
				cx = x + 1;
				if (cx < Width) {
					unsigned int Index{ Blocks.GetIndex(cx, cy, cz) };
					if (!Blocks.Grid[Index].Collision) {
						Vector3 Offset{ cx,cy,cz };
						DMesh.AddTriangle(Offset + CubeCorners[4], Offset + CubeCorners[6], Offset + CubeCorners[7]);
						DMesh.AddTriangle(Offset + CubeCorners[7], Offset + CubeCorners[5], Offset + CubeCorners[4]);
				}	}
				else {
					Vector3 Offset{ cx,cy,cz };
					DMesh.AddTriangle(Offset + CubeCorners[4], Offset + CubeCorners[6], Offset + CubeCorners[7]);
					DMesh.AddTriangle(Offset + CubeCorners[7], Offset + CubeCorners[5], Offset + CubeCorners[4]);
				}
				// Bottom face : y - 1
				cx = x;
				cy = y - 1;
				if (cy < Height) {
					Vector3 Offset{ cx,cy,cz };
					unsigned int Index{ Blocks.GetIndex(cx, cy, cz) };
					if (!Blocks.Grid[Index].Collision) {
						DMesh.AddTriangle(Offset + CubeCorners[2], Offset + CubeCorners[6], Offset + CubeCorners[4]);
						DMesh.AddTriangle(Offset + CubeCorners[4], Offset + CubeCorners[2], Offset + CubeCorners[0]);
				}	}
				else {
					Vector3 Offset{ cx,cy,cz };
					DMesh.AddTriangle(Offset + CubeCorners[2], Offset + CubeCorners[6], Offset + CubeCorners[4]);
					DMesh.AddTriangle(Offset + CubeCorners[4], Offset + CubeCorners[2], Offset + CubeCorners[0]);
				}
				// Top face    : y + 1
				cy = y + 1;
				if (cy < Height) {
					unsigned int Index{ Blocks.GetIndex(cx, cy, cz) };
					if (!Blocks.Grid[Index].Collision) {
						Vector3 Offset{ cx,cy,cz };
						DMesh.AddTriangle(Offset + CubeCorners[1], Offset + CubeCorners[7], Offset + CubeCorners[5]);
						DMesh.AddTriangle(Offset + CubeCorners[1], Offset + CubeCorners[7], Offset + CubeCorners[3]);
				}	}
				else {
					Vector3 Offset{ cx,cy,cz };
					DMesh.AddTriangle(Offset + CubeCorners[1], Offset + CubeCorners[7], Offset + CubeCorners[5]);
					DMesh.AddTriangle(Offset + CubeCorners[1], Offset + CubeCorners[7], Offset + CubeCorners[3]);
				}
				// Back face   : z - 1
				cy = y;
				cz = z - 1;
				if (cz < Length) {
					unsigned int Index{ Blocks.GetIndex(cx, cy, cz) };
					if (!Blocks.Grid[Index].Collision) {
						Vector3 Offset{ cx,cy,cz };
						DMesh.AddTriangle(Offset + CubeCorners[2], Offset + CubeCorners[7], Offset + CubeCorners[6]);
						DMesh.AddTriangle(Offset + CubeCorners[2], Offset + CubeCorners[7], Offset + CubeCorners[3]);
				}	}
				else {
					Vector3 Offset{ cx,cy,cz };
					DMesh.AddTriangle(Offset + CubeCorners[2], Offset + CubeCorners[7], Offset + CubeCorners[6]);
					DMesh.AddTriangle(Offset + CubeCorners[2], Offset + CubeCorners[7], Offset + CubeCorners[3]);
				}
				// Front face  : z + 1
				cz = z + 1;
				if (cz < Length) {
					unsigned int Index{ Blocks.GetIndex(cx, cy, cz) };
					if (!Blocks.Grid[Index].Collision) {
						Vector3 Offset{ cx,cy,cz };
						DMesh.AddTriangle(Offset + CubeCorners[1], Offset + CubeCorners[4], Offset + CubeCorners[0]);
						DMesh.AddTriangle(Offset + CubeCorners[1], Offset + CubeCorners[5], Offset + CubeCorners[4]);
				}	}
				else {
					Vector3 Offset{ cx,cy,cz };
					DMesh.AddTriangle(Offset + CubeCorners[1], Offset + CubeCorners[4], Offset + CubeCorners[0]);
					DMesh.AddTriangle(Offset + CubeCorners[1], Offset + CubeCorners[5], Offset + CubeCorners[4]);
	}	}	}	}

	// Convert model
	WorldModel = LoadModelFromMesh(DMesh.GetMesh());
}