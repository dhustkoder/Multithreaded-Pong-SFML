#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "player.h"
#include "ball.h"


constexpr float winWidth = 800;
constexpr float winHeight = 420;
int main()
{
	sf::RenderWindow win({ (unsigned)winWidth, (unsigned)winHeight }, "sfml");
	Player player1(winWidth, winHeight, 30.0F, 80.0F);
	win.setFramerateLimit(60);


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
		win.draw(player1);
		win.draw(ball);
		win.display();
	}


}