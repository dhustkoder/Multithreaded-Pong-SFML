
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

	auto mainWin = mainWinUnique.get();
	
	mainWin->clear(sf::Color::Black);
	ParticleSystem particleSys( { GameWindow::Width, GameWindow::Height } );
	//particleSys.fuel(1000);
	particleSys.setDissolutionRate(15);
	particleSys.setPosition(0,0);
	particleSys.setGravity(-5.f, 0);
	unsigned i = 0, j = 0;
	while(mainWin->isOpen())
	{
		particleSys.setPosition(++i, j);	
		mainWin->clear(sf::Color::Black);
		mainWin->updateWindowState();
		mainWin->drawAndDisplay(particleSys);
		particleSys.update(20.75f / 1000);
		if( i > GameWindow::Width) {
			i = 0;
			++j;
		}
		if(j > GameWindow::Height)
			i = j = 0;
		if(particleSys.getNumberOfParticles() < 10) {
			particleSys.setDissolve();
			particleSys.fuel(25);
		}
	
	}
}

