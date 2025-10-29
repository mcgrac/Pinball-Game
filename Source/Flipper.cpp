#include"Flipper.h"

Flipper::Flipper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType)
	: PhysicEntity(physics->CreateCircle(_x, _y, 25, _type), _listener, _collType), texture(_texture)
{
	body->entity = this;
}
Flipper::~Flipper(){}