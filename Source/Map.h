#pragma once
#include "iostream"
#include "PhysicEntity.h"
#include "raylib.h"
#include <vector>

using namespace std;
//class Map {
//public:
//	Map();
//
//	~Map();
//
//	vector<PhysicEntity*> obstacles;
//	Vector2 ballPosition;
//protected:
//	//PhysicEntity* createOutline(Vector2 pos0, Vector2* points, int size);
//};

class Map {
public:

    virtual ~Map() {}

    virtual void Start() = 0;     // Construye el nivel
    virtual void Update() {}      // Opcional (animaciones)
    virtual void CleanUp() = 0;   // Libera memoria

protected:
    // Cosas comunes que quieran los niveles:
    vector<PhysBody*> walls;
    vector<PhysBody*> bumpers;
    vector<PhysBody*> decorations;
    vector<PhysBody*> obstacles;
};
