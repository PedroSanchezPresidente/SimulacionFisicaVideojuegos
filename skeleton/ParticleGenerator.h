#pragma once
#include <list>
#include "Particle.h"

enum ParticleType {SPHERE, BOX};

class ParticleGenerator
{
private:
	ParticleType type;
	Vector3 pos;
	Vector3 minDir;
	int radio;
	int lifeTime;
	float timer;
	float rate;			//particulas por segundo
	PxShape* shape;
	int numPar;
	Vector3 maxDir;

public:
	ParticleGenerator(Vector3 Pos, Vector3 MinDir, int Radio, float LifeTime, float Rate, ParticleType Type, Vector3 DirMax = Vector3(0,0,0)) : pos(Pos), minDir(MinDir), radio(Radio* Radio), lifeTime(LifeTime), type(Type), numPar(0), maxDir(DirMax) {
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

	void generarParticulasDU(std::list<Particle*> &particulas, double t);

	void generarParticulasGauss(std::list<Particle*>& particulas, double t);

	int getNumeroParticula() { return numPar; };

	void decreaseNumeroParticula() { numPar--; };

	Vector3 getPos() { return pos; };

	float getRadio() { return radio; };
};

