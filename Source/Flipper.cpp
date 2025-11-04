#include "Flipper.h"


Flipper::Flipper(ModulePhysics* physics, int _x, int _y, bool _isLeft, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType, int* _points)
	: PhysicEntity(physics->CreatePolygon(_x, _y, _points, 16, b2_dynamicBody), _listener, _collType), texture(_texture)
{
	this->isLeft = _isLeft;
	body->entity = this;
    this->points = _points;
    if (isLeft) { texture = LoadTexture("Assets/Textures/leftFlipper.png"); }
    else{ texture = LoadTexture("Assets/Textures/rightFlipper.png"); }
   
    float best1 = isLeft ? -1e9f : 1e9f;  int i1 = -1;
    float best2 = isLeft ? -1e9f : 1e9f;  int i2 = -1;

    auto consider = [&](int idx, float x) {
        if (isLeft) {
            if (x > best1) { best2 = best1; i2 = i1; best1 = x; i1 = idx; }
            else if (x > best2) { best2 = x; i2 = idx; }
        }
        else {
            if (x < best1) { best2 = best1; i2 = i1; best1 = x; i1 = idx; }
            else if (x < best2) { best2 = x; i2 = idx; }
        }
        };

    for (int i = 0; i < 16; i += 2) {
        consider(i, static_cast<float>(points[i]));
    }


    pivotLocalPx.x = (points[i1] + points[i2]) * 0.5f;
    pivotLocalPx.y = (points[i1 + 1] + points[i2 + 1]) * 0.5f;


    float minx = 1e9f, maxx = -1e9f, miny = 1e9f, maxy = -1e9f;
    for (int i = 0; i < 16; i += 2) {
        float x = static_cast<float>(points[i]);
        float y = static_cast<float>(points[i + 1]);
        if (x < minx) minx = x; if (x > maxx) maxx = x;
        if (y < miny) miny = y; if (y > maxy) maxy = y;
    }
    float w = (maxx - minx); if (w < 1.0f) w = 1.0f;
    float h = (maxy - miny); if (h < 1.0f) h = 1.0f;

    float u = (pivotLocalPx.x - minx) / 0.5;
    float v = (pivotLocalPx.y - miny) / 0.5;
    texOriginPx = { u * texture.width, v * texture.height };

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

void Flipper::Update()
{
    //draw texture
    //int x, y;
    //body->GetPhysicPosition(x, y);
    //Vector2 position{ (float)x, (float)y };
    //float scale = 1.0f;
    //Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    //Rectangle dest = { position.x, position.y, (float)texture.width * scale, (float)texture.height * scale };
    ////Vector2 origin = { (float)texture.width / 2.0f, (float)texture.height / 2.0f };

    //Vector2 origin;
    //if (isLeft)
    //    origin = { 0.0f, (float)texture.height };   // esquina inferior izquierda
    //else
    //    origin = { (float)texture.width, (float)texture.height }; // esquina inferior derecha

    //float rotation = body->GetRotation() * RAD2DEG;
    //DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

    b2Vec2 pos = body->GetB2Body()->GetPosition();
    float angle = body->GetB2Body()->GetAngle() * RAD2DEG;

    Vector2 position = { METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y) };

    Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dest = { position.x, position.y, (float)texture.width, (float)texture.height };

    Vector2 origin;
    if (isLeft)
        origin = { texture.width * 1.0f, texture.height * 0.0f };
    else
        origin = { texture.width * 0.0f, texture.height * 0.0f };

    DrawTexturePro(texture, src, dest, origin, angle, WHITE);
}