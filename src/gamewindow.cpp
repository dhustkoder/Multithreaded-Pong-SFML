#include "gamewindow.h"

unsigned GameWindow::sm_width = 0, GameWindow::sm_height = 0;
const unsigned &GameWindow::width = GameWindow::sm_width, &GameWindow::height = GameWindow::sm_height;

int GameWindow::sm_instances = 0;

std::unique_ptr<GameWindow> GameWindow::makeUniqueWindow(sf::VideoMode&& mode, const char *windowName) noexcept
{
	if(sm_instances > 0)
		return nullptr;

	return std::unique_ptr<GameWindow>(new GameWindow(std::move(mode), windowName));

}


std::unique_ptr<GameWindow> GameWindow::makeUniqueWindow(const char *windowName) noexcept
{
	if(sm_instances > 0)
		return nullptr;

	return std::unique_ptr<GameWindow>(new GameWindow({defaultWidth,defaultHeight}, windowName));

}



GameWindow::GameWindow(sf::VideoMode &&mode, const char *windowName) noexcept :
	m_renderWindow(mode, windowName)
{
	m_renderWindow.setFramerateLimit(60);
	m_renderWindow.setVerticalSyncEnabled(true);
	m_event.type = sf::Event::GainedFocus;
	sm_width = mode.width;
	sm_height = mode.height;
	++sm_instances;
}

void GameWindow::updateWindowState() noexcept
{
	m_renderWindow.clear(sf::Color::Black);
	m_renderWindow.pollEvent(m_event);

	if (m_event.type == sf::Event::Closed)
	m_renderWindow.close();
}


void GameWindow::setSize(const unsigned __width, const unsigned __height) noexcept
{
	m_renderWindow.setSize({__width, __height});
	sm_width = __width;
	sm_height = __height;
}
