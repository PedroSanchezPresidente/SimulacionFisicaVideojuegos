#include "Particle.h"

void Particle::integrade(double t) {
	vel += t * acc;
	pose.p += t * vel;
}