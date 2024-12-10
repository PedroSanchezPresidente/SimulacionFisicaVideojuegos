#pragma once
#include "ForceGenerator.h"

class BouyancyForceGenerator : public ForceGenerator {
public:
	BouyancyForceGenerator(float h, float v, float d) : _height(h), _volume(v), _liquid_density(d), ForceGenerator(Vector3(0,0,0)) {
		PxBoxGeometry b;
		b.halfExtents = { 10,0.5,10 };
		PxShape* sape = CreateShape(b);
		_liquid_particle = new Particle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,1 }, 1, sape, 100, 100);
	}

	virtual Vector3 getForce(Object* p) {
		float h = p->getPos().y;
		float h0 = _liquid_particle->getPos().y;

		Vector3 f(0, 0, 0);
		float immersed = 0.0;
		if (h - h0 > _height * 0.5)
			immersed = 0.0;
		else if (h0 - h > _height * 0.5)
			immersed = 1.0;
		else
			immersed = (h0 - h) / _height + 0.5;

		f.y = _liquid_density * _volume * immersed * 9.8;
		return f;
	}

protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;
};