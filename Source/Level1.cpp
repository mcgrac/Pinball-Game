#include "iostream"
#include "Level1.h"
#include "PhysicEntity.h"
#include "raylib.h"

Level1::Level1(ModulePhysics* _physics, Module* _listener, Ball* _ball)
{
	this->physics = _physics;
	this->listener = _listener;
	this->ball = _ball;
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
	548, 193,
	530, 168,
	501, 140,
	469, 118,
	435, 103,
	392, 90,
	347, 85,
	298, 86,
	247, 96,
	194, 116,
	156, 140,
	127, 170,
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
	walls.push_back(new PhysicEntity(physics->CreateChain(0, 0, backgroundExternal, 228, b2_staticBody), listener, ColliderType::WALL));

	int backgroundInternal[118] = {
		428, 256,
	446, 227,
	462, 203,
	468, 196,
	479, 188,
	467, 174,
	447, 160,
	427, 149,
	407, 139,
	380, 131,
	353, 128,
	321, 127,
	292, 128,
	265, 134,
	242, 144,
	218, 157,
	197, 172,
	180, 187,
	163, 207,
	151, 228,
	145, 258,
	146, 292,
	152, 319,
	166, 341,
	186, 373,
	201, 400,
	213, 419,
	214, 424,
	211, 428,
	207, 426,
	200, 415,
	175, 374,
	153, 336,
	141, 311,
	134, 278,
	137, 250,
	145, 221,
	160, 196,
	179, 175,
	203, 157,
	229, 142,
	261, 128,
	288, 122,
	319, 120,
	353, 121,
	384, 125,
	418, 136,
	443, 149,
	470, 168,
	484, 181,
	493, 190,
	488, 193,
	479, 199,
	467, 212,
	427, 277,
	422, 283,
	417, 283,
	415, 277,
	419, 270
	};
	walls.push_back(new PhysicEntity(physics->CreateChain(0, 0, backgroundInternal, 118, b2_staticBody), listener, ColliderType::WALL));

	int leftTriangle[16] = {
	224, 831,
	235, 830,
	242, 819,
	204, 721,
	195, 714,
	185, 719,
	146, 768,
	147, 778
	};
	walls.push_back(new PhysicEntity(physics->CreatePolygon(0, 0, leftTriangle, 16, b2_staticBody), listener, ColliderType::WALL));

	int rightTriangle[16] = {
	386, 831,
	375, 827,
	372, 815,
	410, 719,
	418, 713,
	427, 716,
	469, 766,
	468, 778
	};
	walls.push_back(new PhysicEntity(physics->CreatePolygon(0, 0, rightTriangle, 16, b2_staticBody), listener, ColliderType::WALL));

	//Bumpers creation
	bumpers.push_back(new Bumper(physics, 242, 554, listener, bumpersText, b2_staticBody, ColliderType::BUMPER, 30));
	bumpers.push_back(new Bumper(physics, 377, 554, listener, bumpersText, b2_staticBody, ColliderType::BUMPER, 30));
	bumpers.push_back(new Bumper(physics, 312, 447, listener, bumpersText, b2_staticBody, ColliderType::BUMPER, 30));

	//flippers creation
	int leftFlipperCords[16] = {
		-27, 24,
		-1, 49,
		-2, 54,
		-7, 57,
		-63, 31,
		-68, 21,
		-53, 2,
		-43, 5
	};
	flippers.push_back(new Flipper(physics, 275, 835, true, listener, leftFlipper, b2_kinematicBody, ColliderType::FLIPPER, leftFlipperCords));
	int rightFlipperCords[16] = {
		27, 24,
		1, 49,
		2, 54,
		7, 57,
		63, 31,
		68, 21,
		53, 2,
		43, 5
	};
	flippers.push_back(new Flipper(physics, 338, 835, false, listener, rightFlipper, b2_kinematicBody, ColliderType::FLIPPER, rightFlipperCords));

	//launcher creation
	launchers.push_back(new Launcher(physics, ball, 550, 900, 50, 20, listener, launcherText, ColliderType::LAUNCHER));

	sensorDown = new PhysicEntity(physics->CreateRectangleSensor(0, 1009, 648, 10, b2_staticBody), listener, ColliderType::VOID);
	sensorDown->GetBody()->entity = sensorDown;
}

void Level1::CleanUp()
{
    // Eliminar paredes, etc...

	for (PhysicEntity* p : walls)
	{
		delete p; // o como sea tu wrapper
	}

	walls.clear();

	for (Bumper* b : bumpers)
	{
		delete b;
	}
	bumpers.clear();

	delete sensorDown;

}

void Level1::Update() {

	DrawTexture(background, 0, 0, WHITE);

	for (Bumper* b : bumpers)
	{
		if (b != nullptr)
			b->Update();
		else
			cout << "Bumper NULLPTR" << endl;
	}

	for (Launcher* l : launchers) {
		if (l != nullptr)
			l->Update();
		else
			cout << "Launcher NULLPTR" << endl;
	}

	//for (Flipper* f : flippers) {
	//	if (f != nullptr)
	//	{
	//		f->Update();
	//		//cout << "Flipper NO NULLPTR" << endl;
	//	}
	//	else
	//		cout << "Flipper NULLPTR" << endl;
	//}
}


