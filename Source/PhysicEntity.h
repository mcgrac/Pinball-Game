#pragma once
#include "ModulePhysics.h"
#include "p2Point.h"
#include "Globals.h"

class PhysicEntity
{
public:
	PhysicEntity(PhysBody* _body, Module* _listener, ColliderType _collType);
	virtual ~PhysicEntity();
	virtual void Update();

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
