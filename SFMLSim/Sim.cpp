#include "Sim.h"
#include "Particle.h"
#include <iostream>
std::istream& operator>>(std::istream& is, Direction& d) {
    std::string tmp;
    is >> tmp;
    if (tmp == "right") {
        d = Direction::right;
    }
    else if (tmp == "left") {
        d = Direction::left;
    }
    else if (tmp == "up") {
        d = Direction::up;
    }
    else if (tmp == "down") {
        d = Direction::down;
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, Direction& d) {
    if (d == Direction::up)
        return os << "up";
    else if (d == Direction::down)
        return os << "down";
    else if (d == Direction::right)
        return os << "right";
    else if (d == Direction::left)
        return os << "left";
    return os;
}
Sim::Sim() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
	window = new sf::RenderWindow(sf::VideoMode(800,800),"Particles", sf::Style::Default, settings);
}

void Sim::draw() {
    //get user particle num, get user force
    std::cout << "Type number of particles and initial direction of force (up,down, left, right)\n";
    int numOfP{0};
    Direction d;
    std::cin >> numOfP >> d;
    std::cout << d;
 
    window->setFramerateLimit(60);
    Particle p1{ sf::Vector2f{405,200},10.0f};
    Particle p2{ sf::Vector2f{500,200},100.0f };
    sf::CircleShape circle{ 5.0f };
    circle.setPosition(p1.coord);
    p1.circle = circle;
    sf::CircleShape circle2{ 10.0f };
    circle2.setPosition(p2.coord);
    p2.circle = circle2;

    sf::CircleShape test{ 5.0f };
    circle.setPosition(sf::Vector2f{0,10});

    float x = 300.f;
    float y = 200.0f;
    std::vector<Particle*> buffer;
  //  buffer.push_back(*p1);
  //  buffer.push_back(*p2);
    for (float i = 0; i < numOfP; ++i) {
        Particle* tmp=  new Particle{ sf::Vector2f{x ,y},30.0f};
        sf::CircleShape circle { 5.0f };
        circle.setPosition(tmp->coord);
        tmp->circle = circle;
        if (x >= 700) {
            x = 0;
            ++y;
        }
        else
            x += 11;
       buffer.push_back(tmp);
    }
    for (Particle* p : buffer) {
        int force = 10.0f * p->getMass();
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
    //ball bottom
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f{0,700}),
        sf::Vertex(sf::Vector2f{800,700})
    };
    //ball top
    sf::Vertex line2[] =
    {
        sf::Vertex(sf::Vector2f{0,100}),
        sf::Vertex(sf::Vector2f{800,100})
    };
    //ball left
    sf::Vertex line3[] =
    {
        sf::Vertex(sf::Vector2f{100,100}),
        sf::Vertex(sf::Vector2f{100,700})
    };
    //ball right
    sf::Vertex line4[] =
    {
        sf::Vertex(sf::Vector2f{700,100}),
        sf::Vertex(sf::Vector2f{700,700})
    };
    sf::Clock clock;
    sf::Time time_per_frame = sf::seconds(1.f / 60.f);
    sf::Time time_since_last_update = sf::Time::Zero;
    sf::Time time_sleep;
     float dt = 1.0f / 60.0f;
    dt = 0.12f;
    while (window->isOpen())
    {
      //  time_sleep = sf::Time::Zero;

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for (Particle* p : buffer) {
                    p->acceleration.y *= -1.0f;
                }
                
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                for (Particle* p : buffer) {
                    if(p->acceleration.x==0)
                        p->acceleration.x = 1.0f;
                    else
                        p->acceleration.x *= -1.0f;
                }

            }
        }

        for (Particle* p : buffer) {
            p->calculation(dt, buffer);
        }
        window->clear();
        for (Particle* p : buffer) {
            window->draw(p->circle);
        }
 
        window->draw(line,2,sf::Lines);
        window->draw(line2, 2, sf::Lines);
        window->draw(line3, 2, sf::Lines);
        window->draw(line4, 2, sf::Lines);
        window->display();
    }

}