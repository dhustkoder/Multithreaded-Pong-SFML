#include <cmath>
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
	static constexpr const float VELOCITY {8.5};
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
	sf::Vector2f ball {Ball::VELOCITY, Ball::VELOCITY / 2};
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
		const auto shapePos = shape.getPosition();
		pos.right = shapePos.x + width / 2.f;
		pos.left = shapePos.x - width / 2.f;
		pos.bottom = shapePos.y + height / 2.f;
		pos.top = shapePos.y - height / 2.f;
	};
	
	update(objects.ball, positions->ball, Ball::RADIUS, Ball::RADIUS);
	update(objects.player, positions->player, Paddle::WIDTH, Paddle::HEIGHT);
	update(objects.cpu, positions->cpu, Paddle::WIDTH, Paddle::HEIGHT);
}


static void update_objects(GameObjects* const objects,
                           Positions* const positions,
                           Velocities* const velocities)
{
	using std::abs;
	
	update_positions(*objects, positions);
	
	const auto collision = [](auto& p1, auto& p2) {
		return (p1.right >= p2.left && p1.left <= p2.right)
		&& (p1.bottom >= p2.top && p1.top <= p2.bottom);
	};
	
	const auto& ballPos = positions->ball;
	auto& ballVel = velocities->ball;
	
	if (collision(ballPos, positions->player) ||
	    collision(ballPos, positions->cpu))
		ballVel.x = -ballVel.x;
	else if (ballPos.left < 0)
		ballVel.x = abs(ballVel.x);
	else if (ballPos.right > WIN_WIDTH)
		ballVel.x = -abs(ballVel.x);
	if (ballPos.top < 0)
		ballVel.y = abs(ballVel.y);
	else if (ballPos.bottom > WIN_HEIGHT)
		ballVel.y = -abs(ballVel.y);
	
	objects->ball.setPosition(objects->ball.getPosition() + ballVel);
	
	if (velocities->player) {
		auto& player = objects->player;
		const auto& playerVel = velocities->player;
		const auto& shapePos = player.getPosition();
		player.setPosition(shapePos.x, shapePos.y + playerVel);
	}
}




static void process_input(Position* const playerPos,
                          float* const playerVel)
{
	using sf::Keyboard;
	if (playerPos->top > 0 && Keyboard::isKeyPressed(Keyboard::W))
		*playerVel = -Paddle::VELOCITY;
	else if (playerPos->bottom < WIN_HEIGHT && Keyboard::isKeyPressed(Keyboard::S))
		*playerVel = Paddle::VELOCITY;
	else
		*playerVel = 0;
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
			switch (event.type) {
			case sf::Event::KeyPressed: /*fall*/
			case sf::Event::KeyReleased:
				process_input(&positions.player, &velocities.player);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		
		update_objects(&objects, &positions, &velocities);
		
		window.clear(sf::Color::Red);
		window.draw(objects.ball);
		window.draw(objects.player);
		window.draw(objects.cpu);
		window.display();
	}

	return 0;
}













