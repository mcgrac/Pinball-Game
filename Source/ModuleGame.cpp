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
	scoreTracker = new ScoreTracker(0, 0.5, 1);

	// Load intro and end textures
	introTexture = LoadTexture("Assets/Textures/initialScreen.png");
	endTexture = LoadTexture("Assets/Textures/endScreen.png");
	
	// Load Main Sounds
	start = LoadSound("Assets/Sounds/start.wav");
	gameOver = LoadSound("Assets/Sounds/gameOver.wav");;
	music = LoadSound("Assets/Sounds/music.wav");;
	//Load Collision Sounds
	walls = LoadSound("Assets/Sounds/walls.wav");;
	bumpers = LoadSound("Assets/Sounds/bumpers.wav");;
	flippers = LoadSound("Assets/Sounds/flippers.wav");;
	voids = LoadSound("Assets/Sounds/voids.wav");;

	currentBalls = 0; //restart balls

	PlaySound(start);

	return ret;
}

void ModuleGame::StartGame()
{
	scoreTracker = new ScoreTracker(0, 0.5, 1);

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

	delete scoreTracker;
	scoreTracker = nullptr;

}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	UnloadTexture(introTexture);
	UnloadTexture(endTexture);

	UnloadSound(start);
	UnloadSound(gameOver);
	UnloadSound(music);

	UnloadSound(walls);
	UnloadSound(bumpers);
	UnloadSound(flippers);
	UnloadSound(voids);

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
			StopSound(start);
			PlaySound(music);
			StartGame();
		}

		return UPDATE_CONTINUE;
	}
	case GameState::PLAYING:
	{
		//For testing
		//if (IsKeyPressed(KEY_E)) {

		//	if (scoreTracker->score > highScore) {
		//		highScore = scoreTracker->score;
		//	}

		//	state = GameState::GAMEOVER;
		//	StopSound(music);
		//}

		if (currentBalls <= maxBalls)
		{
			for (Launcher* l : currentMap->GetLaunchers()) {
				if (IsKeyDown(KEY_DOWN))
				{
					l->Press(dt); // baja el lanzador
				}

				if (IsKeyReleased(KEY_DOWN))
				{
					l->Release(); // suelta la bola
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
			for (Bumper* b : currentMap->GetSpecialBumpers())
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

			//change bounciness of bumpers
			if (IsKeyPressed(KEY_F5)) 
			{ 
				fixtureChanged = !fixtureChanged;

				if (!fixtureChanged) { //normal restitution
					for (Bumper* b : currentMap->GetSpecialBumpers())
					{
						b->GetBody()->GetB2Body()->GetFixtureList()->SetRestitution(1.2f);
					}
					for (Bumper* b : currentMap->GetBumpers())
					{
						b->GetBody()->GetB2Body()->GetFixtureList()->SetRestitution(1.2f);
					}
				}
				else if (fixtureChanged) { //alternative restitution
					cout << "changed restitution" << endl;

					for (Bumper* b : currentMap->GetSpecialBumpers())
					{
						b->GetBody()->GetB2Body()->GetFixtureList()->SetRestitution(0.5f);
					}
					for (Bumper* b : currentMap->GetBumpers())
					{
						b->GetBody()->GetB2Body()->GetFixtureList()->SetRestitution(0.5f);
					}
				}
			}

			//manage the score and Score meter
			ManageScore();
			//Gameplay Controls
			DrawText(TextFormat("Number of used balls: %d", currentBalls), 300, 60, 20, RED);

			if (restartBallFlag)
				RestartBall();
		}
		else
		{
			StopSound(music);
			PlaySound(gameOver);

			//update highscore
			if (scoreTracker->score > highScore) {
				highScore = scoreTracker->score;
			}

			state = GameState::GAMEOVER;
		}
		break;
	}
	case GameState::GAMEOVER:
	{
		App->physics->SetDebug(false);

		DrawTexture(endTexture, 0, 0, WHITE);
		DrawText(TextFormat("%06i points", scoreTracker->score), 250, 550, 20, WHITE);
		DrawText(TextFormat("High Score: %06i points", highScore), 200, 570, 20, WHITE);
		DrawText(TextFormat("Previous score: %06i points", previousScore), 200, 590, 20, WHITE);

		if (IsKeyPressed(KEY_SPACE))
		{
			previousScore = scoreTracker->score;
			StopSound(gameOver);
			ResetGame();
			PlaySound(start);
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

void ModuleGame::ManageScore() {
	scoreTracker->UpdateScore();
	scoreTracker->PrintScore(highScore);
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

		PlaySound(bumpers);
	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::VOID)
	{
		PlaySound(voids);
		restartBallFlag = true;
		scoreTracker->PauseTracker();
		cout << "VoidCollision START" << endl;

	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::WALL)
	{
		cout << "Colliding WALLS" << endl;
		PlaySound(walls);

	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::FLIPPER)
	{
		PlaySound(flippers);

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
		if (scoreTracker->paused) {
			scoreTracker->paused = false;
		}
		scoreTracker->BumperHit();
		cout << "BumperCollision END" << endl;

	}
	else if (other->entity && other->entity->GetColliderType() == ColliderType::VOID)
	{
		cout << "VoidCollision END" << endl;

	}
}
