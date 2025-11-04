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
	state = GameState::INTRO;

	// Load intro and end textures
	introTexture = LoadTexture("Assets/Textures/initialScreen.png");
	endTexture = LoadTexture("Assets/Textures/endScreen.png");
	


	//ball = new Ball(App->physics, 550, 800, this, b2_dynamicBody, ColliderType::BALL);
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

	////CREATION OF THE MAP LEVEL 1;
	//currentMap = new Level1(App->physics, this, ball);
	//currentMap->Start();
	return ret;
}

void ModuleGame::StartGame()
{
	// Reset counters
	currentBalls = 0;
	restartBallFlag = false;

	// Create objects only once space has been pressed
	ball = new Ball(App->physics, 550, 800, this, b2_dynamicBody, ColliderType::BALL);
	currentMap = new Level1(App->physics, this, ball);
	currentMap->Start();

	state = GameState::PLAYING;
}

void ModuleGame::ResetGame()
{
	// Limpia entidades del nivel anterior
	if (currentMap != nullptr)
	{
		currentMap->CleanUp();
		delete currentMap;
		currentMap = nullptr;
	}

	delete ball;
	ball = nullptr;

}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	UnloadTexture(introTexture);
	UnloadTexture(endTexture);

	return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
	float dt = GetFrameTime();

	switch (state)
	{
	case GameState::INTRO:
	{
		DrawTexture(introTexture, 0, 0, WHITE);

		if (IsKeyPressed(KEY_SPACE))
		{
			StartGame();
		}

		return UPDATE_CONTINUE;
	}
	case GameState::PLAYING:
	{
		//For testing
		if (IsKeyPressed(KEY_E)) {
			state = GameState::GAMEOVER;
		}
		if (currentBalls <= maxBalls)
		{
			//Gameplay Controls

			for (Launcher* l : currentMap->GetLaunchers()) {
				if (IsKeyDown(KEY_DOWN))
				{
					l->Press(dt); // baja el lanzador
				}

				if (IsKeyReleased(KEY_DOWN))
				{
					l->Release(dt); // suelta la bola
				}
			}

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

			currentMap->Update(dt);
			ball->Update();

			//specialBumpers logic
			bool allTouched = true;
			for (Bumper* b : currentMap->GetBumpers())
			{
				if (!b->GetIsTouched())
				{
					allTouched = false;
					break;
				}
			}

			if (allTouched)
			{
				currentBalls--; //adds one more ball to play

				//reset special bumpers touched to false
				for (Bumper* b : currentMap->GetBumpers())
				{
					b->HasBeenTouched(false);
				}
			}

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
		DrawTexture(endTexture, 0, 0, WHITE);

		if (IsKeyPressed(KEY_SPACE))
		{
			// cleanup current game
			//CleanUp();

			ResetGame();
			// go back to intro
			state = GameState::INTRO;
		}

		return UPDATE_CONTINUE;
	}
	}

	return UPDATE_CONTINUE;
}

void ModuleGame::RestartBall() {
	ball->GetBody()->SetPosition(550, 800);
	currentBalls++;
	restartBallFlag = false;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {

	//std::cout << "On Collision" << std::endl;
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
		// Intentamos castear a bumper
		Bumper* bumper = dynamic_cast<Bumper*>(other->entity);
		if (bumper != nullptr)
		{
			if (bumper->GetIsSpecial())
			{
				if (!bumper->GetIsTouched()) {
					bumper->HasBeenTouched(true);
					cout << "SPECIAL BUMPER ACTIVATED!" << endl;
				}
			}
			else
			{
				//no special bumper touched
			}
		}
	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::VOID)
	{
		restartBallFlag = true;
		cout << "VoidCollision START" << endl;

	}
}

void ModuleGame::OnCollisionEnd(PhysBody* bodyA, PhysBody* bodyB) {
	//std::cout << "On Collision End" << std::endl;

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
