#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "RigidSolid.h"
#include <list>
#include <vector>

using namespace physx;

class RigidSolidGenerator
{
public:
	RigidSolidGenerator(Vector3 Pos, Vector3 Color, PxShape* Shape, float Densidad, float Masa, float LifeTime, float Radio, PxScene* GScene, PxPhysics* GPhysics, float Rate, std::vector<int>* index) :
		numSR(0), pos(Pos), color(Color), shape(Shape), densidad(Densidad), lifeTime(LifeTime), radio(Radio), gScene(GScene), gPhysics(GPhysics), rate(Rate), timer(Rate), ForceGeneratorsIndex(index), masa(Masa){}

	void generateSR(std::list<RigidSolid*>& list, double t);

private:
	int numSR;
	Vector3 pos;
	Vector3 color;
	PxShape* shape;
	float densidad;
	float lifeTime;
	float radio;
	PxScene* gScene;
	PxPhysics* gPhysics;
	float timer;
	float rate;
	float masa;
	std::vector<int>* ForceGeneratorsIndex;
};

