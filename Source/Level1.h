#pragma once
#include "Map.h"

class Level1 : public Map {
public:
    Level1(ModulePhysics* physics, Module* _listener, Ball* _ball);
    ~Level1();

    void Start() override;
    void Update(float dt) override;
    void CleanUp() override;

    inline vector<Flipper*>& GetFlippers() override { return flippers; }
    inline vector<Launcher*>& GetLaunchers() override { return launchers; }
    inline vector<Bumper*>& GetBumpers() override { return specialBumpers; }

private:
    ModulePhysics* physics;
    Module* listener; // listener for everithing
    Ball* ball;

    Texture2D background;
    Texture2D bumpersText;
    Texture2D leftFlipper;
    Texture2D rightFlipper;
    Texture2D launcherText;
};