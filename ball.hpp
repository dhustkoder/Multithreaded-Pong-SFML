#ifndef BALL_HPP
#define BALL_HPP

constexpr float ballRadius 		= 20.f;
constexpr float ballVelocity 	= 3.f;

struct Ball
{
	

	sf::Vector2f velocity { ballVelocity, ballVelocity } ;
	sf::CircleShape shape;
	Ball()
	{
		shape.setRadius(ballRadius);
		shape.setPosition(static_division(WIDTH,2), static_division(HEIGHT,2));
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(static_division(ballRadius,2),static_division(ballRadius,2));
					
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
	
	float x() 		const 		{ return shape.getPosition().x; 					}
	float y() 		const		{ return shape.getPosition().y; 					} 
	float top() 	const 		{ return y() - static_division(ballRadius,2.f); 	}
	float bottom() 	const 		{ return y() + ballRadius; 							}
	float left() 	const 		{ return x() - static_division(ballRadius,2.f); 	}
	float right() 	const 		{ return x() + ballRadius; 							}

};



#endif