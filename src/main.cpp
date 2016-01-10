
#ifdef __linux__
#include <X11/Xlib.h>
#undef None
#endif

#include "processes.h"

#include <SFML/Graphics.hpp>
#include "gamewindow.h"
#include "particlesystem/particle.h"

int main()
{

#ifdef __linux__
	XInitThreads(); // prevent X11 threads error
#endif

	// single player and multiplayer test
	//startGame(GameMode::SinglePlayer);
	//startGame(GameMode::MultiplayerLocal);


	auto mainWinUnique = GameWindow::makeUniqueWindow();

	auto *mainWin = mainWinUnique.get();
	
	sf::Image image;
	sf::Texture texture;
	
	image.loadFromFile("fireball.png");

	sf::IntRect rect;
	rect.width = 64;
	rect.height = 64;
	texture.loadFromImage(image, rect);
	texture.setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(static_cast<sf::Vector2f>(mainWin->getSize()) / 2.f);
	int textureFrameCounter = 0;
	while(mainWin->isOpen())
	{
		
		
		mainWin->clear(sf::Color::Black);
		mainWin->updateWindowState();
		mainWin->drawAndDisplay(sprite);
		
		++textureFrameCounter;
		if (textureFrameCounter > 8)
			textureFrameCounter = 0;

		rect.left = 64 * textureFrameCounter;
		texture.loadFromImage(image, rect);
	}

}

