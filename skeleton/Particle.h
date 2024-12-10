#pragma once
#include "Object.h"
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;
#define EULER

class Particle : public Object
{
public:

	Particle(Vector3 Pos, Vector3 Vel, Vector3 Scale, Vector3 Color, float Transparencia, PxShape* Shape, float LifeTime, float Radio, float Masa = 1, std::vector<int>* FGIndex = new std::vector<int>, Vector3 Acc = Vector3(0, 0, 0), float Dumpling = 0.9) :
		Object(Pos, LifeTime, Radio, Vel, Acc, Masa, FGIndex), dumpling(Dumpling)
	{
		renderItem = new RenderItem;
		renderItem->shape = Shape;
		renderItem->color = Vector4(Color, Transparencia);
		renderItem->transform = &pose;

		//renderItem = new RenderItem(Shape, &pose, Vector4(Color, Transparencia));

		RegisterRenderItem(renderItem);
	};
	~Particle() { DeregisterRenderItem(renderItem); };

	virtual void integrade(double t);

	bool isAlive() { 
		if (lifeTime < 0 || (pose.p - posIni).magnitudeSquared() > radio)
			return false;
		else
			return true;
	};

protected:
	float dumpling;
};

