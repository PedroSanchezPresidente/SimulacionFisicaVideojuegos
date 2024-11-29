#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;

class RigidSolid {
public:
	RigidSolid(Vector3 Pos, Vector3 Color, PxShape* shape, float Densidad, float LifeTime, float maxDist, PxScene* gScene, PxPhysics* gPhysics) : iniPos(Pos), pose(Pos), lifeTime(LifeTime), masa(1), vel({ 0,0,0 }), acc({0,0,0}) {

		PxRigidDynamic* new_solid;
		new_solid = gPhysics->createRigidDynamic(pose);
		new_solid->setLinearVelocity(vel);
		new_solid->setAngularVelocity({0,0,0});
		new_solid->attachShape(*shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, Densidad);
		gScene->addActor(*new_solid);

		dynamic_item = new RenderItem(shape, new_solid, { Color, 1 });
	}

	void setVelocity(Vector3 v) { vel = v; }
	void setAcceleration(Vector3 a) { acc = a; }
	void setMass(float m) { masa = m; }

	bool isAlive() {}

private:
	PxTransform pose;
	Vector3 iniPos;
	Vector3 vel;
	Vector3 acc;
	float masa;
	float lifeTime;
	RenderItem* dynamic_item;
};