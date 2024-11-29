#pragma once
#include <list>
#include "Particle.h"
#include "RigidSolid.h"
#include "ParticleGenerator.h"
#include "GravityGenerator.h"
#include "WhirlWindGenerator.h"
#include "ExplosionGenerator.h"
#include "AnchoredSpringFG.h"
#include "ElasticForceGenerator.h"
#include "BouyancyForceGenerator.h"
#include "RigidSolidGenerator.h"

using namespace std;

class ParticleSystem
{
private:
	list<Particle*> particles;
	list<RigidSolid*> rigidSolids;
	vector<ParticleGenerator*> particleGens;
	vector<ForceGenerator*> forceGens;
	vector<RigidSolidGenerator*> RSGens;

public:
	~ParticleSystem() {
		for (Particle* p : particles)
			delete p;
		particles.clear();

		for (ParticleGenerator* g : particleGens)
			delete g;
		particleGens.clear();

		for (ForceGenerator* g : forceGens)
			delete g;
		forceGens.clear();
	}

	void update(double t);

	int addParticleGenerator(Vector3 pos, Vector3 minDir, Vector3 maxDir, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale, float Masa = 1, vector<int>* FGIndex = new vector<int>);

	int addParticleGenerator(Vector3 pos, float mean, Vector3 dev, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale, float Masa = 1, vector<int>* FGIndex = new vector<int>);

	void asociateForceGenerator(int ParticleGeneratorIndex, int ForceGeneratorIndex);

	Particle* generateParticle(Vector3 pos, Vector3 vel, Vector3 color, float lifeTime, float radius, float masa, std::vector<int>* index);

	void asociateForceGeneratorToAll(int ForceGeneratorIndex);

	int addForceGenerator(ForceGeneratorTipe tipe, Vector3 force, float k = 1, float Radius = 0);

	int addElasticGenerator(Particle* p1, double k, double res, Particle* p2);

	int addBouyancyGenerator(float h, float v, float d);

	int addAnchorGenerator(Vector3 pos, double k, double res);
};

