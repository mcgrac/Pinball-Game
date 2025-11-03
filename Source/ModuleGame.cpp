#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

#include <iostream>

ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	state = GameState::INTRO;
}

ModuleGame::~ModuleGame()
{
}

bool ModuleGame::Start()
{
	LOG("Game Module Start");

	// Load intro and end textures
	introTexture = LoadTexture("Assets/Textures/initialScreen.png");
	endTexture = LoadTexture("Assets/Textures/endScreen.png");

	// Load game textures (if needed here or later)
	ballTexture = LoadTexture("Assets/Textures/ball.png");
	launcherTexture = LoadTexture("Assets/Textures/launcher.png");

	return true; // wait for user to press SPACE
}

bool ModuleGame::CleanUp()
{
	LOG("Cleaning Game Module");
	if (currentMap != nullptr)
	{
		currentMap->CleanUp();
		delete currentMap;
		currentMap = nullptr;
	}

	return true;
}

void ModuleGame::StartGame()
{
	// Reset counters
	currentBalls = 0;
	restartBallFlag = false;

	// Create objects only once space has been pressed
	ball = new Ball(App->physics, 550, 800, this, ballTexture, b2_dynamicBody, ColliderType::BALL);
	launcher = new Launcher(App->physics, ball, 550, 900, 50, 20, this, launcherTexture, ColliderType::LAUNCHER);

	currentMap = new Level1(App->physics, this);
	currentMap->Start();

	state = GameState::PLAYING;
}

update_status ModuleGame::Update()
{
	switch (state)
	{
	case GameState::INTRO:
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(introTexture, 0, 0, WHITE);
		EndDrawing();

		if (IsKeyPressed(KEY_SPACE))
		{
			StartGame();
		}

		return UPDATE_CONTINUE;
	}
	case GameState::PLAYING:
	{
		if (currentBalls <= maxBalls)
		{
			if (IsKeyDown(KEY_DOWN)) launcher->Press();
			if (IsKeyReleased(KEY_DOWN)) launcher->Release();

			launcher->Update();
			currentMap->Update();
			ball->Update();

			if (restartBallFlag)
				RestartBall();
		}
		else
		{
			state = GameState::GAMEOVER;
		}
		break;
	}
	case GameState::GAMEOVER:
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(endTexture, 0, 0, WHITE);
		EndDrawing();

		if (IsKeyPressed(KEY_SPACE))
		{
			// cleanup current game
			CleanUp();
			// go back to intro
			state = GameState::INTRO;
		}

		return UPDATE_CONTINUE;
	}
	}

	return UPDATE_CONTINUE;
}

void ModuleGame::RestartBall()
{
	ball->GetBody()->SetPosition(550, 800);
	currentBalls++;
	restartBallFlag = false;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (!ball) return;

	PhysBody* ballBody = nullptr;
	PhysBody* other = nullptr;

	if (bodyA == ball->GetBody()) { ballBody = bodyA; other = bodyB; }
	else if (bodyB == ball->GetBody()) { ballBody = bodyB; other = bodyA; }
	else return;

	if (other->entity && other->entity->GetColliderType() == ColliderType::LAUNCHER)
	{
		launcher->OnBallCollision(true);
	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::VOID)
	{
		restartBallFlag = true;
	}
}

void ModuleGame::OnCollisionEnd(PhysBody* bodyA, PhysBody* bodyB)
{
	if (!ball) return;

	PhysBody* ballBody = nullptr;
	PhysBody* other = nullptr;

	if (bodyA == ball->GetBody()) { ballBody = bodyA; other = bodyB; }
	else if (bodyB == ball->GetBody()) { ballBody = bodyB; other = bodyA; }
	else return;

	if (other->entity && other->entity->GetColliderType() == ColliderType::LAUNCHER)
	{
		launcher->OnBallCollision(false);
	}
}
