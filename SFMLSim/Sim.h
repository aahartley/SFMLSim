#pragma once
#include <SFML/Graphics.hpp>
#include <omp.h>
#include "Matrix.h"

class Sim {
public:
	Sim();
	~Sim() { delete window; }
	void draw();
	void draw2();
private:
	sf::RenderWindow* window;
};