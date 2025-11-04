#pragma once
#include "iostream"
#include "PhysicEntity.h"
#include "Timer.h"
#include "raylib.h"
class ScoreTracker
{
public:
	ScoreTracker(int initialScore, double frequancy, int amount);
	~ScoreTracker();
	void UpdateScore();
	void PrintScore(int highScore);
	void PauseTracker();
	void ResumeTracker();
	void BumperHit();
	bool paused = true;
	int score;
	Timer* timer;
	double Frequency;
	int amount;
	double lastUpdate;
<<<<<<< HEAD

	bool firstMile = false;
	Sound firstMilestone = LoadSound("Assets/Sounds/points1.wav");
	bool secondMile = false;
	Sound secondMilestone = LoadSound("Assets/Sounds/points2.wav");
	bool thirdMile = false;
	Sound thirdMilestone = LoadSound("Assets/Sounds/points3.wav");
=======
>>>>>>> e30fad6803b8a76164b31fa5542244c1f9c00051
};
