#include "ScoreTracker.h"


ScoreTracker::ScoreTracker(int initialScore, double frequency, int amount) {
	this->score = initialScore;
	this->Frequency = frequency;
	this->amount = amount;
	timer = new Timer();
	timer->Start();
	lastUpdate = timer->ReadSec();
}
ScoreTracker::~ScoreTracker(){
	delete timer;
}
void ScoreTracker::UpdateScore() {
	if (timer->ReadSec() - Frequency >= lastUpdate) {
		score += amount;
		lastUpdate = timer->ReadSec();
	}
}
void ScoreTracker::PrintScore() {
	DrawText(TextFormat("Score: %06i points", score), 300, 20, 20, RED);
}