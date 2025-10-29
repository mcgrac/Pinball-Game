#include "Flipper.h"

void Flipper::Activate()
{
	b2Vec2 impulse = b2Vec2(0.0f, -10.0f);
	body->GetB2Body()->ApplyLinearImpulseToCenter(impulse, true);
}

void Flipper::Deactivate()
{
	b2Vec2 impulse = b2Vec2(0.0f, 10.0f);
	body->GetB2Body()->ApplyLinearImpulseToCenter(impulse, true);
}

void Flipper::IsPressed()
{
	if (!isPressed)
	{
		Activate();
		isPressed = true;
	}
	else
	{
		Deactivate();
		isPressed = false;
	}
}