#pragma once
#include "ModulePhysics.h"
#include "p2Point.h"
#include "Globals.h"

class PhysicEntity
{
protected:

	PhysicEntity(PhysBody* _body, Module* _listener, ColliderType _collType);

public:
	virtual ~PhysicEntity();
	virtual void Update() = 0;

	virtual int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal)
	{
		return 0;
	}
	inline PhysBody* GetBody() const { return body; }
	inline ColliderType GetColliderType() { return ctype; }

protected:
	PhysBody* body;
	Module* listener;
	ColliderType ctype;
};
