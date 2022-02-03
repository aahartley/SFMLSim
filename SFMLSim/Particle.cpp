#include "Particle.h"


Particle::Particle(sf::Vector2f coord,float mass)
	:coord(coord),mass(mass),acceleration(sf::Vector2f{0.0f,0.0f}),
		velocity(sf::Vector2f{ 0.0f,0.0f })
{
	float force = 10.0f * mass;
	//acceleration.y += force / mass;
	//acceleration.x = 1.0f;
	elasticity = 0.5f;
}
void Particle::draw(float dt) {
	coord.x += velocity.x * dt;
	coord.y += velocity.y * dt;
	if (coord.y >= 700 - circle.getRadius() * 2)
		coord.y = 700 - circle.getRadius() * 2;
	if (coord.x >= 700 - circle.getRadius() * 2)
		coord.x = 700 - circle.getRadius() * 2;
	if (coord.y <= 100)
		coord.y = 100;
	if (coord.x <= 100)
		coord.x = 100;
}
void Particle::forces(float dt) {
	velocity.x += acceleration.x * dt;
	velocity.y += acceleration.y * dt;



}
void Particle::calculation(float dt,std::vector<Particle*>& buffer) {
	forces(dt);
	collisionDetection(dt, buffer);
	draw(dt);
	circle.setPosition(coord);
	
}
void Particle::collisionDetection(float dt,std::vector<Particle*>& buffer) {
	std::vector<std::pair<Particle,Particle>> collidingCircles;
	//floor
	if (circle.getPosition().y >= 700-circle.getRadius()*2) {
		velocity.y *= -elasticity;
	}
	//top
	if (circle.getPosition().y <= 100) {
	
		velocity.y *= -elasticity;
	}
	//right
	if (circle.getPosition().x >= 700 - circle.getRadius() * 2) {
	
		velocity.x *= -elasticity;
	}
	//left
	if (circle.getPosition().x <= 100) {

		velocity.x *= -elasticity;
	}
	//static collision
	for (Particle* p : buffer) {

		if (p != this) {
			//distance between circles
			float distance = std::sqrtf((p->coord.x - coord.x) * (p->coord.x - coord.x) + (p->coord.y - coord.y) * (p->coord.y - coord.y));
			//if circles are touching
			if (distance <= circle.getRadius()+p->circle.getRadius()) {
				collidingCircles.push_back({ *p,*this });
				float overlap = 0.5f * distance - circle.getRadius() - p->circle.getRadius();
				//displace circles by overlap
				coord.x -= overlap * (coord.x - p->coord.x) / distance;
				coord.y -= overlap * (coord.y - p->coord.y) / distance;
				p->coord.x += overlap * (coord.x - p->coord.x) / distance;
				p->coord.y += overlap * (coord.y - p->coord.y) / distance;
			
		
			}
		}
	}

	for (auto p : collidingCircles) {
		Particle& first = p.first;
		Particle& second = p.second;
		float distance = std::sqrtf((first.coord.x - second.coord.x) * (first.coord.x - second.coord.x) + (first.coord.y - second.coord.y) * (first.coord.y - second.coord.y));
		// Normal
		float nx = (second.coord.x - first.coord.x) / distance;
		float ny = (second.coord.y - first.coord.y) / distance;

		// Tangent
		float tx = -ny;
		float ty = nx;

		// Dot Product Tangent
		float dpTan1 = first.velocity.x * tx + first.velocity.y * ty;
		float dpTan2 = second.velocity.x * tx + second.velocity.y * ty;

		// Dot Product Normal
		float dpNorm1 = first.velocity.x * nx + first.velocity.y * ny;
		float dpNorm2 = second.velocity.x * nx + second.velocity.y * ny;

		// Conservation of momentum in 1D
		float m1 = (dpNorm1 * (first.mass - second.mass) + 2.0f * second.mass * dpNorm2) / (first.mass + second.mass);
		float m2 = (dpNorm2 * (second.mass - first.mass) + 2.0f * first.mass * dpNorm1) / (first.mass + second.mass);

		// Update ball velocities
		first.velocity.x = tx * dpTan1 + nx * m1;
		first.velocity.y = ty * dpTan1 + ny * m1;
		second.velocity.x = tx * dpTan2 + nx * m2;
		second.velocity.y = ty * dpTan2 + ny * m2;
	}
	collidingCircles.clear();
}
