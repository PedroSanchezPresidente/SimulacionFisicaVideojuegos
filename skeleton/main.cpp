#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Vector3D.h"
#include "Proyectil.h"
#include "ParticleSystem.h"
#include "RigidSolid.h"
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

ParticleSystem* particleSystem;

std::vector<Proyectil*> proyectiles;
std::vector<Particle*> particles;
std::vector<int>* fuerzas_p = new vector<int>;
std::vector<int>* fuerzas_t = new vector<int>;

vector<PxRigidStatic*> mapa;
vector<RenderItem*> mapa_i;
RigidSolid* pelota;
vector<RigidSolid*> obstaculos;


extern void setCamPos(Vector3 pos);

void createMap() {
	PxRigidStatic* Suelo = gPhysics->createRigidStatic({ -400,0,0 });
	PxShape* shape = CreateShape(PxBoxGeometry(500, 0.1, 100));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0, 0.2, 0, 1 }));
	mapa.push_back(Suelo);

	Suelo = gPhysics->createRigidStatic({ -400,0,100 });
	shape = CreateShape(PxBoxGeometry(500, 30, 0.1));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 }));
	mapa.push_back(Suelo);

	Suelo = gPhysics->createRigidStatic({ -400,0,-100 });
	shape = CreateShape(PxBoxGeometry(500, 30, 0.1));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 }));
	mapa.push_back(Suelo);

	Suelo = gPhysics->createRigidStatic({ 100,0,0 });
	shape = CreateShape(PxBoxGeometry(0.1, 10, 100));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 }));
	mapa.push_back(Suelo);

	Suelo = gPhysics->createRigidStatic({ -900,0,0 });
	shape = CreateShape(PxBoxGeometry(0.1, 30, 100));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 }));
	mapa.push_back(Suelo);

	int i = particleSystem->addBouyancyGenerator(2, 50, 100, 4.f / 3.f * 3.1416 * 2.f * 2.f * 2.f, 1, { -100,2,0 });

	fuerzas_p->push_back(i);

	i = particleSystem->addForceGenerator(ForceGeneratorTipe::WHIRLWIND, {-700,0,0}, 1, 40);
	fuerzas_t->push_back(i);
	fuerzas_p->push_back(i);
	particleSystem->addParticleGenerator(Vector3(-700, 0, 0), 0, Vector3(10, 0.1, 10), 90, 10, 10, Vector3(1, 1, 0), 1, Vector3(1, 1, 1), 2, fuerzas_t);

	i = particleSystem->addForceGenerator(ForceGeneratorTipe::WIND, { 0,0,30 }, 1, 25, {-500,10,-100});
	fuerzas_p->push_back(i);
	particleSystem->addParticleGenerator(Vector3(-500, 10, -100), Vector3(-3, -3, 20), Vector3(3, 3, 40), 200, 10, 50, Vector3(0, 0, 1), 5, Vector3(1, 1, 1), 1);

	PxBoxGeometry box;
	box.halfExtents = { 2,2,4 };
	shape = CreateShape(box);
	float masa = 1;
	float volumen = 4.f * 2.f * 2.f;
	obstaculos.push_back(particleSystem->generateRs({ -200,2,50 }, { 1,1,1 }, shape, masa / volumen, masa, 0, 0, gScene, gPhysics, fuerzas_p));
	obstaculos.push_back(particleSystem->generateRs({ -249,2,27 }, { 1,1,1 }, shape, masa / volumen, masa, 0, 0, gScene, gPhysics, fuerzas_p));
	obstaculos.push_back(particleSystem->generateRs({ -293,2,-72 }, { 1,1,1 }, shape, masa / volumen, masa, 0, 0, gScene, gPhysics, fuerzas_p));
	obstaculos.push_back(particleSystem->generateRs({ -223,2,-7 }, { 1,1,1 }, shape, masa / volumen, masa, 0, 0, gScene, gPhysics, fuerzas_p));
	obstaculos.push_back(particleSystem->generateRs({ -323,2,30 }, { 1,1,1 }, shape, masa / volumen, masa, 0, 0, gScene, gPhysics, fuerzas_p));
	obstaculos.push_back(particleSystem->generateRs({ -364,2,-42 }, { 1,1,1 }, shape, masa / volumen, masa, 0, 0, gScene, gPhysics, fuerzas_p));
	obstaculos.push_back(particleSystem->generateRs({ -293,2,-21 }, { 1,1,1 }, shape, masa / volumen, masa, 0, 0, gScene, gPhysics, fuerzas_p));
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	srand(time(NULL));
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

	particleSystem = new ParticleSystem();

	createMap();

	PxSphereGeometry sphere;
	sphere.radius = 2;
	PxShape* shape = CreateShape(sphere);
	float volumen = 4.f / 3.f * 3.1416 * 2.f * 2.f * 2.f;
	pelota = particleSystem->generateRs({ 0,2,0 }, { 1,0,0 }, shape, 2 / volumen, 2, 0, 0, gScene, gPhysics, fuerzas_p);
	setCamPos(pelota->getPos());
	}

void reset() {
	for (RigidSolid* r : obstaculos)
		r->reset();
	pelota->reset();
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

	setCamPos(pelota->getPos());
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	delete particleSystem;

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	for(int i = 0; i < proyectiles.size(); i ++)
		delete proyectiles[i];
	proyectiles.clear();

	for(RenderItem* i : mapa_i)
		DeregisterRenderItem(i);
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	int index;
	switch(toupper(key))
	{
	case 'W':
		pelota->addForce({-100,0,0});
		break;
	case 'S':
		pelota->addForce({ 100,0,0 });
		break;
	case 'A':
		pelota->addForce({ 0,0,100 });
		break;
	case 'D':
		pelota->addForce({ 0,0,-100 });
		break;
	case 'R':
		reset();
		break;
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