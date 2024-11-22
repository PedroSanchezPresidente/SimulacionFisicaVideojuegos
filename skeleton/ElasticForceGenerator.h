#pragma once
#include "SpringForceGenerator.h"

class ElasticForceGenerator : public SpringForceGenerator{
private:
	Particle* _one;

public:
	ElasticForceGenerator(double k, double resting_leng, Particle* other, Particle* one) : SpringForceGenerator(k, resting_leng, other), _one(one) {};

	virtual Vector3 getForce(Particle* particle) {
		if (_other == particle) {
			_other = _one;
			_one = particle;
		}
		if ((_one->getPos() - _other->getPos()).magnitudeSquared() > _resting_length * _resting_length)
			return SpringForceGenerator::getForce(_one);
		else
			return Vector3(0,0,0);
	}
};