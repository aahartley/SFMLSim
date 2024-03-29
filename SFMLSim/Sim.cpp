#include "Sim.h"
#include "Particle.h"
#include <iostream>
#include "ParticleGenerator.h"
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
void Sim::draw2() {
    ParticleGenerator pg;
    std::vector<Particle*> buffer = pg.generate(1, Direction::down);
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
    Matrix matrix(buffer[0]->circle.getPosition().x, buffer[0]->circle.getPosition().y, 1);
    
    
    while (window->isOpen())
    {
        window->setFramerateLimit(5);
        //  time_sleep = sf::Time::Zero;

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for (int i = 0; i < buffer.size(); i++) {
                    buffer[i]->acceleration.y *= -1.0f;
                }


            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                for (int i = 0; i < buffer.size(); i++) {
                    if (buffer[i]->acceleration.x == 0)
                        buffer[i]->acceleration.x = 1.0f;
                    else
                        buffer[i]->acceleration.x *= -1.0f;
                }

            }
        }
        for (int i = 0; i < buffer.size(); i++) {
          //  matrix.multiply();
          //  buffer[i]->coord=(sf::Vector2f{ matrix[0][0],matrix[1][0] });
          //  buffer[i]->circle.setPosition(sf::Vector2f{ matrix[0][0],matrix[0][1] });
            
        }
        window->clear();
        for (int i = 0; i < buffer.size(); i++) {
          //  window->draw(buffer[i]->circle);
        }
        // window->draw(test);
        
        window->draw(line, 2, sf::Lines);
        window->draw(line2, 2, sf::Lines);
        window->draw(line3, 2, sf::Lines);
        window->draw(line4, 2, sf::Lines);
        window->display();
    }
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
    test.setPosition(sf::Vector2f{100,100});

    ParticleGenerator pg;
    std::vector<Particle*> buffer = pg.generate(1, Direction::down);
  //  buffer.push_back(*p1);
  //  buffer.push_back(*p2);
   
  
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
                #pragma omp parallel for num_threads(2)
                for (int i = 0; i < buffer.size(); i++) {
                    buffer[i]->acceleration.y *= -1.0f;
                    }
                
                
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                #pragma omp parallel for num_threads(2)
                for (int i = 0; i < buffer.size(); i++) {
                    if(buffer[i]->acceleration.x == 0)
                        buffer[i]->acceleration.x = 1.0f;
                    else
                        buffer[i]->acceleration.x *= -1.0f;
                }

            }
        }
        #pragma omp parallel for num_threads(5) schedule(static)
        for (int i = 0; i < buffer.size();i++) {
            buffer[i]->calculation(dt, buffer);
        }
        window->clear();
        for (int i = 0; i < buffer.size(); i++) {
            window->draw(buffer[i]->circle);
        }
       // window->draw(test);
        window->draw(line,2,sf::Lines);
        window->draw(line2, 2, sf::Lines);
        window->draw(line3, 2, sf::Lines);
        window->draw(line4, 2, sf::Lines);
        window->display();
    }

}