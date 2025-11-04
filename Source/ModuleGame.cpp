#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

#include"iostream"


ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//physics = app->physics; // <-- Esto asegura que physics ya apunta al módulo correcto
}

ModuleGame::~ModuleGame()
{}

// Load assets
bool ModuleGame::Start()
{
	LOG("Loading Intro assets");

	bool ret = true;

	


	ball = new Ball(App->physics, 550, 800, this, ballTexture, b2_dynamicBody, ColliderType::BALL);
	//launcher = new Launcher(App->physics, ball, 550, 900, 50, 20, this, launcherTexture, ColliderType::LAUNCHER);

	//ball->SetBullet(true);

	int rightPoints[16] =
	{
		30, -8,
		 5, -8,
		 -12, -6,
		 -30, -2,
		 -30,  2,
		 -12,  6,
		 5,  8,
		30,  8
	};

	int flipperLeftPoints[12] = {
		 -40, -10,
		 40, -10,
		 50,  10,
		 -30,  10,
		 -35,   0,
		 -40,   0
	};

	int flipperRightPoints[12] = {
		40, -10,
		-40, -10,
		-50,  10,
		30,  10,
		35,   0,
		40,   0
	};

	//leftFlipper = new Flipper(App->physics, 125, 800, true, this, leftFlipperTexture, b2_dynamicBody, ColliderType::FLIPPER, flipperLeftPoints);
	//rightFlipper = new Flipper(App->physics, 275, 800, false, this, rightFlipperTexture, b2_dynamicBody, ColliderType::FLIPPER, flipperRightPoints);

	currentBalls = 0; //restart balls

	//CREATION OF THE MAP LEVEL 1;
	currentMap = new Level1(App->physics, this, ball);
	currentMap->Start();
	return ret;
}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	currentMap->CleanUp();
	delete currentMap;

	return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
	if (currentBalls <= maxBalls) {

		//=== Input centralizado ===

		for (Launcher* l : currentMap->GetLaunchers()) {
			if (IsKeyDown(KEY_DOWN))
			{
				l->Press(); // baja el lanzador
			}

			if (IsKeyReleased(KEY_DOWN))
			{
				l->Release(); // suelta la bola
			}
		}


		//if (IsKeyDown(KEY_LEFT))
		//	leftFlipper->Press();
		//else 
		//	leftFlipper->Release();

		//if (IsKeyDown(KEY_RIGHT))
		//	rightFlipper->Press();
		//else 
		//	rightFlipper->Release();

		for (Flipper* f : currentMap->GetFlippers())
		{
			if (IsKeyDown(KEY_LEFT) && f->IsLeft()) 
				f->Press();
			else if (f->IsLeft()) 
				f->Release();

			if (IsKeyDown(KEY_RIGHT) && !f->IsLeft()) 
				f->Press();
			else if (!f->IsLeft()) 
				f->Release();
		}


		// === Actualizar entidades ===
		//launcher->Update();
		currentMap->Update();
		ball->Update();
		//leftFlipper->Update();
		//rightFlipper->Update();

		if (restartBallFlag)
			RestartBall();

	}
	else {
		//FINISH GAME	
		cout << "GAME OVER" << endl;
		
	}

	return UPDATE_CONTINUE;
}

void ModuleGame::RestartBall() {
	ball->GetBody()->SetPosition(550, 800);
	currentBalls++;
	restartBallFlag = false;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {

	std::cout << "On Collision" << std::endl;
	// Detectar quién es la bola y quién es el otro
	PhysBody* ballBody = nullptr;
	PhysBody* other = nullptr;

	if (bodyA == ball->GetBody()) { ballBody = bodyA; other = bodyB; }
	else if (bodyB == ball->GetBody()) { ballBody = bodyB; other = bodyA; }
	else return;

	if (other->entity && other->entity->GetColliderType() == ColliderType::LAUNCHER)
	{
		//launcher->OnBallCollision(true); //ball collision launcher true
		ball->OnLauncherCollision(true);

	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::BUMPER)
	{
		cout << "BumperCollision START" << endl;

	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::VOID)
	{
		restartBallFlag = true;
		cout << "VoidCollision START" << endl;

	}
}

void ModuleGame::OnCollisionEnd(PhysBody* bodyA, PhysBody* bodyB) {
	std::cout << "On Collision End" << std::endl;

	// Detectar quién es la bola y quién es el otro
	PhysBody* ballBody = nullptr;
	PhysBody* other = nullptr;

	if (bodyA == ball->GetBody()) { ballBody = bodyA; other = bodyB; }
	else if (bodyB == ball->GetBody()) { ballBody = bodyB; other = bodyA; }
	else return;

	if (other->entity && other->entity->GetColliderType() == ColliderType::LAUNCHER)
	{
		//launcher->OnBallCollision(false); //ballCollision launcher false
		ball->OnLauncherCollision(false);
	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::BUMPER)
	{
		cout << "BumperCollision END" << endl;

	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::VOID)
	{
		cout << "VoidCollision END" << endl;

	}
}
