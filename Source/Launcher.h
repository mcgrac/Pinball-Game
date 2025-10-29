#pragma once
#include "PhysicEntity.h"
#include "Ball.h"
class Launcher : public PhysicEntity
{
public:
	Launcher(ModulePhysics* physics, Ball* ball, int _x, int _y, int _width, int _heigh, Module* _listener, Texture2D _texture, b2BodyType _type, ColliderType _collType);

	~Launcher();

	//void Update() override
	//{
	//	/*int x, y;
	//	body->GetPhysicPosition(x, y);
	//	DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
	//		Rectangle{ (float)x, (float)y, (float)texture.width, (float)texture.height },
	//		Vector2{ (float)texture.width / 2.0f, (float)texture.height / 2.0f }, body->GetRotation() * RAD2DEG, WHITE);*/
	//}

	void Update();          // mueve físicamente el launcher
	void Press();           // llamada cuando se mantiene pulsado ↓
	void Release();         // llamada cuando se suelta ↓

	int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal) override
	{
		return body->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);;
	}

private:
	Texture2D texture;

	Ball* ball = nullptr;

	bool isPressed = false;
	float initialY = 0.0f;
	float maxOffset = 100.0f;  // cuánto puede bajar

	float pressStartTime = 0.0f; // tiempo en que se empezó a presionar
	float maxPower = 25.0f;      // fuerza máxima
	float chargeSpeed = 10.0f;   // velocidad de carga del impulso

};
