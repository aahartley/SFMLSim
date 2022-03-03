#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "Particle.h"
class Matrix {
public:
	Matrix() {};
	Matrix(float x, float y, float n);
	const float* operator [] (uint8_t i) const { return m[i]; }
	float* operator [] (uint8_t i) { return m[i]; }
	void multiply();
private:
	float m[1][3] {{100,100,1}};
};

