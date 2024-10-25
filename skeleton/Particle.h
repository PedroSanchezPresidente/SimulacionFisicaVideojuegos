#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;
#define EULER

class Particle
{
public:

	Particle(Vector3 Pos, Vector3 Vel, Vector3 Scale, Vector3 Color, float Transparencia, PxShape* Shape, float LifeTime, float Radio, Vector3 Acc = Vector3(0, 0, 0), float Dumpling = 0.9) : 
		acc(Acc), vel(Vel), pose(Pos), posIni(Pos), dumpling(Dumpling), lifeTime(LifeTime), radio(Radio*Radio)
	{
		renderItem = new RenderItem;
		renderItem->shape = Shape;
		renderItem->color = Vector4(Color, Transparencia);
		renderItem->transform = &pose;
		RegisterRenderItem(renderItem);
	};
	~Particle() { DeregisterRenderItem(renderItem); delete renderItem; };

	virtual void integrade(double t);

	void setAcceleration(Vector3 Acc) {
		acc = Acc;
	}

	bool isAlive() { 
		if (lifeTime < 0 || (pose.p - posIni).magnitudeSquared() > radio)
			return false;
		else
			return true;
	};

	Vector3 getPos() { return pose.p; };

protected:
	float dumpling;
	Vector3 vel;
	Vector3 acc;
	PxTransform pose;
	Vector3 posIni;
	float lifeTime;
	float radio;
	RenderItem* renderItem;
};

