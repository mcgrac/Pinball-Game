#pragma once
#include "iostream"
#include "PhysicEntity.h"
#include "raylib.h"
#include <vector>
#include "Bumper.h"
#include "Flipper.h"
#include "Launcher.h"
#include "Ball.h"

using namespace std;

class Map {
public:

    virtual ~Map() {}

    virtual void Start() = 0;     // Construye el nivel
    virtual void Update() = 0;      // Opcional (animaciones)
    virtual void CleanUp() = 0;   // Libera memoria

    inline virtual vector<Flipper*>& GetFlippers() { static std::vector<Flipper*> empty; return empty; }
    inline virtual vector<Launcher*>& GetLaunchers() { static std::vector<Launcher*> empty; return empty; }

protected:

    // Cosas comunes que quieran los niveles:
    vector<PhysicEntity*> walls;
    vector<Bumper*> bumpers;
    vector<Flipper*> flippers;
    vector<Launcher*> launchers;

    PhysicEntity* sensorDown = nullptr;
};
