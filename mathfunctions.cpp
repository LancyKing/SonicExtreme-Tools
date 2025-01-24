#include "mathfunctions.hpp"
#include <math.h>

const float pi{ 3.14159 };
const float tau{ pi * 2.f };

// 1D
bool DoLinesOverlap(float StartA, float EndA, float StartB, float EndB) {
	if (StartA < EndB && EndA > StartB) {
		return true;
	}
	return false;
}

// 2D
bool DoBoxesOverlap(Vector2 BoxPosA, Vector2 BoxSizeA, Vector2 BoxPosB, Vector2 BoxSizeB) {
	if (DoLinesOverlap(BoxPosA.x - BoxSizeA.x / 2.f, BoxPosA.x + BoxSizeA.x / 2.f, BoxPosB.x - BoxSizeB.x / 2.f, BoxPosB.x + BoxSizeB.x / 2.f)) {
		if (DoLinesOverlap(BoxPosA.y - BoxSizeA.y / 2.f, BoxPosA.y + BoxSizeA.y / 2.f, BoxPosB.y - BoxSizeB.y / 2.f, BoxPosB.y + BoxSizeB.y / 2.f)) {
			return true;
		}
		return false;
	}
	return false;
}
Vector2 operator+(Vector2 lhs, Vector2 rhs) {
	return Vector2{ lhs.x + rhs.x, lhs.y + rhs.y };
}
Vector2 operator-(Vector2 lhs, Vector2 rhs) {
	return Vector2{ lhs.x - rhs.x, lhs.y - rhs.y };
}
Vector2 operator*(Vector2 lhs, float rhs) {
	return Vector2{ lhs.x * rhs, lhs.y * rhs };
}
Vector2 operator/(Vector2 lhs, float rhs) {
	return Vector2{ lhs.x / rhs, lhs.y / rhs };
}
float Max(float a, float b) {
	if (a > b) { return a; }
	return b;
}
float Min(float a, float b) {
	if (a < b) { return a; }
	return b;
}
float Clamp(float v, float min, float max) {
	if (v < min) {
		return min;
	}
	if (v > max) {
		return max;
	}
	return v;
}
float Dot(Vector2 a, Vector2 b) {
	return a.x * b.x + a.y * b.y;
}
float Length(Vector2 v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}
float LengthSquared(Vector2 v) {
	return v.x * v.x + v.y * v.y;
}
float Distance(Vector2 v1, Vector2 v2) {
	return Length(v1 - v2);
}
float DegreesToRadians(float degrees) {
	return (degrees / 180.f) * pi;
}
float RadiansToDegrees(float radians) {
	return (radians / pi) * 180.f;
}
float Interpolate(float a, float b, float w) {
	return a * (1.f - w) + b * w;
}
float Power(float a, int e) {
	float result{ 1.f };
	if (e > 0) {
		for (int i = 0; i < e; i++) {
			result *= a;
		}
	}
	else if (e < 0) {
		for (int i = 0; i > e; i--) {
			result /= a;
		}
	}
	return result;
}
Vector2 Normal(Vector2 v) {
	if (Length(v) == 0.f) {
		return Vector2{ 0,0 };
	}
	return v / Length(v);
}
Vector2 Rotate90(Vector2 v, int quarters) {
	int rotations = quarters % 4;
	if (rotations < 0) {
		rotations += 4;
	}

	Vector2 temp{ v };
	for (int i = 0; i < rotations; i++) {
		temp.x = v.y;
		temp.y = -v.x;
		v = temp;
	}
	return v;
}
Vector2 RotateRadians(Vector2 v, float radians) {
	Vector2 result{ v };
	result.x = cosf(radians) * v.x - sinf(radians) * v.y;
	result.y = sinf(radians) * v.x + cosf(radians) * v.y;
	return result;
}
int Max(int a, int b) {
	if (a > b) { return a; }
	else { return b; }
}
int Min(int a, int b) {
	if (a < b) { return a; }
	else { return b; }
}
int Clamp(int v, int min, int max) {
	if (v < min) {
		return min;
	}
	if (v > max) {
		return max;
	}
	return v;
}

Vector2i::Vector2i(int x, int y) : x(x), y(y) {}
Vector2i::Vector2i() {}

Vector2i operator+(Vector2i lhs, Vector2i rhs) {
	return Vector2i{ lhs.x + rhs.x, lhs.y + rhs.y };
}
Vector2i operator-(Vector2i lhs, Vector2i rhs) {
	return Vector2i{ lhs.x - rhs.x, lhs.y - rhs.y };
}
Vector2i operator*(Vector2i lhs, int rhs) {
	return Vector2i{ lhs.x * rhs, lhs.y * rhs };
}
bool operator==(Vector2i lhs, Vector2i rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
float Distance(Vector2i v1, Vector2i v2) {
	int dx{ v1.x - v2.x };
	int dy{ v1.y - v2.y };
	return sqrt(dx * dx + dy * dy);
}

// 3D
bool DoCubesOverlap(Vector3 CubePosA, Vector3 CubeSizeA, Vector3 CubePosB, Vector3 CubeSizeB) {
	if (DoLinesOverlap(CubePosA.x - CubeSizeA.x / 2.f, CubePosA.x + CubeSizeA.x / 2.f, CubePosB.x - CubeSizeB.x / 2.f, CubePosB.x + CubeSizeB.x / 2.f)) {
		if (DoLinesOverlap(CubePosA.y - CubeSizeA.y / 2.f, CubePosA.y + CubeSizeA.y / 2.f, CubePosB.y - CubeSizeB.y / 2.f, CubePosB.y + CubeSizeB.y / 2.f)) {
			if (DoLinesOverlap(CubePosA.z - CubeSizeA.z / 2.f, CubePosA.z + CubeSizeA.z / 2.f, CubePosB.z - CubeSizeB.z / 2.f, CubePosB.z + CubeSizeB.z / 2.f)) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}
Vector3 operator+(Vector3 lhs, Vector3 rhs) {
	return Vector3{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}
Vector3 operator-(Vector3 lhs, Vector3 rhs) {
	return Vector3{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}
Vector3 operator*(Vector3 lhs, float rhs) {
	return Vector3{ lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}
Vector3 operator/(Vector3 lhs, float rhs) {
	return Vector3{ lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
}
float Length(Vector3 v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
float Distance(Vector3 v1, Vector3 v2) {
	return Length(v1 - v2);
}
Vector3 Normal(Vector3 v) {
	return v / Length(v);
}
Vector3 Rotate3D(Vector3 v, Vector3 r) {
	Vector3 Result{ v };
	Vector2 Temp{};
	// Rotate x axis
	Temp = RotateRadians(Vector2{ Result.y,Result.z }, r.x);
	Result.y = Temp.x;
	Result.z = Temp.y;
	// Rotate y axis
	Temp = RotateRadians(Vector2{ Result.x,Result.z }, r.y);
	Result.x = Temp.x;
	Result.z = Temp.y;
	// Rotate z axis
	Temp = RotateRadians(Vector2{ Result.y,Result.z }, r.z);
	Result.y = Temp.x;
	Result.z = Temp.y;
	return Result;
}


// Lines
Vector2 Line::ClosestPoint(Vector2 p) {
	Vector2 n{ Normal(b - a) };
	return a + n * Dot(n, p);
}

Line::Line(Vector2 start, Vector2 end) : a(start), b(end) {}

Vector2 Segment::ClosestPoint(Vector2 p) {
	Vector2 n{ Normal(b - a) };
	float lengthP_AB{ Dot(n,p - a) };
	if (lengthP_AB <= 0.f) {
		return a;
	}
	else if (lengthP_AB >= Distance(a, b)) {
		return b;
	}
	else {
		return a + n * lengthP_AB;
	}
}

Segment::Segment(Vector2 a, Vector2 b) : Line{ a,b } {}

// Constraints
Vector2 DistanceConstraint(Vector2 a, Vector2 b, float length) {
	return a + Normal(b - a) * (Distance(a, b) - length);
}
Vector2 SegmentConstraint(Vector2 a, Vector2 b, Vector2 p) {
	return Segment{ a,b }.ClosestPoint(p);
}

// Fast approximations
float FastPower(float a, float e) {
	return Interpolate(Power(a, int(e)), Power(a, int(ceil(e))), (ceil(e) - e) * -1.f + 1.f);
}

// Colors
Color Interpolate(Color a, Color b, float w) {
	unsigned char r{ unsigned char(Interpolate(float(a.r), float(b.r), w)) };
	unsigned char g{ unsigned char(Interpolate(float(a.g), float(b.g), w)) };
	unsigned char b2{ unsigned char(Interpolate(float(a.b), float(b.b), w)) };
	unsigned char a2{ unsigned char(Interpolate(float(a.a), float(b.a), w)) };
	return Color{ r,g,b2,a2 };
}
bool operator==(Color lhs, Color rhs) {
	if (lhs.r != rhs.r) {
		return false;
	}
	if (lhs.g != rhs.g) {
		return false;
	}
	if (lhs.b != rhs.b) {
		return false;
	}
	return true;
}