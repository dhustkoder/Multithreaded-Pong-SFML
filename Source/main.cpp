#include <iostream>
#include <SFML/Graphics.hpp>

constexpr const int WIN_WIDTH = 512;
constexpr const int WIN_HEIGHT = 256;

constexpr const float BALL_RADIUS = 10.5;
constexpr const float BALL_VELOCITY = 7.5;

struct Position : sf::Vector2f {
	using sf::Vector2f::Vector2;
};
struct Velocity : sf::Vector2f {
	using sf::Vector2f::Vector2;
};


struct GameObjects {
	sf::CircleShape ball {BALL_RADIUS};
};

struct Positions {
	Position ball { WIN_WIDTH / 2, WIN_HEIGHT / 2 };
};

struct Velocities {
	Velocity ball { BALL_VELOCITY, BALL_VELOCITY };
};


static void update_objects(GameObjects* objects, Positions* positions, Velocities* velocities);


int main()
{
	GameObjects objects;
	Positions positions;
	Velocities velocities;
	
	sf::RenderWindow window({WIN_WIDTH, WIN_HEIGHT}, "PongCpp");
	sf::Event event;
	
	window.setFramerateLimit(60);
	
	while (window.isOpen()) {
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
		}
		
		update_objects(&objects, &positions, &velocities);
		
		window.clear(sf::Color::Red);
		
		window.draw(objects.ball);
		
		window.display();
	}

	return 0;
}











static void update_objects(GameObjects* const objects,
                           Positions* const positions,
                           Velocities* const velocities)
{
	{
		auto& ballpos = positions->ball;
		auto& ballvel = velocities->ball;
		
		if (ballpos.x < 0)
			ballvel.x = -ballvel.x;
		else if (ballpos.x > WIN_WIDTH)
			ballvel.x = -ballvel.x;
		if (ballpos.y < 0)
			ballvel.y = -ballvel.y;
		else if (ballpos.y > WIN_HEIGHT)
			ballvel.y = -ballvel.y;
		
		ballpos += ballvel;
	}


	objects->ball.setPosition(positions->ball);
}






