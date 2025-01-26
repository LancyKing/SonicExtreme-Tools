#pragma once
#include <fstream>
#include <vector>



namespace lancy {
	struct Vertex {
		float x;
		float y;
		float z;
		float w;

		Vertex(float x, float y, float z, float w);
		Vertex(float x, float y, float z);
	};



	struct Face {
		unsigned int v1;
		unsigned int v2;
		unsigned int v3;
	};



	struct DynamicMesh {
		std::vector<Vertex>Vertices;
		std::vector<Face>Faces;

		int AddVertex(Vertex v);
		int AddFace(Face f);

		void Export(const char* Filename); // Include ".obj" at end of filename

		DynamicMesh();
	};

	DynamicMesh CreateCube(float x, float y, float z, float Width);
}