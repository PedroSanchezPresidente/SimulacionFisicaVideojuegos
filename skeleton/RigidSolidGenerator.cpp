#include "RigidSolidGenerator.h"

void RigidSolidGenerator::generateSR(std::list<RigidSolid*>& list, double t) {
	timer += t;
	int cont = timer / rate;
	timer -= rate * cont;
	for (int i = 0; i < cont; i++) {
		RigidSolid* p = new RigidSolid(pos, color, shape, densidad, lifeTime, radio, gScene, gPhysics);
		list.push_back(p);
		numSR++;
	}
}