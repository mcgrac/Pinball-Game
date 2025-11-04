#pragma once
#include"PhysicEntity.h"
#include "iostream"

class Flipper : public PhysicEntity
{
public:

	Flipper(ModulePhysics* physics, int _x, int _y, bool _isLeft,Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType, int* points);
	~Flipper();

	void Update() override;

	void Press();
	void Release();

	inline bool IsLeft() { return isLeft; }

private:

	b2RevoluteJoint* joint = nullptr;
	bool isLeft = false;
	Texture2D texture{};

	int* points = nullptr;
	Vector2 pivotLocalPx{ 0,0 };
	Vector2 texOriginPx{ 0,0 };
};
