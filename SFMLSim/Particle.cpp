#include "Particle.h"


Particle::Particle(sf::Vector2f coord,float mass)
	:coord(coord),mass(mass),acceleration(sf::Vector2f{0.0f,0.0f}),
		velocity(sf::Vector2f{ 0.0f,0.0f })
{
	float force = 10.0f * mass;
	//acceleration.y += force / mass;
	//acceleration.x = 1.0f;
	elasticity =0.5f;
}
void Particle::draw(float dt) {
//	coord.x += velocity.x * dt;
	//coord.y += velocity.y * dt;
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
	coord.x += velocity.x * dt;
	coord.y += velocity.y * dt;
	

	

}
void Particle::calculation(float dt,std::vector<Particle*>& buffer) {
	forces(dt);
	collisionDetection(dt, buffer);
	draw(dt);
	circle.setPosition(coord);
	
}
sf::Vector2f Particle::rotate(sf::Vector2f& vel, float angle) {
	return sf::Vector2f{ vel.x * std::cos(angle) - vel.y * std::sin(angle),vel.x * std::sin(angle) + vel.y * std::cos(angle) };
}
void Particle::collisionDetection(float dt,std::vector<Particle*>& buffer) {
	std::vector<std::pair<Particle*,Particle*>> collidingCircles;
	//floor
	if (coord.y >= 700-circle.getRadius()*2) {
		velocity.y *= -elasticity;
	}
	//top
	if (coord.y <= 100) {
	
		velocity.y *= -elasticity;
	}
	//right
	if (coord.x >= 700 - circle.getRadius() * 2) {
	
		velocity.x *= -elasticity;
	}
	//left
	if (coord.x <= 100) {

		velocity.x *= -elasticity;
	}
	
	//collision between circles
	#pragma omp parallel for num_threads(2)
	for (int i = 0; i < buffer.size(); ++i) {
		if (buffer[i] != this) {
			float xDistance = buffer[i]->coord.x- this->coord.x ;
			float yDistance = buffer[i]->coord.y- this->coord.y;
			float radiSum = buffer[i]->circle.getRadius() + this->circle.getRadius();
			float distance = std::sqrt(std::pow(xDistance, 2) + std::pow(yDistance, 2));
			if (distance <= radiSum) {
				collidingCircles.push_back({ buffer[i], this });
				float overlap = radiSum - distance+1;
				this->coord.x += overlap/2;
				this->coord.y += overlap/2;
				buffer[i]->coord.x -= overlap / 2;
				buffer[i]->coord.y -= overlap / 2;
			}
		
	
		

		}
	}
	//resolve collision
	#pragma omp parallel for num_threads(2)
	for (int i = 0; i < collidingCircles.size(); ++i) {
		Particle* first = collidingCircles[i].first;
		Particle* second = collidingCircles[i].second;
		float xVelDif = first->velocity.x - second->velocity.x;
		float yVelDif = first->velocity.y - second->velocity.y;

		float xDist = second->coord.x - first->coord.x;
		float yDist = second->coord.y - first->coord.y;

		if (xVelDif * xDist + yVelDif * yDist >= 0) {
			float angle = -std::atan2(second->coord.y - first->coord.y, second->coord.x - first->coord.x);
			float m1 = first->mass;
			float m2 = second->mass;

			sf::Vector2f u1 = rotate(first->velocity, angle);
			sf::Vector2f u2 = rotate(second->velocity, angle);

			sf::Vector2f v1 = { u1.x * (m1 - m2) / (m1 + m2) + u2.x * 2 * m2 / (m1 + m2),u1.y };
			sf::Vector2f v2 = { u2.x * (m1 - m2) / (m1 + m2) + u1.x * 2 * m2 / (m1 + m2),u2.y };

			sf::Vector2f vFinal1 = rotate(v1, -angle);
			sf::Vector2f vFinal2 = rotate(v2, -angle);

			first->velocity.x = vFinal1.x;
			first->velocity.y = vFinal1.y;

			second->velocity.x = vFinal2.x;
			second->velocity.y = vFinal2.y;

		}


	}
}
