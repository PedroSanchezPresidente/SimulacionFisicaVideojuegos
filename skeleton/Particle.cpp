#include "Particle.h"

void Particle::integrade(double t) {
	pose.p += t * vel;
}