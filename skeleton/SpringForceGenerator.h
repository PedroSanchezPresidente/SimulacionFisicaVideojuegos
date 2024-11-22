#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator {
public:
	SpringForceGenerator(double k, double resting_leng, Particle* other) : _k(k), _resting_length(resting_leng), _other(other) {};

	virtual Vector3 getForce(Particle* particle) {
		Vector3 relative_pos_vector = _other->getPos() - particle->getPos();
		Vector3 force;

		const float length = relative_pos_vector.normalize();
		const float delta_x = length - _resting_length;

		force = relative_pos_vector * delta_x * _k;

		return force;
	}

	inline void setK(double k) { _k = k; }

	virtual ~SpringForceGenerator() {}

protected:
	double _k;
	double _resting_length;
	Particle* _other
};