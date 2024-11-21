#include "ParticleGenerator.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>


void ParticleGenerator::generarParticulas(std::list<Particle*>& particulas, double t) {
	switch (type) {
	case LINEAL:
		generarParticulasDU(particulas, t);
		break;
	case NORMAL_2D:
		generarParticulasGauss(particulas, t);
		break;
	}
}


void ParticleGenerator::generarParticulasDU(std::list<Particle*> &particulas, double t) {
	timer += t;
	int cont = timer / rate;
	timer -= rate * cont;
	for (int i = 0; i < cont; i++) {
		Vector3 dir = Vector3(generateUni(data.uniform_data.minDir.x, data.uniform_data.maxDir.x), generateUni(data.uniform_data.minDir.y, data.uniform_data.maxDir.y), generateUni(data.uniform_data.minDir.z, data.uniform_data.maxDir.z));
		Particle* p = new Particle(pos, dir, scale, color, transparencia, shape, lifeTime, radio, masa, ForceGeneratorsIndex);
		particulas.push_back(p);
		numPar++;
	}
}

void ParticleGenerator::generarParticulasGauss(std::list<Particle*>& particulas, double t) {
	timer += t;
	int cont = timer / rate;
	timer -= rate * cont;;

	for (int i = 0; i < cont; i++) {
		Vector3 dir = Vector3(generateGauss(data.normal_data.mean, data.normal_data.dev.x), generateGauss(data.normal_data.mean, data.normal_data.dev.y), generateGauss(data.normal_data.mean, data.normal_data.dev.z));
		Particle* p = new Particle(pos, dir, scale, color, transparencia, shape, lifeTime, radio, masa, ForceGeneratorsIndex);
		particulas.push_back(p);
		numPar++;
	}
}

float ParticleGenerator::generateGauss(float mean, float dev) {
	std::random_device rd{};
	std::mt19937 r{ rd() };
	std::normal_distribution<float> normal_dist(mean, dev);
	return normal_dist(r);
}

float ParticleGenerator::generateUni(float min, float max) {
	std::random_device rd{};
	std::mt19937 r{ rd() };
	std::uniform_real_distribution<float> normal_dist(min, max);
	return normal_dist(r);
}