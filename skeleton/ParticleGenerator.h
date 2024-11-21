#pragma once
#include <list>
#include <vector>
#include "Particle.h"

enum ParticleType {LINEAL, NORMAL_2D, NORMAL_MULTI};

class ParticleGenerator
{
private:
	ParticleType type;
	Vector3 pos;
	int radio;
	int lifeTime;
	float timer;
	float rate;			//particulas por segundo
	PxShape* shape;
	int numPar;
	Vector3 color;
	float transparencia;
	Vector3 scale;
	float masa;
	std::vector<int>* ForceGeneratorsIndex;

	struct DistributionData {
		struct {
			Vector3 minDir;
			Vector3 maxDir;
		} uniform_data;
		struct {
			float mean;
			Vector3 dev;
		} normal_data;
	};

	DistributionData data;

	float generateGauss(float mean, float dev);

	float generateUni(float min, float max);

	void generarParticulasDU(std::list<Particle*> &particulas, double t);

	void generarParticulasGauss(std::list<Particle*>& particulas, double t);

public:
	ParticleGenerator(Vector3 Pos, Vector3 MinDir, Vector3 MaxDir,int Radio, float LifeTime, float Rate, Vector3 Color, float Transparencia, Vector3 Scale, float Masa = 1, std::vector<int>* FGIndex = new std::vector<int>) : pos(Pos), radio(Radio), lifeTime(LifeTime), type(LINEAL), numPar(0), color(Color), transparencia(Transparencia), scale(Scale), masa(Masa), ForceGeneratorsIndex(FGIndex) {
		data.uniform_data = { MinDir, MaxDir };
		rate = 1 / Rate;
		PxSphereGeometry s;
		s.radius = 1;
		shape = CreateShape(s);
	};

	ParticleGenerator(Vector3 Pos, float Mean, Vector3 Dev, int Radio, float LifeTime, float Rate, Vector3 Color, float Transparencia, Vector3 Scale, float Masa = 1, std::vector<int>* FGIndex = new std::vector<int>) : pos(Pos), radio(Radio), lifeTime(LifeTime), type(NORMAL_2D), numPar(0), color(Color), transparencia(Transparencia), scale(Scale), masa(Masa), ForceGeneratorsIndex(FGIndex) {
		data.normal_data = {Mean, Dev};
		rate = 1 / Rate;
		PxSphereGeometry s;
		s.radius = 1;
		shape = CreateShape(s);
	};

	void generarParticulas(std::list<Particle*>& particulas, double t);

	Vector3 getPos() { return pos; };

	float getRadio() { return radio; };

	void addForceGenerator(int i) { return ForceGeneratorsIndex->push_back(i); };

	std::vector<int>* getForceGenerators() const {return ForceGeneratorsIndex; };
};

