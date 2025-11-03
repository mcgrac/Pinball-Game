#include "Flipper.h"


Flipper::Flipper(ModulePhysics* physics, int _x, int _y, bool _isLeft, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType, int* _points)
	: PhysicEntity(physics->CreatePolygon(_x, _y, _points, 12, b2_dynamicBody), _listener, _collType), texture(_texture)
{
	this->isLeft = _isLeft;
	body->entity = this;
    this->points = _points;


    // Obtener body dinámico real
    b2Body* b = body->GetB2Body();
    b->SetGravityScale(1.0f);

    // --- Pivote estático ---
    b2BodyDef pivotDef;
    pivotDef.type = b2_staticBody;
    pivotDef.position.Set(PIXEL_TO_METERS(_x), PIXEL_TO_METERS(_y));

    b2Body* pivot = physics->GetWorld()->CreateBody(&pivotDef);

    // --- Revolute Joint ---
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = pivot;
    jointDef.bodyB = b;

    jointDef.localAnchorA.Set(0, 0);
    jointDef.localAnchorB.Set(isLeft ? -0.45f : 0.45f, 0);

    jointDef.collideConnected = false;

    jointDef.enableLimit = true;
    if (isLeft)
    {
        jointDef.lowerAngle = -25 * DEGTORAD;
        jointDef.upperAngle = 15 * DEGTORAD;
    }
    else
    {
        jointDef.lowerAngle = -15 * DEGTORAD;
        jointDef.upperAngle = 25 * DEGTORAD;
    }

    jointDef.enableMotor = true;
    jointDef.motorSpeed = 0;
    jointDef.maxMotorTorque = 400.0f;

    joint = (b2RevoluteJoint*)physics->GetWorld()->CreateJoint(&jointDef);


}
Flipper::~Flipper() {}

void Flipper::Press()
{
    std::cout << "flipper pressed" << std::endl;
    float flipperSpeed = 20.0f;

    if (isLeft)
        joint->SetMotorSpeed(-flipperSpeed);
    else
        joint->SetMotorSpeed(flipperSpeed);
}

void Flipper::Release()
{
    std::cout << "flipper released" << std::endl;
    float flipperSpeed = 20.0f;

    if (isLeft)
        joint->SetMotorSpeed(flipperSpeed);
    else
        joint->SetMotorSpeed(-flipperSpeed);
}