#pragma once
#include "PhysicEntity.h"
#include "Ball.h"
class Launcher : public PhysicEntity
{
public:
	Launcher(ModulePhysics* physics, Ball* ball, int _x, int _y, int _width, int _heigh, Module* _listener, Texture2D _texture, ColliderType _collType);

	~Launcher();

	void Update(float dt);          
	void Press(float dt);           
	void Release();         
	inline bool OnBallCollision(bool res) { return onBallCollision = res; }

	int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal) override
	{
		return body->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);;
	}

	bool ballInside = false;

	inline bool GetIsCharging() { return isCharging; }
	inline bool GetReturning() { return returning; }
	
	inline void SetIsCharging(bool res) { isCharging = res; }
	inline void SetIsReturning(bool res) { returning = res; }

private:
	Texture2D texture;

	Ball* ball = nullptr;

	float pressStartTime = 0.0f; // tiempo en que se empezó a presionar
	float maxPower = 25.0f;      // fuerza máxima


	bool isCharging = false;
	bool returning = false;
	bool onBallCollision = false;

	float initialY = 0.0f;
	float maxOffset = 70.0f;  // hasta dónde baja
	float speedDown = 3.0f;   // lentito hacia abajo
	float speedUp = 20.0f;    // rápido hacia arriba

	float charge = 0.0f;
	float maxCharge = 15.0f;   // límite (ajústalo)
	float chargeRate = 0.5f;   // cuánto carga por frame (ajústalo)

};
