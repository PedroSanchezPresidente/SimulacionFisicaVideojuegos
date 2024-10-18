#include "Particle.h"

void Particle::integrade(double t) {
#ifdef EULER
	pose.p += t * vel;
	vel += t * acc;
	vel = vel * pow(dumpling, t);
#elif defined SEMI-INPLICIT_EULER
	vel += t * acc;
	pose.p += t * vel;
	vel = vel * pow(dumpling, t);
#elif defined VERLET
	vel += acc * t / 2;
	pose.p += vel*t;
#endif // !Euler
	time -= t;
}