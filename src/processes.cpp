#include <thread>
#include <atomic>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "processes.h"
#include "utility.h"
#include "player.h"
#include "cpu.h"
#include "ball.h"

// global constants (compile time)
constexpr unsigned winWidth = 800;
constexpr unsigned winHeight = 420;


// main global variables
static Player player1;
static sf::Event winEvent;

// thread purpose globals
static std::atomic<bool> isGameRunning(false);
static std::atomic<bool> doInputAndCollisionProcess(false);


// functions declaration
void process_input_and_collision(Ball& ball, Shape& shp);
void mainGameLoop(sf::RenderWindow& mainWin, const Shape& shp, const Ball& ball);

// template functions for window processes
template<typename ...Ts>
inline void drawAndDisplay(sf::RenderWindow &win, Ts&& ...args) 
{
	(void)std::initializer_list<int>
	{
		(win.draw(std::forward<Ts>(args)), 0)...
	};

	win.display();
	

}

template<typename ...Ts>
inline void updateObjects(Ts&& ...args) 
{
	return (void)std::initializer_list<int>
	{
		(std::forward<Ts>(args).update(), 0)...
	};
}

// returns true if window was closed
bool updateWindowState(sf::RenderWindow& mainWin)
{
	mainWin.clear(sf::Color::Black);
	mainWin.pollEvent(winEvent);
	
	if (winEvent.type == sf::Event::Closed) {
		mainWin.close();
		return true;
	}

	return false;
}


// main functions
void startGame(GameMode mode)
{
	auto mainWindow =
		std::make_unique<sf::RenderWindow>(sf::VideoMode(winWidth, winHeight, 32), "Multithread-Pong-SFML");

	winEvent.type = sf::Event::GainedFocus;
	mainWindow->setFramerateLimit(60);
	mainWindow->setVerticalSyncEnabled(true);	
	
	Shape::informWindowSize(winWidth, winHeight);
	player1.setPosition(Shape::Position::LeftCorner);
	

	// create the rest of game objects
	auto ballUnique = std::make_unique<Ball>();
	std::unique_ptr<Shape> adverShapeUnique;

	if (mode == GameMode::SinglePlayer) {
		adverShapeUnique = std::make_unique<Cpu>(*ballUnique);
		adverShapeUnique->setPosition(Shape::Position::RightCorner);
	}

	else if (mode == GameMode::MultiplayerLocal) {
		adverShapeUnique = std::make_unique<Player>();
		adverShapeUnique->setPosition(Shape::Position::RightCorner);
		static_cast<Player*>(adverShapeUnique.get())->setKeys(sf::Keyboard::Numpad8, sf::Keyboard::Numpad2);
	}

	// start game and input and collision thread
	isGameRunning = true;
	auto input_and_collision_thread =
		std::make_unique<std::thread>(process_input_and_collision,
			std::ref(*ballUnique), std::ref(*adverShapeUnique));

	// call mainGameLoop, the loop which controlls window and thread access
	mainGameLoop(*mainWindow, *adverShapeUnique, *ballUnique);

	// stop game wait thread to return, exit
	isGameRunning = false;
	input_and_collision_thread->join();

}



void mainGameLoop(sf::RenderWindow& mainWin, const Shape& shp, const Ball& ball)
{
	while (mainWin.isOpen())
	{
		doInputAndCollisionProcess = true;
		updateWindowState(mainWin);

		while (doInputAndCollisionProcess)
			std::this_thread::yield();

		drawAndDisplay(mainWin, player1, shp, ball);
	}
}



void process_input_and_collision(Ball& ball, Shape& shp)
{
	//load sound to memory
	auto soundBuff = std::make_unique<sf::SoundBuffer>();
	soundBuff->loadFromFile("../Resources/ballsound");
	auto sound = std::make_unique<sf::Sound>(*soundBuff); // sound for ball impact

	while (isGameRunning)
	{
		if(doInputAndCollisionProcess)
		{
			updateObjects(player1, shp, ball);

			if (isColliding(player1, ball)) {
				sound->play();
				ball.treatCollisionWith(player1);
			}
			
			else if (isColliding(shp, ball)) {
				sound->play();
				ball.treatCollisionWith(shp);
			}
			
			doInputAndCollisionProcess = false; // wait until next round...
		}
		
		else
			std::this_thread::yield();
	}
}





