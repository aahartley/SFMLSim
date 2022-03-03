#include "ParticleGenerator.h"

std::vector<Particle*> ParticleGenerator::generate(int numOfP,Direction d) {
    float x = 300.f;
    float y = 200.0f;
    for (float i = 0; i < numOfP; ++i) {
        Particle* tmp = new Particle{ sf::Vector2f{x ,y},30.0f };
        sf::CircleShape circle{ 5.0f };
        if (x >= 680) {
            x = 300;
            y += 20;
            if (y >= 690)
                break;
        }
        else {
            x += 12;

        }
        circle.setPosition(tmp->coord);
        tmp->circle = circle;
        particles.push_back(tmp);
    }
    for (Particle* p : particles) {
        float force = 10.0f * p->getMass();
        switch (d) {
        case(Direction::up): {
            p->acceleration.y -= force / p->getMass();
            break;
        }
        case(Direction::down): {
            p->acceleration.y += force / p->getMass();
            break;
        }
        case(Direction::left): {
            p->acceleration.x -= force / p->getMass();
            break;
        }
        case(Direction::right): {
            p->acceleration.x += force / p->getMass();
            break;
        }
        default:
            break;
        }
    }
    return particles;
}
void ParticleGenerator::path() {
  //  Matrix m{};
  //  Matrix2 t{};
  //  m.setData(particles);
  //  m.multiply(t);
}