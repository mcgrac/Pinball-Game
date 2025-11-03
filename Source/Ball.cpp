#include"Ball.h"

Ball::Ball(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType)
	: PhysicEntity(physics->CreateBall(_x, _y, 15, _type), _listener, _collType)
	, texture(_texture)
{
	body->entity = this;

	texture = LoadTexture("Assets/Textures/ball.png");
}

Ball::~Ball() {
	UnloadTexture(texture);

}

void Ball::Update(){

	int x, y;
	body->GetPhysicPosition(x, y);
	Vector2 position{ (float)x, (float)y };
	float scale = 1.0f;
	Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle dest = { position.x, position.y, (float)texture.width * scale, (float)texture.height * scale };
	Vector2 origin = { (float)texture.width / 2.0f, (float)texture.height / 2.0f };
	float rotation = body->GetRotation() * RAD2DEG;

	DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}