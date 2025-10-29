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

	ball = new Ball(App->physics, 200, 200, this, ballTexture, b2_dynamicBody, ColliderType::BALL);
	launcher = new Launcher(App->physics, ball, 200, 900, 50, 20, this, launcherTexture, b2_staticBody, ColliderType::LAUNCHER);
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
	if (IsKeyDown(KEY_DOWN))
	{
		launcher->Press(); // baja el lanzador
	}

	if (IsKeyReleased(KEY_DOWN))
	{
		launcher->Release(); // suelta la bola
	}

    // === Actualizar entidades ===
    launcher->Update();
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

	if (other->entity && other->entity->GetColliderType() == ColliderType::BALL)
	{
		//launcher->SetBallInContact(true);
		std::cout << "Ball touching launcher" << std::endl;
		
	}
}

void ModuleGame::OnCollisionEnd(PhysBody* bodyA, PhysBody* bodyB) {
	std::cout << "On Collision End" << std::endl;
}
