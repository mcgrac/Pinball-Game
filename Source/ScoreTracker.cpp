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
ScoreTracker::~ScoreTracker(){
	delete timer;
}
void ScoreTracker::UpdateScore() {
	if (paused == false) {
		if (timer->ReadSec() - Frequency >= lastUpdate) {
			score += amount;
			lastUpdate = timer->ReadSec();
		}
	}
}
void ScoreTracker::PrintScore() {
	DrawText(TextFormat("Score: %06i points", score), 300, 20, 20, RED);
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