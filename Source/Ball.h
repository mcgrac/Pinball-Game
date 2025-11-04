#pragma once
#include"PhysicEntity.h"

class Ball : public PhysicEntity
{
public:
	Ball(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType);
	~Ball();

	void Update() override;

private:
	Texture2D texture;

};