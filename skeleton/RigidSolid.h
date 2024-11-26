#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;

class RigidSolid {
public:
	RigidSolid(Vector3 Pos, Vector3 Color, float Radio, float LifeTime, PxScene* gScene, PxPhysics* gPhysics) : pose(Pos), lifeTime(LifeTime), masa(1), vel({ 0,0,0 }), acc({0,0,0}) {

		PxBoxGeometry b;
		b.halfExtents = { Radio,Radio,Radio };
		PxShape* shape = CreateShape(b);

		PxRigidDynamic* new_solid;
		new_solid = gPhysics->createRigidDynamic(pose);
		new_solid->setLinearVelocity(vel);
		new_solid->setAngularVelocity({0,0,0});
		new_solid->attachShape(*shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
		gScene->addActor(*new_solid);

		dynamic_item = new RenderItem(shape, new_solid, { Color, 1 });
	}

	void setVelocity(Vector3 v) { vel = v; }
	void setAcceleration(Vector3 a) { acc = a; }
	void setMass(float m) { masa = m; }

private:
	PxTransform pose;
	Vector3 vel;
	Vector3 acc;
	float masa;
	float lifeTime;
	RenderItem* dynamic_item;
};