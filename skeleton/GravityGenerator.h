#pragma once
#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator {
private:
	Vector3 _aceleracion;

public:
	GravityGenerator(Vector3 acc) : _aceleracion(acc) {};

	void setAcc(Vector3 acc) { _aceleracion = acc; };

	virtual Vector3 getForce(Particle* particle) {
		return particle->getMasa() * _aceleracion;
	}
};