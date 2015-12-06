#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "player.h"
#include "ball.h"

constexpr float winWidth = 800;
constexpr float winHeight = 420;

Player player1(winWidth, winHeight, 30.0F, 80.0F);
Player player2(winWidth, winHeight, 30.0F, 80.0F);
Ball ball(winWidth, winHeight);

std::atomic<bool> isGameRunning(false);
std::atomic<bool> doInputAndCollisionProcess(false);


void process_input_and_collision()
{
	//load sound to memory
	auto soundBuff = std::make_unique<sf::SoundBuffer>();
	soundBuff->loadFromFile("../Resources/ballsound");
	auto sound = std::make_unique<sf::Sound>();
	sound->setBuffer(*soundBuff); // sound for ball impact

	while (isGameRunning)
	{
		if(doInputAndCollisionProcess)
		{

			player1.update();
			player2.update();
			ball.update();

			
			if (Shape::isColliding(player1, ball))
			{
				sound->play();
				ball.treatCollisionWith(player1);
			}
			else if (Shape::isColliding(player2, ball))
			{
				sound->play();
				ball.treatCollisionWith(player2);
			}
			doInputAndCollisionProcess = false;
		}
		else
			std::this_thread::yield();
	}


}


int main()
{
	sf::RenderWindow win({ (unsigned)winWidth, (unsigned)winHeight }, "sfml");
	sf::Event winEvent;

	winEvent.type = sf::Event::GainedFocus;
	win.setFramerateLimit(60);
	win.setVerticalSyncEnabled(true);

	player1.setPosition(5.0F, winHeight / 2);
	player2.setPosition(winWidth - 5.0F, winHeight / 2);
	
	// start game and extra thread
	isGameRunning = true;
	auto input_and_collision_thread = std::make_unique<std::thread>(process_input_and_collision);
	
	while (win.isOpen())
	{
		doInputAndCollisionProcess = true;

		win.clear(sf::Color::Black);
		win.pollEvent(winEvent);

		if (winEvent.type == sf::Event::Closed)
		{
			win.close();
			break;
		}


		while(doInputAndCollisionProcess)
			std::this_thread::yield();

		
		win.draw(player1);
		win.draw(player2);
		win.draw(ball);
		win.display();
	}

	isGameRunning = false;
	input_and_collision_thread->join();
	input_and_collision_thread.reset();
}

