#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"


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

	ball = new Ball(App->physics, 200, 200, this, ballTexture, b2_dynamicBody);
	launcher = new Launcher(App->physics, ball, 200, 900, 50, 20, this, launcherTexture, b2_staticBody);
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
