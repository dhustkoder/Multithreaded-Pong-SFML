
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "player.h"
#include "ball.h"

int main()
{
	sf::RenderWindow win({ 800,420 }, "sfml");
	Player player1(800, 420);
	win.setFramerateLimit(60);


	Ball ball(800 / 2, 420 / 2);
	sf::Event winEvent;

	while (win.isOpen())
	{
		win.pollEvent(winEvent);
		if (winEvent.type == winEvent.Closed)
			win.close();

		win.clear(sf::Color::Black);
		player1.update();
		ball.update();
		win.draw(player1);
		win.draw(ball);
		win.display();
	}


}