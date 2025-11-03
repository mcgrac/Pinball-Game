#pragma once
#include "Map.h"

//class Level1 : public Map {
//	Level1();
//};

class Level1 : public Map {
public:
    Level1(ModulePhysics* physics);
    ~Level1();

    void Start() override;
    void Update() override;
    void CleanUp() override;
private:
    ModulePhysics* physics;
    Texture2D background;
};