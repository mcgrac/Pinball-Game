#include "Flipper.h"

Flipper::Flipper(ModulePhysics* physics, int _x, int _y, bool _isLeft, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType)
	: PhysicEntity(physics->CreateRectangle(_x, _y, 60, 12, _type), _listener, _collType), texture(_texture)
{
	this->isLeft = _isLeft;
	body->entity = this;

    b2Body* b = body->GetB2Body();

    // Pivote (cuerpo estático)
    b2BodyDef pivotDef;
    pivotDef.type = b2_staticBody;
    pivotDef.position.Set(_x, _y);
    b2Body* pivot = physics->GetWorld()->CreateBody(&pivotDef);

    // Joint
    b2RevoluteJointDef jointDef;
    jointDef.Initialize(pivot, b, pivot->GetPosition());

    // Límites de giro
    jointDef.enableLimit = true;

    if (isLeft)
    {
        jointDef.lowerAngle = -25 * DEGTORAD;
        jointDef.upperAngle = 25 * DEGTORAD;
    }
    else
    {
        // invertimos
        jointDef.lowerAngle = -25 * DEGTORAD;
        jointDef.upperAngle = 25 * DEGTORAD;
    }

    // Motor
    jointDef.enableMotor = true;
    jointDef.maxMotorTorque = 200.0f;

    joint = (b2RevoluteJoint*)physics->GetWorld()->CreateJoint(&jointDef);
}
Flipper::~Flipper() {}