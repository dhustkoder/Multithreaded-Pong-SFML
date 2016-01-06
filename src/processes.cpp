#include <thread>
#include <atomic>
#include <memory>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "processes.h"
#include "gamewindow.h"
#include "gamescore.h"
#include "utility.h"
#include "player.h"
#include "cpu.h"
#include "ball.h"

// global constants (compile time)
constexpr unsigned winWidth = 800;
constexpr unsigned winHeight = 420;


// main global variables
static Player player1;

static std::atomic<bool> isGameRunning(false);
static std::atomic<bool> doInputAndCollisionProcess(false);


// functions declaration
void process_input_and_collision(Ball& ball, Shape& shp) noexcept;
void mainGameLoop(GameWindow& mainWin, const Shape& shp, const Ball& ball) noexcept;

// main functions
void startGame(GameMode mode)
{
	auto mainWindowUnique = GameWindow::makeUniqueWindow(sf::VideoMode(winWidth, winHeight, 32), "Multithread-Pong-SFML");
	player1.setPosition(Shape::Position::LeftSide);

	// create the rest of game objects
	auto ballUnique = std::make_unique<Ball>();
	std::unique_ptr<Shape> adverShapeUnique;

	if (mode == GameMode::SinglePlayer) {
		adverShapeUnique = std::make_unique<Cpu>(*ballUnique);
		adverShapeUnique->setPosition(Shape::Position::RightSide);
	}

	else if (mode == GameMode::MultiplayerLocal) {
		adverShapeUnique = std::make_unique<Player>();
		adverShapeUnique->setPosition(Shape::Position::RightSide);
		static_cast<Player*>(adverShapeUnique.get())->setKeys(sf::Keyboard::Numpad8, sf::Keyboard::Numpad2);
	}

	// start game and input and collision thread
	isGameRunning = true;
	auto input_and_collision_thread =
		std::make_unique<std::thread>(process_input_and_collision,
			std::ref(*ballUnique), std::ref(*adverShapeUnique));

	// call mainGameLoop, the loop which controlls window and thread access
	mainGameLoop(*mainWindowUnique, *adverShapeUnique, *ballUnique);

	// stop game wait thread to return, exit
	isGameRunning = false;
	input_and_collision_thread->join();

}



void mainGameLoop(GameWindow& mainWin, const Shape& adverShape, const Ball& ball) noexcept
{
	while (mainWin.isOpen())
	{
		doInputAndCollisionProcess = true;
		mainWin.updateWindowState();
		
		while (doInputAndCollisionProcess)
			std::this_thread::yield();

		GameScore::update(ball);
		GameScore::display();

		mainWin.drawAndDisplay(player1, adverShape, ball);
	}
}



void process_input_and_collision(Ball& ball, Shape& shp) noexcept
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





