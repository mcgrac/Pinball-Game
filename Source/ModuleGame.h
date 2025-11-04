#pragma once

#include "Globals.h"
#include "Module.h"

#include "p2Point.h"

#include "Ball.h"
#include"Launcher.h"
#include "Bumper.h"
#include"Flipper.h"
#include "raylib.h"
#include <vector>

#include "Map.h"
#include"Level1.h"

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

	bool Start();
	update_status Update();
	bool CleanUp();
	void RestartBall();
	void StartGame();
	void ResetGame();

	ModulePhysics* physics = nullptr;
	//PhysBody* ball = nullptr;
	PhysBody* launcherBase = nullptr;
	PhysBody* launcherPlunger = nullptr;

	Ball* ball;
	//Launcher* launcher;
	//Flipper* leftFlipper;
	//Flipper* rightFlipper;

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;
	void OnCollisionEnd(PhysBody* bodyA, PhysBody* bodyB) override;

	Map* currentMap = nullptr;

	std::vector<PhysicEntity*> entities;

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

	bool fixtureChanged = false;

	bool restartBallFlag = false;
	GameState state = GameState::INTRO;

	Texture2D introTexture;
	Texture2D endTexture;
};
