#include "global.hpp"

#include "assets.hpp"
#include "world.hpp"
#include "lancy_meshes.hpp"



// main.cpp globals
Vector3 PlayerPos{};
Vector3 PlayerAngle{};
Vector3 PlayerLookDir{};
float PlayerMoveSpeed{};



int main() {
	// Render variable initialization
	InitWindow(Settings::WindowWidth, Settings::WindowHeight, ":3"); SetTargetFPS(60);
	DisableCursor();

	RenderTexture2D RenderTexture{ LoadRenderTexture(Settings::RenderWidth,Settings::RenderHeight) };
	Rectangle RenderRectangle{ 0.f,0.f,Settings::RenderWidth,-Settings::RenderHeight };
	Rectangle WindowRectangle{ -Settings::RenderRatio,-Settings::RenderRatio,Settings::WindowWidth + Settings::RenderRatio * 2,Settings::WindowHeight + Settings::RenderRatio * 2 };

	Camera MainCam{ 0 };
	MainCam.fovy = 90.f;
	MainCam.position = Vector3{ 0.f,2.f,-3.f };
	MainCam.projection = CAMERA_PERSPECTIVE;
	MainCam.target = Vector3{};
	MainCam.up = Vector3{ 0.f,1.f,0.f };

	// World initialization
	World MainWorld{ "assets/pcx_levels/GOLD.png" };

	// Generate mesh
	lancy::DynamicMesh DMesh;
	DMesh = lancy::CreateCube(0.f, 0.f, 0.f, .5f);
	DMesh.Export("file.obj");


	while (!WindowShouldClose()) {
		// Update
		float Delta{ GetFrameTime() };
		Vector3 MoveDir{};
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			PlayerMoveSpeed = 37.5f;
		}
		else {
			PlayerMoveSpeed = 12.5f;
		}
		if (IsKeyDown(KEY_W)) {
			MoveDir.x += sinf(-PlayerAngle.y) * Delta * PlayerMoveSpeed;
			MoveDir.z += cosf(-PlayerAngle.y) * Delta * PlayerMoveSpeed;
		}
		if (IsKeyDown(KEY_S)) {
			MoveDir.x -= sinf(-PlayerAngle.y) * Delta * PlayerMoveSpeed;
			MoveDir.z -= cosf(-PlayerAngle.y) * Delta * PlayerMoveSpeed;
		}
		if (IsKeyDown(KEY_A)) {
			MoveDir.x += cosf(-PlayerAngle.y) * Delta * PlayerMoveSpeed;
			MoveDir.z -= sinf(-PlayerAngle.y) * Delta * PlayerMoveSpeed;
		}
		if (IsKeyDown(KEY_D)) {
			MoveDir.x -= cosf(-PlayerAngle.y) * Delta * PlayerMoveSpeed;
			MoveDir.z += sinf(-PlayerAngle.y) * Delta * PlayerMoveSpeed;
		}
		if (IsKeyDown(KEY_SPACE)) {
			MoveDir.y += Delta * 12.5f;
		}
		if (IsKeyDown(KEY_C)) {
			MoveDir.y -= Delta * 12.5f;
		}
		PlayerPos = PlayerPos + MoveDir;
		Vector2 MouseDelta{ GetMouseDelta() };
		PlayerAngle.x += MouseDelta.y * .004f;
		PlayerAngle.y += MouseDelta.x * .004f;
		PlayerAngle.x = Clamp(PlayerAngle.x, -1.45f, 1.45f);
		PlayerLookDir = Rotate3D(Vector3{ 0.f,0.f,1.f }, PlayerAngle);
		MainCam.position = PlayerPos;
		MainCam.target = PlayerPos + PlayerLookDir;


		// Draw
		BeginTextureMode(RenderTexture); ClearBackground(BLACK);
		BeginMode3D(MainCam);


		MainWorld.Draw();
		

		EndMode3D(); EndTextureMode(); BeginDrawing();
		DrawTexturePro(RenderTexture.texture, RenderRectangle, WindowRectangle, Vector2{ 0,0 }, 0.f, WHITE);


		// UI : Color of block you're looking at
		Block* ThisBlock{ MainWorld.CastRay(PlayerPos,PlayerLookDir) };
		const char* ColorText{ "NoCol" };
		if (ThisBlock == nullptr) {
			DrawText("NoCol", 0, 0, 18, WHITE);
		}
		else {
			Color Col{ ThisBlock->Col };
			ColorText = TextFormat("(%i,%i,%i)", Col.r, Col.g, Col.b);
		}
		DrawRectangle(0, 0, MeasureText(ColorText, 18) + 4, 20, BLACK);
		DrawText(ColorText, 0, 0, 18, WHITE);

		// UI : Crosshair
		int MidX{ Settings::WindowWidth / 2 };
		int MidY{ Settings::WindowHeight / 2 };
		DrawLineEx(Vector2{ (float)MidX - 8, (float)MidY }, Vector2{ (float)MidX + 8, (float)MidY }, 5, BLACK);
		DrawLineEx(Vector2{ (float)MidX, (float)MidY - 8 }, Vector2{ (float)MidX, (float)MidY + 8 }, 5, BLACK);
		DrawLineEx(Vector2{ (float)MidX - 6, (float)MidY }, Vector2{ (float)MidX + 6, (float)MidY }, 3, WHITE);
		DrawLineEx(Vector2{ (float)MidX, (float)MidY - 6 }, Vector2{ (float)MidX, (float)MidY + 6 }, 3, WHITE);


		EndDrawing();
	}
}