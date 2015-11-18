#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "player.h"
#include "ball.h"

constexpr float winWidth = 800;
constexpr float winHeight = 420;



int main()
{
	sf::RenderWindow win({ (unsigned)winWidth, (unsigned)winHeight }, "sfml");
	win.setFramerateLimit(60);
	Player player1(winWidth, winHeight, 10.0F, 80.0F);

	player1.setPosition(5.0F, winHeight / 2);

	Ball ball(winWidth, winHeight);
	sf::Event winEvent;
	while (win.isOpen())
	{
		win.pollEvent(winEvent);
		if (winEvent.type == winEvent.Closed)
			win.close();

		win.clear(sf::Color::Black);
		player1.update();
		ball.update();

		if (Shape::isColliding(player1, ball))
		{
			// TODO: play song
			ball.treatCollision(player1);
		}
		win.draw(player1);
		win.draw(ball);
		win.display();
	}


}