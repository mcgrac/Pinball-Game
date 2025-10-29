#pragma once
#include "iostream"
#include "PhysicEntity.h"
#include "raylib.h"
#include <vector>

using namespace std;
class Map {
public:
	Map();

	~Map();

	vector<PhysicEntity*> obstacles;
	Vector2 ballPosition;
protected:
	PhysicEntity* createOutline(Vector2 pos0, Vector2* points, int size);
};
