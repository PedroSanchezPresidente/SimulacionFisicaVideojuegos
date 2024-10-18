#pragma once
#include <list>
#include "Particle.h"

enum ParticleType {SPHERE, BOX};

class ParticleGenerator
{
private:
	ParticleType type;
	Vector3 pos;
	Vector3 dir;
	int radio;
	int lifeTime;
	float timer;
	float rate;			//particulas por segundo
	PxShape* shape;
	int numPar;

public:
	ParticleGenerator(Vector3 Pos, Vector3 Dir, int Radio, float LifeTime, float Rate, ParticleType Type) : pos(Pos), dir(Dir), radio(Radio * Radio), lifeTime(LifeTime), type(Type), numPar(0) {
		rate = 1 / Rate;
		if (type == SPHERE){
			PxSphereGeometry s;
			s.radius = 1;
			shape = CreateShape(s);
		}
		else if(type == BOX){
			PxBoxGeometry b;
			shape = CreateShape(b);
		}
	};

	void generarParticulas(std::list<Particle*> &particulas, double t);

	int getNumeroParticula() { return numPar; };

	Vector3 getPos() { return pos; };

	float getRadio() { return radio; };
};

