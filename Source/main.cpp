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

struct Shapes {
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



static void update_positions(const Shapes& shapes, Positions* const positions)
{
	const auto update =
	[](const sf::Shape& shape, Position& pos, float width, float height) {
		const auto shapePos = shape.getPosition();
		const auto width_diff = width / 2.f;
		const auto height_diff = height / 2.f;
		pos.right = shapePos.x + width_diff;
		pos.left = shapePos.x - width_diff;
		pos.bottom = shapePos.y + height_diff;
		pos.top = shapePos.y - height_diff;
	};
	
	update(shapes.ball, positions->ball, Ball::RADIUS, Ball::RADIUS);
	update(shapes.player, positions->player, Paddle::WIDTH, Paddle::HEIGHT);
	update(shapes.cpu, positions->cpu, Paddle::WIDTH, Paddle::HEIGHT);
}


static void update_shapes(Shapes* const shapes,
                           Positions* const positions,
                           Velocities* const velocities)
{
	using std::abs;
	
	update_positions(*shapes, positions);
	
	const auto collision = [](const auto& p1, const auto& p2) {
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
	
	shapes->ball.setPosition(shapes->ball.getPosition() + ballVel);
	
	const float playerVel = velocities->player;
	if (playerVel) {
		const auto playerTop = positions->player.top;
		const auto playerBottom = positions->player.bottom;
		auto shapePos = shapes->player.getPosition();
		
		if (playerVel > 0 && playerBottom < WIN_HEIGHT)
			shapePos.y += playerVel;
		else if (playerVel < 0 && playerTop > 0)
			shapePos.y += playerVel;
		
		shapes->player.setPosition(shapePos);
	}
}


static float process_input()
{
	using sf::Keyboard;
	if (Keyboard::isKeyPressed(Keyboard::W))
		return -Paddle::VELOCITY;
	else if (Keyboard::isKeyPressed(Keyboard::S))
		return Paddle::VELOCITY;
	return 0;
}


int main()
{
	Shapes shapes;
	Positions positions;
	Velocities velocities;
	sf::RenderWindow window({WIN_WIDTH, WIN_HEIGHT}, "PongCpp");
	sf::Event event;
	
	window.setFramerateLimit(60);
	
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed: /*fall*/
			case sf::Event::KeyReleased:
				velocities.player = process_input();
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		
		update_shapes(&shapes, &positions, &velocities);
		
		window.clear(sf::Color::Red);
		window.draw(shapes.ball);
		window.draw(shapes.player);
		window.draw(shapes.cpu);
		window.display();
	}

	return 0;
}













