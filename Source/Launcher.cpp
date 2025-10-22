#include "Launcher.h"
//#include "App.h"
//#include "Input.h"


Launcher::Launcher(ModulePhysics* physics, Ball* ball, int _x, int _y, int _width, int _heigh, Module* _listener, Texture2D _texture, b2BodyType _type)
    : PhysicEntity(physics->CreateRectangle(_x, _y, _width, _heigh, b2_staticBody), listener)
{
    this->ball = ball;
    initialY = _y;
}
Launcher::~Launcher()
{
}

void Launcher::Press()
{
    if (!isPressed)
    {
        isPressed = true;
        pressStartTime = GetTime(); // Raylib: obtiene el tiempo en segundos
    }
}

void Launcher::Release()
{
    if (isPressed)
    {
        isPressed = false;

        // Calcular cuánto tiempo estuvo presionado
        float heldTime = GetTime() - pressStartTime;
        float power = heldTime * chargeSpeed;

        // Limitar a una fuerza máxima
        if (power > maxPower)
            power = maxPower;

        // Restablecer posición
        body->SetPosition(body->GetPositionX(), initialY);

        // Aplicar impulso a la bola
        if (ball != nullptr)
        {
            b2Body* ballBody = ball->GetBody()->GetB2Body();
            if (ballBody != nullptr)
                ballBody->ApplyLinearImpulseToCenter(b2Vec2(0, -power), true);
        }
    }
}

void Launcher::Update()
{
    if (isPressed)
    {
        int newY = body->GetPositionY() + 3; // baja lentamente
        if (newY < initialY + maxOffset)
            body->SetPosition(body->GetPositionX(), newY);
    }
}