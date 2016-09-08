#include <iostream>
#include <SFML/Graphics.hpp>

constexpr const int WIN_WIDTH {512};
constexpr const int WIN_HEIGHT {256};

struct Position {
	float top, bottom, left, right;
};

struct Ball : sf::CircleShape {
	static constexpr const float RADIUS {10.5};
	static constexpr const float VELOCITY {7.5};
	Ball() : sf::CircleShape(RADIUS) {
		setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
		setOrigin(RADIUS, RADIUS);
	}
};

struct Paddle : sf::RectangleShape {
	static constexpr const float WIDTH {15};
	static constexpr const float HEIGHT {60};
	static constexpr const float VELOCITY {4.5};
	Paddle(sf::Vector2f pos) : sf::RectangleShape({WIDTH, HEIGHT}) {
		setPosition(pos);
		setOrigin(WIDTH / 2, HEIGHT / 2);
	}
};

struct GameObjects {
	Ball ball;
	Paddle player {{Paddle::WIDTH, WIN_HEIGHT / 2}};
	Paddle cpu {{WIN_WIDTH - Paddle::WIDTH, WIN_HEIGHT / 2}};
};

struct Velocities {
	sf::Vector2f ball {Ball::VELOCITY, Ball::VELOCITY};
	float player {0};
	float cpu {0};
};

struct Positions {
	Position ball;
	Position player;
	Position cpu;
};



static void update_positions(const GameObjects& objects, Positions* const positions)
{
	const auto update =
	[](const sf::Shape& shape, Position& pos, float width, float height) {
		pos.right = shape.getPosition().x + width / 2.f;
		pos.left = shape.getPosition().x - width / 2.f;
		pos.bottom = shape.getPosition().y + height / 2.f;
		pos.top = shape.getPosition().y - height / 2.f;
	};
	
	update(objects.ball, positions->ball, Ball::RADIUS, Ball::RADIUS);
	//update(objects.player, positions->player, Paddle::WIDTH, Paddle::HEIGHT);
	//update(objects.cpu, positions->cpu, Paddle::WIDTH, Paddle::HEIGHT);
}

static void update_objects(GameObjects* const objects,
                           Positions* const positions,
                           Velocities* const velocities)
{
	update_positions(*objects, positions);
	
	auto& ballPos = positions->ball;
	auto& ballVel = velocities->ball;
	
	if (ballPos.left < 0)
		ballVel.x = -ballVel.x;
	else if (ballPos.right > WIN_WIDTH)
		ballVel.x = -ballVel.x;
	if (ballPos.top < 0)
		ballVel.y = -ballVel.y;
	else if (ballPos.bottom > WIN_HEIGHT)
		ballVel.y = -ballVel.y;
	
	
	objects->ball.setPosition(objects->ball.getPosition() + ballVel);
}



int main()
{
	GameObjects objects;
	Positions positions;
	Velocities velocities;
	sf::RenderWindow window({WIN_WIDTH, WIN_HEIGHT}, "PongCpp");
	sf::Event event;
	
	window.setFramerateLimit(15);
	
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
		//window.draw(objects.player);
		//window.draw(objects.cpu);
		
		window.display();
	}

	return 0;
}













