#pragma once
#include <SFML/Graphics.hpp>

class Sim {
public:
	Sim();
	~Sim() { delete window; }
	void draw();
private:
	sf::RenderWindow* window;
};