#include "Particle.h"

void Particle::integrade(double t) {
	vel +=  + t * acc;
	vel = vel * pow(dumpling, t);
	pose.p += t * vel;
}