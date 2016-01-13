
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
	startGame(GameMode::MultiplayerLocal);

	/*
	// Tests
	auto mainWinUnique = GameWindow::makeUniqueWindow();
	auto *mainWin = mainWinUnique.get();
	
	enum { Left, LeftUp, Up, RightUp, Right, DownRight, Down, DownLeft };
	sf::IntRect spritePos[] = 
	{ 
		{ 0,0, 64,64 },           { 0, 64 * LeftUp, 64, 64 },
		{ 0, 64 * Up, 64, 64 },   { 0, 64 * RightUp, 64, 64 },
		{ 0, 64 * Right, 64, 64 },{ 0, 64 * DownRight, 64, 64 },
		{ 0, 64 * Down, 64, 64 }, { 0, 64 * DownLeft, 64, 64 } 
	};

	sf::Texture texture;
	sf::IntRect rect;
	rect.width = 64;
	rect.height = 64;
	texture.loadFromFile("../Resources/balltexture");
	texture.setSmooth(true);


	sf::CircleShape _sprite(10.5);
	sf::Shape& sprite = _sprite;
	sprite.setTexture(&texture);
	sprite.setPosition(static_cast<sf::Vector2f>(mainWin->getSize()) / 2.f);


	int textureFrameCounter = 0;
	int currentDirection = 0;
	std::clock_t clk = std::clock();
	constexpr auto frameUpdateTime = CLOCKS_PER_SEC / 800;
	while(mainWin->isOpen())
	{
		
		
		mainWin->clear(sf::Color::Black);
		mainWin->updateWindowState();
	
		

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			currentDirection = LeftUp;
			sprite.move(-1,-1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			currentDirection = RightUp;
			sprite.move(1,-1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			currentDirection = DownLeft;
			sprite.move(-1,1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			currentDirection = DownRight;
			sprite.move(1,1);
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			currentDirection = Up;
			sprite.move(0,-1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			currentDirection = Down;
			sprite.move(0,1);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			currentDirection = Left;
			sprite.move(-1,0);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			currentDirection = Right;
			sprite.move(1,0);
		}


		sf::IntRect &currentRect = spritePos[currentDirection];
		
		if((std::clock() - clk) > frameUpdateTime ) 
		{
			currentRect.left = 64 * textureFrameCounter;
			++textureFrameCounter;
			if(textureFrameCounter > 7)
				textureFrameCounter = 0;

			clk = std::clock();
		}
		
		sprite.setTextureRect(currentRect);

		mainWin->drawAndDisplay(sprite);
	}
	*/
}

