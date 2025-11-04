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
};
