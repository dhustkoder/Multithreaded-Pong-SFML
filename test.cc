
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>




constexpr size_t WIDTH = 800;
constexpr size_t HEIGHT = 600;
constexpr size_t division(size_t x, size_t y)
{
	return x/y;

}



constexpr float ballRadius = 20.f;
constexpr float ballVelocity = 3.f;


struct Ball
{
	

	sf::Vector2f velocity { ballVelocity, 0 } ;
	sf::CircleShape shape;
	Ball()
	{
		shape.setRadius(ballRadius);
		shape.setPosition(division(WIDTH,2), division(HEIGHT,2));
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(division(ballRadius,2),division(ballRadius,2));
					
	}

	void move()
	{
		if(getX() > WIDTH)
			velocity.x = -ballVelocity;
		else if(getX() < 0)
			velocity.x = ballVelocity;

		shape.move(velocity);
	}
	
	float getX() const 	{ return shape.getPosition().x - division(ballRadius,2); }
	float getY() const	{ return shape.getPosition().y; } 



};






int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "sfml");
	window.setFramerateLimit(60);
	Ball ball;
	while(window.isOpen())
	{
		window.clear(sf::Color::Black);
		sf::Event ev;

		if(window.pollEvent(ev))
		{
			if(ev.type == sf::Event::Closed)
				window.close();

			
		
		}
		ball.move();
		window.draw(ball.shape);
		window.display();

	}






}
