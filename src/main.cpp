#include "pch.h"
#include "timewrp.h"


int main()
{

#ifdef __linux__
	XInitThreads(); // prevent X11 threads error
#endif


	// single player and multiplayer test
	startGame(GameMode::SinglePlayer);
	//startGame(GameMode::MultiplayerLocal);
	//ballDebug();


	/*
	auto mainWinUnique = GameWindow::makeUniqueWindow();
	auto *mainWin = mainWinUnique.get();

	Shape rect1({ 40 / 2, 40 / 2 }, std::make_unique<sf::RectangleShape>(sf::Vector2f(40, 40 ))),
		rect2({ 40 / 2, 40 / 2 }, std::make_unique<sf::RectangleShape>(sf::Vector2f(40, 40)));

	rect1.getShape().setFillColor(sf::Color::Red);
	rect1.setPosition(0, 0);
	
	rect2.getShape().setFillColor(sf::Color::Blue);
	rect2.setPosition(GameWindow::Width / 2, GameWindow::Height / 2);

	while(mainWin->isOpen())
	{
		
		
		mainWin->clear(sf::Color::Black);
		mainWin->updateWindowState();
	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			
			rect1.getShape().move(-1,-1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

			rect1.getShape().move(1,-1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			
			rect1.getShape().move(-1,1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			
			rect1.getShape().move(1,1);
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			
			rect1.getShape().move(0,-1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			
			rect1.getShape().move(0,1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			
			rect1.getShape().move(-1,0);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	
			rect1.getShape().move(1,0);
		}

		if (rect1.collided(rect2)) {
			static auto counter = 0;
			std::cout << "collided" << std::endl;
			if (++counter > 10) {
				system("cls");
				counter = 0;
			}
			
		}
		mainWin->drawAndDisplay(rect1, rect2);
	}
	*/
}

