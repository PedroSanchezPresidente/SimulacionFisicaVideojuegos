#include "ParticleGenerator.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

void ParticleGenerator::generarParticulasDU(std::list<Particle*> &particulas, double t) {
	timer += t;
	int cont = timer / rate;
	timer -= rate * cont;
	for (int i = 0; i < cont; i++) {
		Particle* p = new Particle(pos, Vector3(rand() % (int)maxDir.x + (int)minDir.x, rand() % (int)maxDir.y + minDir.y, rand() % (int)maxDir.z + minDir.z), Vector3(1, 1, 1), Vector3(0, 0, 0), 1, shape, lifeTime);
		particulas.push_back(p);
		numPar++;
	}
}

void ParticleGenerator::generarParticulasGauss(std::list<Particle*>& particulas, double t) {
	timer += t;
	int cont = timer / rate;
	timer -= rate * cont;

	std::normal_distribution<float> normal_dist{ 10.0, 2.0 };

	for (int i = 0; i < cont; i++) {
		int r = rand() % 11;
		Vector3 dir = Vector3(r, normal_dist((float)r), r);
		Particle* p = new Particle(pos, dir, Vector3(1, 1, 1), Vector3(0, 0, 0), 1, shape, lifeTime);
		particulas.push_back(p);
		numPar++;
	}
}