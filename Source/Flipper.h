#pragma once
#include"PhysicEntity.h"
#include "iostream"

class Flipper : public PhysicEntity
{
public:

	Flipper(ModulePhysics* physics, int _x, int _y, bool _isLeft,Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType, int* points);
	~Flipper();

	void Update() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);
		Vector2 position{ (float)x, (float)y };
		float scale = 1.0f;
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { position.x, position.y, (float)texture.width * scale, (float)texture.height * scale };
		Vector2 origin = { (float)texture.width / 2.0f, (float)texture.height / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
	}

	void Press();
	void Release();

private:
	b2RevoluteJoint* joint;
	bool isLeft;

	Texture2D texture;
	int* points;
};
