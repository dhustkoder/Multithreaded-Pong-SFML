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
static Player player1(winWidth, winHeight, 30.0F, 80.0F);
static sf::Event winEvent;

// thread purpose globals
static std::atomic<bool> isGameRunning(false);
static std::atomic<bool> doInputAndCollisionProcess(false);


// functions
void process_input_and_collision(Ball& ball, Shape& shp);
void mainGameLoop(sf::RenderWindow& mainWin, const Shape& shp, const Ball& ball);

template<typename ...Ts>
inline void drawAndDisplay(sf::RenderWindow &win, Ts&& ...args) {
	std::initializer_list<int>
	{
		(win.draw(std::forward<Ts>(args)), 0)...
	};
	
	win.display();
}

template<typename ...Ts>
inline void updateObjects(Ts&& ...args) {
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




// game
void startGame(GameMode mode)
{
	auto mainWindow =
		std::make_unique<sf::RenderWindow>(sf::VideoMode(winWidth, winHeight, 32), "Multithread-Pong-SFML");

	player1.setPosition(5.f, cexpr_div((float)winHeight, 2.f));
	winEvent.type = sf::Event::GainedFocus;
	mainWindow->setFramerateLimit(60);


	if (mode == GameMode::SinglePlayer)
	{
		isGameRunning = true;
		auto ballUnique = std::make_unique<Ball>(winWidth, winHeight);
		auto cpuPaddleUnique = std::make_unique<Cpu>(winWidth, winHeight, 30.0f, 80.0f, *ballUnique);
		cpuPaddleUnique->setPosition(cexpr_sub(winWidth, 5u), cexpr_div(winHeight, 2u));

		auto input_and_collision_thread =
			std::make_unique<std::thread>(process_input_and_collision,
				std::ref(*ballUnique.get()), std::ref(*cpuPaddleUnique.get()));

		mainGameLoop(*mainWindow, *cpuPaddleUnique, *ballUnique);
		isGameRunning = false;
		input_and_collision_thread->join();
	}

	else if (mode == GameMode::MultiplayerLocal)
	{
		isGameRunning = true;
		auto ballUnique = std::make_unique<Ball>(winWidth, winHeight);
		auto player2Unique = std::make_unique<Player>(winWidth, winHeight, 30.0F, 80.0F);
		player2Unique->setPosition(cexpr_sub((float)winWidth, 5.f), cexpr_div((float)winHeight, 2.f));
		player2Unique->setKeys(sf::Keyboard::Numpad8, sf::Keyboard::Numpad2);

		auto input_and_collision_thread =
			std::make_unique<std::thread>(process_input_and_collision,
				std::ref(*ballUnique), std::ref(*player2Unique));

		mainGameLoop(*mainWindow, *player2Unique, *ballUnique);

		isGameRunning = false;
		input_and_collision_thread->join();
	}



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

			if (isColliding(player1, ball))
			{
				sound->play();
				ball.treatCollisionWith(player1);
			}
			else if (isColliding(shp, ball))
			{
				sound->play();
				ball.treatCollisionWith(shp);
			}
			
			doInputAndCollisionProcess = false; // wait until next round...
		}
		
		else
			std::this_thread::yield();
	}


}





