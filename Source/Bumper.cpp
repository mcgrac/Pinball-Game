#include"Bumper.h"
Bumper::Bumper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType, float _radious, bool _isSpecial)
	: PhysicEntity(physics->CreateCircle(_x, _y, _radious, _type), _listener, _collType)
	, texture(_texture), isScpecial(_isSpecial)
{
	body->entity = this;

	b2Fixture* fix = body->GetB2Body()->GetFixtureList();
	fix->SetRestitution(1.2f);
}
Bumper::~Bumper() {}

void Bumper::Update() {
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