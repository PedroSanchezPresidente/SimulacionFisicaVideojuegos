#include "Proyectil.h"

void Proyectil::integrade(double t) {
	vel += (acc * t / 2) + gS * t;
	pose.p += vel * t;
}