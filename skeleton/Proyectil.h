#pragma once
#include "Particle.h"

class Proyectil : Particle
{
private:
	Vector3 gS;
	float masaS;
public:
	Proyectil(Vector3 Pos, Vector3 Vel, Vector3 Acc, Vector3 VelR = Vector3(330, 0, 0), float Masa = 0.00356, Vector3 Gravedad = Vector3(0.0, -9.8, 0.0), float Dumpling = 0.9) : Particle(Pos, Vel, Acc, Dumpling)
	{
		masaS = Masa * VelR.magnitudeSquared() / vel.magnitudeSquared();
		gS = Gravedad * vel.magnitudeSquared() / VelR.magnitudeSquared();
	};

	virtual void integrade(double t);
};

