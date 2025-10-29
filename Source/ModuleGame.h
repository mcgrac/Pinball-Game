#pragma once

#include "Globals.h"
#include "Module.h"

#include "p2Point.h"

#include "Ball.h"
#include"Launcher.h"
#include "Bumper.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class PhysicEntity;

class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();

	ModulePhysics* physics = nullptr;  
	//PhysBody* ball = nullptr;
	PhysBody* launcherBase = nullptr;
	PhysBody* launcherPlunger = nullptr;

	bool launcherCharging = false;
	float launcherPower = 0.0f;
	const float maxLauncherPower = 8.0f; // potencia máxima

	float launcherX = 1150.0f;
	float launcherY = 600.0f;

	Texture2D ballTexture;
	Texture2D launcherTexture;

	Ball* ball;
	Launcher* launcher;

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;
	void OnCollisionEnd(PhysBody* bodyA, PhysBody* bodyB) override;

public:
	std::vector<PhysicEntity*> entities;
	
};
