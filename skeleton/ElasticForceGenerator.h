#pragma once
#include "SpringForceGenerator.h"

class ElasticForceGenerator : public SpringForceGenerator{
private:
	Object* _one;

public:
	ElasticForceGenerator(double k, double resting_leng, Object* other, Object* one) : SpringForceGenerator(k, resting_leng, other), _one(one) {};

	virtual Vector3 getForce(Object* particle) {
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