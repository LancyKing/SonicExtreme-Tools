#pragma once



namespace lancy {
	template <typename T> struct Array2 {
	private:
		unsigned int Width;
		unsigned int Height;
	public:
		T* Grid;

		unsigned int GetIndex(unsigned int x, unsigned int y) {
			return x + y * Width;
		}

		T Get(unsigned int x, unsigned int y) {
			return Grid[GetIndex(x, y)];
		}
		void Set(unsigned int x, unsigned int y, T value) {
			Grid[GetIndex(x, y)] = value;
		}

		unsigned int GetWidth() {
			return Width;
		}
		unsigned int GetHeight() {
			return Height;
		}

		Array2(unsigned int Width, unsigned int Height) : Width(Width), Height(Height) {
			Grid = new T[Width * Height];
		}
	};

	template <typename T> struct Array3 {
	private:
		unsigned int Width;
		unsigned int Height;
		unsigned int Length;
	public:
		T* Grid;

		unsigned int GetIndex(unsigned int x, unsigned int y, unsigned int z) {
			return x + y * Width + z * Width * Height;
		}

		T Get(unsigned int x, unsigned int y, unsigned int z) {
			return Grid[GetIndex(x, y, z)];
		}
		void Set(unsigned int x, unsigned int y, unsigned int z, T value) {
			Grid[GetIndex(x, y, z)] = value;
		}

		unsigned int GetWidth() {
			return Width;
		}
		unsigned int GetHeight() {
			return Height;
		}
		unsigned int GetLength() {
			return Length;
		}

		Array3(unsigned int Width, unsigned int Height, unsigned int Length) : Width(Width), Height(Height), Length(Length) {
			Grid = new T[Width * Height * Length];
		}
	};
}