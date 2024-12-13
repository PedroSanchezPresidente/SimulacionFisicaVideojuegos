#pragma once
#include "ForceGenerator.h"

class BouyancyForceGenerator : public ForceGenerator {
public:
	BouyancyForceGenerator(float h, float w, float de, float v, float d, Vector3 Pos) : _height(h), _deepth(de), _width(w), _volume(v), _liquid_density(d), ForceGenerator(Pos) {
		PxBoxGeometry b;
		b.halfExtents = { _width, _height , _deepth };
		PxShape* sape = CreateShape(b);
		_liquid_particle = new Particle(Pos, { 0,0,0 }, { 0,0,0 }, { 0,0,1 }, 1, sape, 100, 100);
	}

	virtual Vector3 getForce(Object* p) {

			if ((pos.x - _width < p->getPos().x && pos.x + _width > p->getPos().x)) {
				if ((pos.z - _deepth < p->getPos().z && pos.z + _deepth > p->getPos().z)) {
					float h = p->getPos().y;
					float h0 = _liquid_particle->getPos().y;

					Vector3 f(0, 0, 0);
					float immersed = 0.0;
					if (h - h0 > _height * 0.5)
						immersed = 0.0;
					else if (h0 - h > _height * 0.5)
						immersed = 1.0;
					else
						immersed = (h0 - h) / _height + 0.5;

					f.y = _liquid_density * _volume * immersed * 9.8;
					return f;
				}
			}
			else 
				return { 0,0,0 };

	}

protected:
	float _height;
	float _width;
	float _deepth;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;
};