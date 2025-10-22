#pragma once

#include "Module.h"
#include "Globals.h"

#include "box2d\box2d.h"

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : body(NULL)
	{}

	void GetPhysicPosition(int& x, int& y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

	// Obtener posición en píxeles
	b2Vec2 GetPosition() const;

	float GetPositionX() const { return GetPosition().x; }
	float GetPositionY() const { return GetPosition().y; }

	// Establecer posición (pasando píxeles)
	void SetPosition(float xPixels, float yPixels);

	// Obtener acceso al cuerpo Box2D
	b2Body* GetB2Body() const;

	// Aplicar impulso lineal al centro
	void ApplyLinearImpulseToCenter(b2Vec2 impulse, bool wake = true);

public:
	int width, height;
	b2Body* body;
	// TODO 6: Add a pointer to a module that might want to listen to a collision from this body
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	void GetPhysicPosition(int& x, int& y) const;
	float GetRotation() const;

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType type);
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType type);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, const int* points, int size);

	b2World* GetWorld() const { return world; }  // Devuelve el puntero al mundo físico


private:

	b2Vec2 gravity = { 0,9.81f };
	b2World* world = nullptr;
	bool debug;
	
};