#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

#include "utility.h"
#include "player.h"
#include "cpu.h"
#include "ball.h"



constexpr unsigned winWidth = 800;
constexpr unsigned winHeight = 420;


Player player1(winWidth, winHeight, 30.0F, 80.0F);
Ball ball(winWidth, winHeight);
Cpu player2(winWidth, winHeight, 30.0F, 80.0F, ball);
std::atomic<bool> isGameRunning(false);
std::atomic<bool> doInputAndCollisionProcess(false);


void process_input_and_collision()
{
	//load sound to memory
	auto soundBuff = std::make_unique<sf::SoundBuffer>();
	soundBuff->loadFromFile("../Resources/ballsound");
	auto sound = std::make_unique<sf::Sound>(*soundBuff); // sound for ball impact

	while (isGameRunning)
	{
		if(doInputAndCollisionProcess)
		{
			
			player1.update();
			player2.update();
			ball.update();
	
	
			if (isColliding(player1, ball))
			{
				sound->play();
				ball.treatCollisionWith(player1);
			}
			else if (isColliding(player2, ball))
			{
				sound->play();
				ball.treatCollisionWith(player2);
			}
			
			doInputAndCollisionProcess = false; // wait until next round...
		}
		
		else
			std::this_thread::yield();
	}


}


int main()
{

#ifdef __linux__
	XInitThreads(); // prevent X11 threads error
#endif


	sf::RenderWindow mainWindow(sf::VideoMode(winWidth, winHeight, 64), "Multithread-Pong-SFML");
	sf::Event winEvent;
	winEvent.type = sf::Event::GainedFocus;
	
	mainWindow.setFramerateLimit(60);
	player1.setPosition(5u, cexpr_div(winHeight,2u) );
	player2.setPosition(cexpr_sub(winWidth, 5u), cexpr_div(winHeight,2u));
	
	// start game and extra thread
	isGameRunning = true;
	auto input_and_collision_thread = std::make_unique<std::thread>(process_input_and_collision);

	while (mainWindow.isOpen())
	{
		doInputAndCollisionProcess = true;
		
		mainWindow.clear(sf::Color::Black);
		mainWindow.pollEvent(winEvent);
	
		if (winEvent.type == sf::Event::Closed)
		{
			mainWindow.close();
			break;
		}
	
	
		while(doInputAndCollisionProcess)
			std::this_thread::yield();
	
	
		mainWindow.draw(player1);
		mainWindow.draw(player2);
		mainWindow.draw(ball);
		mainWindow.display();
	}
	
	isGameRunning = false;
	input_and_collision_thread->join();
	input_and_collision_thread.reset();
}

