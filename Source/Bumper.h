#pragma once
#include"PhysicEntity.h"
class Bumper : public PhysicEntity
{
public:
	Bumper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType, float _radious, bool _isSpecial);
	~Bumper();
	void Update() override;

	inline void HasBeenTouched(bool res) { isTouched = res; }

	inline bool GetIsTouched() { return isTouched; }
	inline bool GetIsSpecial() { return isScpecial; }
private:
	Texture2D texture;

	bool isScpecial = false;
	bool isTouched = false;
};
