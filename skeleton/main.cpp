#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Vector3D.h"
#include "Proyectil.h"
#include "ParticleSystem.h"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

RenderItem* esferaX;
RenderItem* esferaY;
RenderItem* esferaZ;

ParticleSystem* particleSystem;

std::vector<Proyectil*> proyectiles;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//Geometria de esfera
	PxSphereGeometry s;
	s.radius = 1;


	esferaX = new RenderItem;
	Vector3D v1(10, 0, 0);
	esferaX->transform = new PxTransform(PxVec3(v1.x, v1.y, v1.z));
	esferaX->color = Vector4(1.0, 0, 0, 1.0);
	esferaX->shape = CreateShape(s);
	RegisterRenderItem(esferaX);

	esferaY = new RenderItem;
	Vector3D v2(0, 10, 0);
	esferaY->transform = new PxTransform(PxVec3(v2.x, v2.y, v2.z));
	esferaY->color = Vector4(0, 1.0, 0, 1.0);
	esferaY->shape = CreateShape(s);
	RegisterRenderItem(esferaY);

	esferaZ = new RenderItem;
	Vector3D v3 = v1 * v2;
	v3 = v3.normalize() * 10;
	esferaZ->transform = new PxTransform(PxVec3(v3.x, v3.y, v3.z));
	esferaZ->color = Vector4(0, 0, 1.0, 1.0);
	esferaZ->shape = CreateShape(s);
	RegisterRenderItem(esferaZ);

	particleSystem = new ParticleSystem();
	particleSystem->addGenerator(Vector3(0,0,0), Vector3(0,10,0), 1, 1, 2, ParticleType::SPHERE);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	for(int i = 0; i < proyectiles.size(); i++)
		proyectiles[i]->integrade(t);

	particleSystem->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	DeregisterRenderItem(esferaX);
	DeregisterRenderItem(esferaY);
	DeregisterRenderItem(esferaZ);

	for(int i = 0; i < proyectiles.size(); i ++)
		delete proyectiles[i];
	proyectiles.clear();
	delete particleSystem;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		proyectiles.push_back(new Proyectil(camera.p, GetCamera()->getDir() * 10, Vector3(0, 0, 0), Vector3(38,0,0)));
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}