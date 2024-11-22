#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "GravityGenerator.h"
#include "WhirlWindGenerator.h"
#include "ExplosionGenerator.h"

using namespace std;

class ParticleSystem
{
private:
	list<Particle*> particles;
	vector<ParticleGenerator*> particleGens;
	vector<ForceGenerator*> forceGens;

public:
	~ParticleSystem() {
		for (Particle* p : particles)
			delete p;
		particles.clear();

		for (ParticleGenerator* g : particleGens)
			delete g;
		particleGens.clear();
	}

	void update(double t);

	int addParticleGenerator(Vector3 pos, Vector3 minDir, Vector3 maxDir, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale, float Masa = 1, vector<int>* FGIndex = new vector<int>);

	int addParticleGenerator(Vector3 pos, float mean, Vector3 dev, float radio, float lifeTime, float ratio, Vector3 color, float transparencia, Vector3 scale, float Masa = 1, vector<int>* FGIndex = new vector<int>);

	void asociateForceGenerator(int ParticleGeneratorIndex, int ForceGeneratorIndex);

	void generateParticle(Vector3 pos, Vector3 vel, Vector3 color, float lifeTime, float radius, float masa, std::vector<int>* index);

	void asociateForceGeneratorToAll(int ForceGeneratorIndex);

	int addForceGenerator(ForceGeneratorTipe tipe, Vector3 force, float k = 1, float Radius = 0);
};

