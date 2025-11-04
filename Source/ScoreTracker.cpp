#include "ScoreTracker.h"


ScoreTracker::ScoreTracker(int initialScore, double frequency, int amount) {
	this->score = initialScore;
	this->Frequency = frequency;
	this->amount = amount;
	timer = new Timer();
	timer->Start();
	lastUpdate = timer->ReadSec();
	paused = true;
}
ScoreTracker::~ScoreTracker() {
	delete timer;
}
void ScoreTracker::UpdateScore() {
	if (paused == false) {
		if (timer->ReadSec() - Frequency >= lastUpdate) {
			score += amount;
			lastUpdate = timer->ReadSec();
		}
	}
	if (score >= 2000 && firstMile==false) {
		PlaySound(firstMilestone);
		firstMile = true;
	}
	if (score >= 5000 && secondMile == false) {
		PlaySound(firstMilestone);
		secondMile = true;
	}
	if (score >= 10000 && thirdMile == false) {
		PlaySound(firstMilestone);
		thirdMile = true;
	}
}
void ScoreTracker::PrintScore(int highScore) {
	DrawText(TextFormat("Score: %06i points", score), 300, 20, 20, RED);
	DrawText(TextFormat("High Score: %06i points", highScore), 300, 40, 20, RED);
}

/*void ScoreTracker::StartScoreTracker() {
	timer->Start();
	lastUpdate = timer->ReadSec();
	paused = false;
}*/

void ScoreTracker::PauseTracker() {
	paused = true;
}
void ScoreTracker::ResumeTracker() {
	paused = false;
}
void ScoreTracker::BumperHit() {
	score += 50;
}