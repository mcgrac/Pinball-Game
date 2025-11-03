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

	ball = new Ball(App->physics, 150, 200, this, ballTexture, b2_dynamicBody, ColliderType::BALL);
	//launcher = new Launcher(App->physics, ball, 200, 900, 50, 20, this, launcherTexture, ColliderType::LAUNCHER);
	

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

	leftFlipper = new Flipper(App->physics, 125, 800, true, this, leftFlipperTexture, b2_dynamicBody, ColliderType::FLIPPER, flipperLeftPoints);
	rightFlipper = new Flipper(App->physics, 275, 800, false, this, rightFlipperTexture, b2_dynamicBody, ColliderType::FLIPPER, flipperRightPoints);

	prueba = App->physics->CreateChain(100, 100, rightPoints, 16, b2_staticBody);

	
	return ret;
}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
	// === Input centralizado ===
	//if (IsKeyDown(KEY_DOWN))
	//{
	//	launcher->Press(); // baja el lanzador
	//}

	//if (IsKeyReleased(KEY_DOWN))
	//{
	//	launcher->Release(); // suelta la bola
	//}

	if (IsKeyDown(KEY_LEFT))
		leftFlipper->Press();
	else 
		leftFlipper->Release();

	if (IsKeyDown(KEY_RIGHT))
		rightFlipper->Press();
	else 
		rightFlipper->Release();


	// === Actualizar entidades ===
	//launcher->Update();
	ball->Update();
	return UPDATE_CONTINUE;
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


	}
}
