#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;

class Object{
public:
	Object(Vector3 Pos, float LifeTime, float Radio, float Masa, std::vector<int>* FGIndex = new std::vector<int>) : posIni(Pos), pose(Pos), lifeTime(LifeTime), radio(Radio* Radio), masa(Masa), vel({ 0,0,0 }), acc({ 0,0,0 }), forceGeneratorsIndex(FGIndex) {}

	Object(Vector3 Pos, float LifeTime, float Radio, Vector3 Vel, Vector3 Acc, float Masa, std::vector<int>* FGIndex = new std::vector<int>) : posIni(Pos), pose(Pos), lifeTime(LifeTime), radio(Radio* Radio), acc(Acc), vel(Vel), masa(Masa), forceGeneratorsIndex(FGIndex) {}

	void setVelocity(Vector3 v) { vel = v; }
	void setAcceleration(Vector3 a) { acc = a; }
	void setMasa(float m) { masa = m; }
	float getMasa() { return masa; }
	Vector3 getPos() { return pose.p; };
	Vector3 getVel() { return vel; };
	std::vector<int>* getForceGenerator() const { return forceGeneratorsIndex; };

protected:
	Vector3 vel;
	Vector3 acc;
	PxTransform pose;
	Vector3 posIni;
	float lifeTime;
	float radio;
	float masa;
	RenderItem* renderItem;
	std::vector<int>* forceGeneratorsIndex;
};