#include <thread>
#include <atomic>
#include <memory>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "processes.h"
#include "gamewindow.h"
#include "gamescore.h"
#include "player.h"
#include "cpu.h"
#include "ball.h"
#include "utility.h"




// main global variables
static Player &player1 = *(new Player);

static std::atomic<bool> isGameRunning(false);
static std::atomic<bool> doInputAndCollisionProcess(false);


// functions declaration
void process_input_and_collision(Ball& ball, Paddle& adverPaddle) noexcept;
void mainGameLoop(GameWindow& mainWin, const Ball& ball, const Paddle& adverPaddle) noexcept;

// main functions
void startGame(GameMode mode)
{
	auto mainWindowUnique = GameWindow::makeUniqueWindow();
	player1.setPosition(Shape::Position::LeftSide);
	
	// create the rest of game objects
	auto ballUnique = std::make_unique<Ball>();
	std::unique_ptr<Paddle> adverPaddleUnique;

	switch (mode)
	{
		case GameMode::SinglePlayer:
			adverPaddleUnique = std::make_unique<Cpu>(*ballUnique);
			adverPaddleUnique->setPosition(Shape::Position::RightSide);
			break;
		
		case GameMode::MultiplayerLocal:
			adverPaddleUnique = std::make_unique<Player>();
			adverPaddleUnique->setPosition(Shape::Position::RightSide);
			static_cast<Player&>(*adverPaddleUnique).setKeys(sf::Keyboard::Numpad8, sf::Keyboard::Numpad2);
			break;
	}

	// start game and input and collision thread
	isGameRunning = true;
	auto input_and_collision_thread =
		std::make_unique<std::thread>(process_input_and_collision,
			std::ref(*ballUnique), std::ref(*adverPaddleUnique));

	// call mainGameLoop, the loop which controlls window and thread access
	mainGameLoop(*mainWindowUnique, *ballUnique, *adverPaddleUnique);

	// stop game wait thread to return, exit
	isGameRunning = false;
	input_and_collision_thread->join();

}



void mainGameLoop(GameWindow& mainWin, const Ball& ball, const Paddle& adverPaddle) noexcept
{
	while (mainWin.isOpen())
	{
		doInputAndCollisionProcess = true;
		mainWin.clear(sf::Color::Black);
		mainWin.updateWindowState();
		
		while (doInputAndCollisionProcess)
			std::this_thread::yield();


		mainWin.drawAndDisplay(player1, adverPaddle, ball);
	}
}



void process_input_and_collision(Ball& ball, Paddle& adverPaddle) noexcept
{
	//load sound to memory
	auto soundBuff = std::make_unique<sf::SoundBuffer>();
	soundBuff->loadFromFile("../Resources/ballsound");
	auto sound = std::make_unique<sf::Sound>(*soundBuff); // sound for ball impact

	while (isGameRunning)
	{
		if(doInputAndCollisionProcess)
		{
			updateObjects(player1, adverPaddle, ball);

			if (ball.collided(player1)) 
			{
				sound->play();
				ball.treatCollision();
			//	player1.tremble(7);
			}
			
			else if (ball.collided(adverPaddle)) {
				sound->play();
				ball.treatCollision();
			}
			
			doInputAndCollisionProcess = false; // wait until next round...
		}
		
		else
			std::this_thread::yield();
	}
}





