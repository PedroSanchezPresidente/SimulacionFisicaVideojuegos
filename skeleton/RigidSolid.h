#pragma once
#include "Object.h"
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include <vector>

using namespace physx;

class RigidSolid : public Object{
public:
	RigidSolid(Vector3 Pos, Vector3 Color, PxShape* Shape, float Densidad, float Masa, float LifeTime, float Radio, PxScene* gScene, PxPhysics* gPhysics, std::vector<int>* FGIndex = new std::vector<int>) : Object(Pos, LifeTime, Radio, Masa, FGIndex), scene(gScene), shape(Shape) {

		new_solid = gPhysics->createRigidDynamic(pose);
		new_solid->setLinearVelocity(vel);
		new_solid->setAngularVelocity({0,0,0});
		new_solid->attachShape(*shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, Densidad);
		gScene->addActor(*new_solid);

		renderItem = new RenderItem(shape, new_solid, {Color, 1});
	}

	virtual ~RigidSolid() {
		DeregisterRenderItem(renderItem);
		scene->removeActor(*new_solid);
		new_solid->release();
	}

	void setVelocity(Vector3 v) { vel = v; }
	void setAcceleration(Vector3 a) { acc = a; }
	void setMasa(float m) { masa = m; }
	float getMasa() { return masa; }
	void integrade(double t) { lifeTime -= t; };
	std::vector<int>* getForceGenerator() const { return forceGeneratorsIndex; };
	void addForce(Vector3 f) { new_solid->addForce(f); };
	virtual Vector3 getPos() { return new_solid->getGlobalPose().p; };
	void reset() { new_solid->getGlobalPose().p = posIni; };
	

	bool isAlive() { 
		if (lifeTime < 0 || (pose.p - posIni).magnitudeSquared() > radio)
			return false;
		else
			return true;
	};

private:
	PxRigidDynamic* new_solid;
	PxScene* scene;
	PxShape* shape;
};