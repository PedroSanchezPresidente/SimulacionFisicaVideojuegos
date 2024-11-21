#pragma once
#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator {
private:
	Vector3 _aceleracion;

public:
	GravityGenerator(Vector3 acc, Vector3 Pos = Vector3(0,0,0)) : _aceleracion(acc), ForceGenerator(Pos) {};

	void setAcc(Vector3 acc) { _aceleracion = acc; };

	virtual Vector3 getForce(Particle* particle) {
		return particle->getMasa() * _aceleracion;
	}
};