#include "iostream"
#include "Level1.h"
#include "PhysicEntity.h"
#include "raylib.h"

using namespace std;

vector<Vector2> positions;


Level1::Level1() {
	//ModulePhysics::CreateChain(0, 0);
	Level1::obstacles = {}; //tots els objectes del nivell
	ballPosition = { 0, 0 };
}


