#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include <vector>

using namespace physx;

class RigidSolid {
public:
	RigidSolid(Vector3 Pos, Vector3 Color, PxShape* Shape, float Densidad, float LifeTime, float MaxDist, PxScene* gScene, PxPhysics* gPhysics, std::vector<int>* FGIndex = new std::vector<int>, ) : iniPos(Pos), pose(Pos), lifeTime(LifeTime), maxDist(MaxDist*MaxDist), masa(1), vel({0,0,0}), acc({0,0,0}), scene(gScene), shape(Shape), forceGeneratorsIndex(FGIndex) {

		new_solid = gPhysics->createRigidDynamic(pose);
		new_solid->setLinearVelocity(vel);
		new_solid->setAngularVelocity({0,0,0});
		new_solid->attachShape(*shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, Densidad);
		gScene->addActor(*new_solid);

		dynamic_item = new RenderItem(shape, new_solid, {Color, 1});
		/*dynamic_item->shape = shape;
		dynamic_item->actor = new_solid;
		dynamic_item->color = { Color, 1 };*/
	}

	virtual ~RigidSolid() {
		DeregisterRenderItem(dynamic_item);
		scene->removeActor(*new_solid);
		new_solid->release();
	}

	void setVelocity(Vector3 v) { vel = v; }
	void setAcceleration(Vector3 a) { acc = a; }
	void setMass(float m) { masa = m; }
	void integrade(double t) { lifeTime -= t; };

	bool isAlive() { 
		if (lifeTime < 0 || (pose.p - iniPos).magnitudeSquared() > maxDist)
			return false;
		else
			return true;
	};

private:
	PxTransform pose;
	Vector3 iniPos;
	Vector3 vel;
	Vector3 acc;
	float masa;
	float lifeTime;
	float maxDist;
	RenderItem* dynamic_item;
	PxRigidDynamic* new_solid;
	PxScene* scene;
	PxShape* shape;
	std::vector<int>* forceGeneratorsIndex;
};