#include <string>
#include <SFML/Graphics/Text.hpp>
#include "gamescore.h"
#include "gamewindow.h"
#include "ball.h"



namespace GameScore {

unsigned playerScore = 0, adverScore = 0;
sf::Font gameFont;
sf::Text player1Text("0",gameFont), adverText("0", gameFont);

void update(const Ball &ball) noexcept
{

	if(ball.getRight() >= GameWindow::Width) {
		++playerScore;
		player1Text.setString(std::to_string(playerScore));
	}

	else if(ball.getLeft() <= 0) {
		++adverScore;
		adverText.setString(std::to_string(adverScore));
	}

}

void display() noexcept {
	std::printf("P1: %u\n", playerScore);
	std::printf("Adver: %u\n", adverScore);
}




}
