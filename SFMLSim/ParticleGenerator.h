#pragma once
#include "Particle.h"

class ParticleGenerator{
public:
	ParticleGenerator() {};
	std::vector<Particle*> particles;
	std::vector<Particle*> generate(int num,Direction d);
	void path();
};