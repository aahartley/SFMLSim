#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
enum class Direction {
	up = 0, down, left, right

};

class Particle{
public:
	Particle(sf::Vector2f coord,float mass);
	sf::Vector2f coord;
	sf::CircleShape circle;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float startY = coord.y;
	void calculation(float dt,std::vector<Particle*>& buffer);
	void collisionDetection(float dt,std::vector<Particle*>& buffer);
	void forces(float dt);
	void draw(float dt);
	float getMass() { return mass; }
private:

	float mass,elasticity;


};

