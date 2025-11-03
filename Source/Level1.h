#pragma once
#include "Map.h"

class Level1 : public Map {
public:
    Level1(ModulePhysics* physics, Module* _listener);
    ~Level1();

    void Start() override;
    void Update() override;
    void CleanUp() override;

    inline vector<Flipper*>& GetFlippers() override { return flippers; }
    inline vector<Launcher*>& GetLaunchers() override { return launchers; }

private:
    ModulePhysics* physics;
    Module* listener; // listener for everithing

    Texture2D background;
    Texture2D bumpersText;
    Texture2D leftFlipper;
    Texture2D rightFlipper;
};