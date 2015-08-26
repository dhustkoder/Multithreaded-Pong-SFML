#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>




constexpr size_t WIDTH = 800;
constexpr size_t HEIGHT = 600;
constexpr float division(const float x, const float y)
{
	return x/y;

}
constexpr float multi(const float x, const float y)
{

	return x*y;
}


constexpr float ballRadius = 20.f;
constexpr float ballVelocity = 3.f;








struct Ball
{
	

	sf::Vector2f velocity { ballVelocity, ballVelocity } ;
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
		if(right() > WIDTH)
			velocity.x = -ballVelocity;
		else if(left() < 0)
			velocity.x = ballVelocity;
		if(top() < 0)
			velocity.y = ballVelocity;
		else if(bottom() > HEIGHT)
			velocity.y = -ballVelocity;
		
		shape.move(velocity);
	}
	
	float x() 		const 		{ return shape.getPosition().x; 				}
	float y() 		const		{ return shape.getPosition().y; 				} 
	float top() 	const 		{ return y() - division(ballRadius,2.f); 		}
	float bottom() 	const 		{ return y() + ballRadius;						}
	float left() 	const 		{ return x() - division(ballRadius,2.f); 		}
	float right() 	const 		{ return x() + ballRadius;						}

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
