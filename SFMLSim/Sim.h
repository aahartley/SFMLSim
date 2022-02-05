#pragma once
#include <SFML/Graphics.hpp>
#include <omp.h>

class Sim {
public:
	Sim();
	~Sim() { delete window; }
	void draw();
private:
	sf::RenderWindow* window;
};