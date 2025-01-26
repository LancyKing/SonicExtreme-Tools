#include "lancy_meshes.hpp"



lancy::Vertex::Vertex(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
lancy::Vertex::Vertex(float x, float y, float z) : x(x), y(y), z(z), w(1.f) {}



int lancy::DynamicMesh::AddVertex(Vertex v) {
	Vertices.push_back(v);
	return Vertices.size() - 1;
}

int lancy::DynamicMesh::AddFace(Face f) {
	Faces.push_back(f);
	return Faces.size() - 1;
}

void lancy::DynamicMesh::Export(const char* Filename) {
	std::ofstream fout{ Filename };
	for (int i = 0; i < Vertices.size(); i++) {
		fout << "v ";
		fout << Vertices[i].x << " ";
		fout << Vertices[i].y << " ";
		fout << Vertices[i].z << " ";
		fout << Vertices[i].w << "\n";
	}
	for (int i = 0; i < Faces.size(); i++) {
		fout << "f ";
		fout << Faces[i].v1 + 1 << " ";
		fout << Faces[i].v2 + 1 << " ";
		fout << Faces[i].v3 + 1 << "\n";
	}
}

lancy::DynamicMesh::DynamicMesh() {}

lancy::DynamicMesh lancy::CreateCube(float x, float y, float z, float Width) {
	lancy::DynamicMesh Result;
	// Vertices
	Result.AddVertex({ x + Width / -2.f, y + Width / -2.f, z + Width / -2.f });
	Result.AddVertex({ x + Width / -2.f, y + Width / 2.f,  z + Width / -2.f });
	Result.AddVertex({ x + Width / 2.f,  y + Width / -2.f, z + Width / -2.f });
	Result.AddVertex({ x + Width / 2.f,  y + Width / 2.f,  z + Width / -2.f });
	Result.AddVertex({ x + Width / -2.f, y + Width / -2.f, z + Width / 2.f  });
	Result.AddVertex({ x + Width / -2.f, y + Width / 2.f,  z + Width / 2.f  });
	Result.AddVertex({ x + Width / 2.f,  y + Width / -2.f, z + Width / 2.f  });
	Result.AddVertex({ x + Width / 2.f,  y + Width / 2.f,  z + Width / 2.f  });
	// Faces
	Result.AddFace({ 0,1,2 });
	Result.AddFace({ 1,3,2 });
	Result.AddFace({ 7,4,6 });
	Result.AddFace({ 4,5,7 });
	Result.AddFace({ 2,7,6 });
	Result.AddFace({ 2,3,7 });
	Result.AddFace({ 1,4,0 });
	Result.AddFace({ 1,5,4 });
	Result.AddFace({ 3,1,5 });
	Result.AddFace({ 3,7,5 });
	Result.AddFace({ 2,4,0 });
	Result.AddFace({ 2,4,6 });
	return Result;
}