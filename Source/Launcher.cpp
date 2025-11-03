#include "Launcher.h"
//#include "App.h"
//#include "Input.h"
#include"iostream"


Launcher::Launcher(ModulePhysics* physics, Ball* ball, int _x, int _y, int _width, int _heigh, Module* _listener, Texture2D _texture, ColliderType _collType)
    : PhysicEntity(physics->CreateRectangle(_x, _y, _width, _heigh, b2_kinematicBody), _listener, _collType)
{
    this->ball = ball;
    body->entity = this;
    initialY = _y;
}
Launcher::~Launcher()
{
}

void Launcher::Press()
{
    std::cout << "isLauncherPressed" << std::endl;
    isCharging = true;
    returning = false;
    body->GetB2Body()->SetLinearVelocity(b2Vec2(0, speedDown));
}

void Launcher::Release()
{
    isCharging = false;
    returning = true;

    body->GetB2Body()->SetLinearVelocity(b2Vec2(0, -speedUp));
}

void Launcher::Update()
{
    float y = body->GetPositionY();
    std::cout << "Y = " << y << std::endl;



    // mientras cargas
    if (isCharging)
    {

        if (y >= initialY + maxOffset)
        {
            std::cout << "reset velocity" << std::endl;
            body->GetB2Body()->SetLinearVelocity(b2Vec2(0, 0));
        }
    }

    // cuando retorna
    if (returning)
    {
        if (y <= initialY)
        {
            std::cout << "reset velocity returning" << std::endl;
            body->GetB2Body()->SetLinearVelocity(b2Vec2(0, 0));
            body->SetPosition(body->GetPositionX(), initialY);
            returning = false;
        }
    }
}