#pragma once
#include"PhysicEntity.h"

class Ball : public PhysicEntity
{
public:
	Ball(ModulePhysics* physics, int _x, int _y, Module* _listener, b2BodyType _type, ColliderType _collType);
	~Ball();

	void Update() override;

	inline void OnLauncherCollision(bool res) {isTouchingLauncher = res; };
	inline bool GetTouchingLauncher() { return isTouchingLauncher; }

private:
	Texture2D texture;
	bool isTouchingLauncher = false;
};