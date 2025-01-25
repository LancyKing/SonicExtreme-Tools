#include "global.hpp"

#include "assets.hpp"
#include "world.hpp"



// main.cpp globals
Vector3 PlayerPos{};
Vector3 PlayerAngle{};
Vector3 PlayerLookDir{};



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


	while (!WindowShouldClose()) {
		// Update
		float Delta{ GetFrameTime() };
		Vector3 MoveDir{};
		if (IsKeyDown(KEY_W)) {
			MoveDir.x += sinf(-PlayerAngle.y) * Delta * 12.5f;
			MoveDir.z += cosf(-PlayerAngle.y) * Delta * 12.5f;
		}
		if (IsKeyDown(KEY_S)) {
			MoveDir.x -= sinf(-PlayerAngle.y) * Delta * 12.5f;
			MoveDir.z -= cosf(-PlayerAngle.y) * Delta * 12.5f;
		}
		if (IsKeyDown(KEY_A)) {
			MoveDir.x += cosf(-PlayerAngle.y) * Delta * 12.5f;
			MoveDir.z -= sinf(-PlayerAngle.y) * Delta * 12.5f;
		}
		if (IsKeyDown(KEY_D)) {
			MoveDir.x -= cosf(-PlayerAngle.y) * Delta * 12.5f;
			MoveDir.z += sinf(-PlayerAngle.y) * Delta * 12.5f;
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



		// Update shader
		float ShaderViewPos[]{ MainCam.position.x,MainCam.position.y,MainCam.position.z };
		SetShaderValue(Shader1, GetShaderLocation(Shader1, "viewPos"), ShaderViewPos, SHADER_UNIFORM_VEC3);


		// Draw
		BeginTextureMode(RenderTexture); ClearBackground(BLACK);
		BeginMode3D(MainCam);


		MainWorld.Draw();
		

		EndMode3D(); EndTextureMode(); BeginDrawing();
		DrawTexturePro(RenderTexture.texture, RenderRectangle, WindowRectangle, Vector2{ 0,0 }, 0.f, WHITE);
		EndDrawing();
	}
}