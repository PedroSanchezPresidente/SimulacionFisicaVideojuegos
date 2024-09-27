#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel) : vel(Vel), pose(Pos) {
		renderItem = new RenderItem;
		PxSphereGeometry s;
		s.radius = 1;
		renderItem->shape = CreateShape(s);
		renderItem->color = Vector4(1, 0.753, 0.796, 1.0);
		renderItem->transform = &pose;
		RegisterRenderItem(renderItem);
	};
	~Particle() { DeregisterRenderItem(renderItem); delete renderItem; };

	void integrade(double t);

private:
	Vector3 vel;
	PxTransform pose;
	RenderItem* renderItem;
};

