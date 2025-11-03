#pragma once
#include "iostream"
#include "PhysicEntity.h"
#include "raylib.h"
class Obstacle
{
public:
	Texture2D texture;
	PhysBody* obsBody;
	b2Shape* obsShape;

};

