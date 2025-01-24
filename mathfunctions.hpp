#pragma once
#include "raylib.h"

extern const float pi;
extern const float tau;

// 1D
bool DoLinesOverlap(float StartA, float EndA, float StartB, float EndB);

// 2D
bool DoBoxesOverlap(Vector2 BoxPosA, Vector2 BoxSizeA, Vector2 BoxPosB, Vector2 BoxSizeB); // Uses center for positions
Vector2 operator+(Vector2 lhs, Vector2 rhs);
Vector2 operator-(Vector2 lhs, Vector2 rhs);
Vector2 operator*(Vector2 lhs, float rhs);
Vector2 operator/(Vector2 lhs, float rhs);
float Max(float a, float b);
float Min(float a, float b);
float Clamp(float v, float min, float max);
float Dot(Vector2 a, Vector2 b);
float Length(Vector2 v);
float LengthSquared(Vector2 v);
float Distance(Vector2 v1, Vector2 v2);
float DegreesToRadians(float degrees);
float RadiansToDegrees(float radians);
float Interpolate(float a, float b, float w);
float Power(float a, int e);
Vector2 Normal(Vector2 v);
Vector2 Rotate90(Vector2 v, int quarters);
Vector2 RotateRadians(Vector2 v, float radians);
int Max(int a, int b);
int Min(int a, int b);
int Clamp(int v, int min, int max);

struct Vector2i {
	int x{ 0 };
	int y{ 0 };

	Vector2i(int x, int y);
	Vector2i();
};

Vector2i operator+(Vector2i lhs, Vector2i rhs);
Vector2i operator-(Vector2i lhs, Vector2i rhs);
Vector2i operator*(Vector2i lhs, int rhs);
bool operator==(Vector2i lhs, Vector2i rhs);
float Distance(Vector2i v1, Vector2i v2);

// 3D
bool DoCubesOverlap(Vector3 CubePosA, Vector3 CubeSizeA, Vector3 CubePosB, Vector3 CubeSizeB); // Uses center for positions
Vector3 operator+(Vector3 lhs, Vector3 rhs);
Vector3 operator-(Vector3 lhs, Vector3 rhs);
Vector3 operator*(Vector3 lhs, float rhs);
Vector3 operator/(Vector3 lhs, float rhs);
float Length(Vector3 v);
float Distance(Vector3 v1, Vector3 v2);
Vector3 Normal(Vector3 v);
Vector3 Rotate3D(Vector3 v, Vector3 r);

// Lines
struct Line {
	Vector2 a;
	Vector2 b;

	virtual Vector2 ClosestPoint(Vector2 p);

	Line(Vector2 start, Vector2 end);
};

struct Segment : public Line {
	Vector2 ClosestPoint(Vector2 p);

	Segment(Vector2 start, Vector2 end);
};

// Constraints
Vector2 DistanceConstraint(Vector2 a, Vector2 b, float length);
Vector2 SegmentConstraint(Vector2 a, Vector2 b, Vector2 p);

// Fast approximations
float FastPower(float a, float e);

// Colors
Color Interpolate(Color a, Color b, float w);
bool operator==(Color lhs, Color rhs);