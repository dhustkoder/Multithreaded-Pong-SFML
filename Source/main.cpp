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
	static constexpr const float VELOCITY {8.8};
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
	sf::Vector2f ball {Ball::VELOCITY, Ball::VELOCITY / 4};
	float player {0};
	float cpu {0};
};

struct Positions {
	Position ball;
	Position player;
	Position cpu;
};

static void update_positions(const Shapes& shapes, Positions* positions);
static void update_velocities(const Positions& positions, Velocities* velocities);
static void update_shapes(const Velocities& velocities, Shapes* shapes);
static void process_input(float* playerVel);


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
				process_input(&velocities.player);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		
		update_positions(shapes, &positions);
		update_velocities(positions, &velocities);
		update_shapes(velocities, &shapes);
		
		window.clear(sf::Color::Red);
		window.draw(shapes.ball);
		window.draw(shapes.player);
		window.draw(shapes.cpu);
		window.display();
	}

	return 0;
}




void update_positions(const Shapes& shapes, Positions* const positions)
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


void update_velocities(const Positions& positions, Velocities* const velocities)
{
	using std::abs;
	
	const auto& ballPos = positions.ball;
	auto& ballVel = velocities->ball;
	
	const auto collided = [&ballPos](const auto& paddle) {
		return (ballPos.right >= paddle.left && ballPos.left <= paddle.right)
		&& (ballPos.bottom >= paddle.top && ballPos.top <= paddle.bottom);
	};
	
	if (collided(positions.player) || collided(positions.cpu))
		ballVel.x = -ballVel.x;
	else if (ballPos.left < 0)
		ballVel.x = abs(ballVel.x);
	else if (ballPos.right > WIN_WIDTH)
		ballVel.x = -abs(ballVel.x);
	
	if (ballPos.top < 0)
		ballVel.y = abs(ballVel.y);
	else if (ballPos.bottom > WIN_HEIGHT)
		ballVel.y = -abs(ballVel.y);
	
	if (velocities->player) {
		const auto playerTop = positions.player.top;
		const auto playerBottom = positions.player.bottom;
		auto& playerVel = velocities->player;
		
		if (playerVel < 0 && playerTop <= 0)
			playerVel = 0;
		else if (playerVel > 0 && playerBottom >= WIN_HEIGHT)
			playerVel = 0;
	}
}


void update_shapes(const Velocities& velocities, Shapes* const shapes)
{
	using std::abs;
	if (velocities.ball != sf::Vector2f{0, 0})
		shapes->ball.setPosition(shapes->ball.getPosition() + velocities.ball);
	
	const auto playerVel = velocities.player;
	if (playerVel) {
		const auto shapePos = shapes->player.getPosition();
		shapes->player.setPosition(shapePos.x, shapePos.y + playerVel);
	}
}


void process_input(float* const playerVel)
{
	using sf::Keyboard;
	if (Keyboard::isKeyPressed(Keyboard::W))
		*playerVel = -Paddle::VELOCITY;
	else if (Keyboard::isKeyPressed(Keyboard::S))
		*playerVel = Paddle::VELOCITY;
	else
		*playerVel = 0;
}








