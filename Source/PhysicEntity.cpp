#include "PhysicEntity.h"
PhysicEntity::PhysicEntity(PhysBody* _body, Module* _listener, ColliderType _collType)
	: body(_body)
	, listener(_listener), ctype(_collType)
{
	//body->ctype = _collType;
	body->listener = _listener; // quién recibe BeginContact
}
PhysicEntity::~PhysicEntity() {

	//destroy bodies
    if (body != nullptr)
    {
        b2World* world = body->GetB2Body()->GetWorld();
        world->DestroyBody(body->GetB2Body());
        body = nullptr;
    }
};

void PhysicEntity::Update() {

}