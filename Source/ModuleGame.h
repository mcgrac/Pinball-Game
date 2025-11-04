#pragma once

#include "Globals.h"
#include "Module.h"
#include "p2Point.h"
#include "Ball.h"
#include "Launcher.h"
#include "Bumper.h"
#include "Flipper.h"
#include "raylib.h"
#include <vector>
#include "Map.h"
#include "Level1.h"

class PhysBody;
class PhysicEntity;

enum class GameState
{
	INTRO,
	PLAYING,
	GAMEOVER
};

class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;
	void RestartBall();
	void StartGame();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;
	void OnCollisionEnd(PhysBody* bodyA, PhysBody* bodyB) override;

public:
	std::vector<PhysicEntity*> entities;

	ModulePhysics* physics = nullptr;

	Ball* ball = nullptr;
	Launcher* launcher = nullptr;
	Map* currentMap = nullptr;

	Texture2D ballTexture;
	Texture2D launcherTexture;
	Texture2D introTexture;
	Texture2D endTexture;

	Sound start;
	Sound gameOver;
	Sound music;

	Sound walls;
	Sound bumpers;
	Sound flippers;
	Sound voids;

private:
	int maxBalls = 5;
	int currentBalls = 0;

	bool restartBallFlag = false;

	GameState state = GameState::INTRO;
};
