#include "iostream"
#include "Level1.h"
#include "PhysicEntity.h"
#include "raylib.h"

//using namespace std;
//
//vector<Vector2> positions;
//
//
//Level1::Level1() {
//	//ModulePhysics::CreateChain(0, 0);
//	Level1::obstacles = {}; //tots els objectes del nivell
//	ballPosition = { 0, 0 };
//}


Level1::Level1(ModulePhysics* _physics)
{
	this->physics = _physics;
}

Level1::~Level1()
{}

void Level1::Start()
{
    // Crear paredes, bumpers, etc...
	cout << "START LEVEL 1" << endl;
	background = LoadTexture("Assets/Textures/background.png");

	int backgroundExternal[228] = {
	526, 976,
	566, 976,
	567, 249,
	558, 216,
	543, 191,
	524, 164,
	502, 144,
	469, 120,
	436, 105,
	397, 94,
	348, 86,
	298, 86,
	247, 96,
	194, 116,
	158, 141,
	130, 168,
	106, 202,
	95, 233,
	90, 266,
	92, 304,
	106, 336,
	126, 370,
	150, 412,
	169, 446,
	174, 456,
	174, 464,
	169, 475,
	155, 494,
	126, 530,
	116, 540,
	112, 551,
	114, 561,
	118, 569,
	127, 582,
	142, 602,
	155, 622,
	161, 631,
	166, 640,
	164, 649,
	156, 665,
	144, 680,
	129, 702,
	112, 730,
	112, 848,
	286, 949,
	288, 956,
	290, 1020,
	283, 1019,
	283, 956,
	105, 856,
	105, 725,
	158, 643,
	98, 554,
	165, 463,
	87, 318,
	81, 248,
	104, 182,
	149, 132,
	222, 93,
	307, 74,
	388, 78,
	453, 96,
	504, 128,
	550, 177,
	576, 249,
	577, 430,
	577, 985,
	518, 984,
	519, 268,
	516, 250,
	512, 242,
	500, 247,
	452, 323,
	451, 462,
	510, 538,
	514, 552,
	511, 561,
	458, 637,
	460, 648,
	508, 722,
	513, 730,
	514, 856,
	336, 954,
	336, 1018,
	326, 1018,
	326, 956,
	328, 950,
	335, 945,
	496, 857,
	502, 853,
	505, 843,
	505, 740,
	503, 729,
	453, 654,
	450, 643,
	451, 634,
	503, 560,
	506, 554,
	504, 546,
	449, 475,
	444, 468,
	443, 459,
	441, 330,
	442, 321,
	446, 313,
	493, 242,
	499, 236,
	507, 231,
	517, 229,
	520, 235,
	523, 245,
	526, 261,
	526, 275,
	525, 960
	};

	walls.push_back(physics->CreateChain(0, 0, backgroundExternal, 228, b2_staticBody));
}

void Level1::CleanUp()
{
    // Eliminar paredes, etc...

	for (auto w : walls)
	{
		physics->DestroyPhysBody(w); // o como sea tu wrapper
	}

	walls.clear();
}

void Level1::Update() {

	cout << "Update level 1" << endl;
	DrawTexture(background, 0, 0, WHITE);
}


