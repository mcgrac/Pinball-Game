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

    body->GetB2Body()->SetGravityScale(0.0f);
    body->ctype = ColliderType::LAUNCHER;

    texture = LoadTexture("Assets/Textures/launcher.png");
}
Launcher::~Launcher()
{
    UnloadTexture(texture);
}

void Launcher::Press(float dt)
{
    //std::cout << "isLauncherPressed" << std::endl;

    isCharging = true;
    returning = false;
    body->GetB2Body()->SetLinearVelocity(b2Vec2(0, speedDown));
}

void Launcher::Release()
{
    // convertimos la carga en un impulso inicial
    float launchPower = charge * .5f; // multiplica para ajustar fuerza

    // sube rápido según carga acumulada
    body->GetB2Body()->SetLinearVelocity(b2Vec2(0, -launchPower));

    // aplica impulso a la bola
    if (ball->GetTouchingLauncher()) {
        ball->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0, -launchPower * 2), true);
    }

    isCharging = false;
    returning = true;
}

void Launcher::Update(float dt)
{
    //Draw
    int x, y;
    body->GetPhysicPosition(x, y);
    Vector2 position{ (float)x, (float)y };
    float scale = 1.0f;
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle dest = { position.x, position.y, (float)texture.width * scale, (float)texture.height * scale };
    Vector2 origin = { (float)texture.width / 2.0f, (float)texture.height / 2.0f };
    float rotation = body->GetRotation() * RAD2DEG;

    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

    float y_phys = body->GetPositionY();
    if (isCharging)
    {
        if (y_phys < initialY + maxOffset)
        {
            body->GetB2Body()->SetLinearVelocity(b2Vec2(0, speedDown));
            charge += chargeRate;
            if (charge > maxCharge) charge = maxCharge;
        }
        else
        {
            body->GetB2Body()->SetLinearVelocity(b2Vec2(0, 0));
        }
    }
    else if (returning)
    {
        if (y_phys > initialY)
        {
            float upSpeed = -speedUp * (charge / maxCharge); // negativo porque sube

/*            std::cout << "charge rate: " << charge/maxCharge << std::endl;
            std::cout << "charge: " << charge << std::endl;
            std::cout << "uSpeed: " << upSpeed << std::endl*/;

            body->GetB2Body()->SetLinearVelocity(b2Vec2(0, upSpeed));
        }
        else
        {
            body->GetB2Body()->SetLinearVelocity(b2Vec2(0, 0));
            body->SetPosition(body->GetPositionX(), initialY);
            returning = false;
            charge = 0;
        }
    }
    else
    {
        body->GetB2Body()->SetLinearVelocity(b2Vec2(0, 0));
        returning = false;
        isCharging = false;
    }
}