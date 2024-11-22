#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringFG : public SpringForceGenerator {
public :
	AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr) {
		PxBoxGeometry b;
		b.halfExtents = Vector3(1, 1, 1);
		PxShape* sape = CreateShape(b);
		_other = new Particle(anchor_pos, { 0,0,0 }, { 1,1,1 }, {0,0,0},1, sape, 100, 10, 1000);
	}

	~AnchoredSpringFG() {
		delete _other;
	}
};