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
std::vector<int>* fuerzas = new vector<int>;

vector<PxRigidStatic*> mapa;
vector<RenderItem*> mapa_i;
RigidSolid* pelota;

extern void setCamPos(Vector3 pos);

void createMap() {
	PxRigidStatic* Suelo = gPhysics->createRigidStatic({ -400,0,0 });
	PxShape* shape = CreateShape(PxBoxGeometry(500, 0.1, 100));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0, 0.2, 0, 1 }));
	mapa.push_back(Suelo);

	Suelo = gPhysics->createRigidStatic({ -400,0,100 });
	shape = CreateShape(PxBoxGeometry(500, 50, 0.1));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 }));
	mapa.push_back(Suelo);

	Suelo = gPhysics->createRigidStatic({ -400,0,-100 });
	shape = CreateShape(PxBoxGeometry(500, 50, 0.1));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 }));
	mapa.push_back(Suelo);

	Suelo = gPhysics->createRigidStatic({ 100,0,0 });
	shape = CreateShape(PxBoxGeometry(0.1, 50, 100));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 }));
	mapa.push_back(Suelo);

	Suelo = gPhysics->createRigidStatic({ -900,0,0 });
	shape = CreateShape(PxBoxGeometry(0.1, 50, 100));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	mapa_i.push_back(new RenderItem(shape, Suelo, { 0.8,0.8,0.8,1 }));
	mapa.push_back(Suelo);

	int i = particleSystem->addBouyancyGenerator(2, 50, 100, 4.f / 3.f * 3.1416 * 2.f * 2.f * 2.f, 1, { -100,2,0 });

	fuerzas->push_back(i);

	int i = particleSystem->addForceGenerator(ForceGeneratorTipe::WHIRLWIND, {-700,0,0}, 1, 40);
	particleSystem->addParticleGenerator({-700}, ,);
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

	//particleSystem->generateParticle(Vector3(0, -20, 15), Vector3(0, 0, 0), Vector3(1, 1, 1), 100.f, 1000.f, 1.f, v);


	//int index = particleSystem->addAnchorGenerator({0,0,15}, 1, 10);
	//v->push_back(index);

	//std::vector<int>* aux = new std::vector<int>;

	//Particle* p1 = particleSystem->generateParticle(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 1, 0), 100.f, 1000.f, 1.f, aux);
	//Particle* p2 = particleSystem->generateParticle(Vector3(5, 0, 0), Vector3(0, 0, 0), Vector3(1, 0, 0), 100.f, 1000.f, 1.f, aux);

	//aux->push_back(particleSystem->addElasticGenerator(p1, 1, 2, p2));


	//particleSystem->generateParticle(Vector3(0, 5, 0), Vector3(0, 0, 0), Vector3(1, 0, 0), 100.f, 1000.f, 2.5, v);
	//v->push_back(particleSystem->addBouyancyGenerator(0.5, 4.19, 1));
	//v->push_back(particleSystem->addForceGenerator(GRAVITY, {0,-9.8,0}));

	createMap();

	PxSphereGeometry sphere;
	sphere.radius = 2;
	PxShape* shape = CreateShape(sphere);
	float densidad = 4.f / 3.f * 3.1416 * 2.f * 2.f * 2.f;
	//rigidSolids.push_back(new RigidSolid({ 0,1,0 }, {1,0,0}, shape, densidad , 2 , 100, 1,gScene, gPhysics, v));
	//particleSystem->addRSGenerator({ 0,20,0 }, { 1,0,0 }, shape, 2/densidad, 2, 10, 1 ,gScene, gPhysics, 5, fuerzas);
	pelota = particleSystem->generateRs({ 0,2,0 }, { 1,0,0 }, shape, 2 / densidad, 2, 10000, 100000, gScene, gPhysics, fuerzas);
	setCamPos(pelota->getPos());

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

	delete pelota;

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


	delete particleSystem;

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