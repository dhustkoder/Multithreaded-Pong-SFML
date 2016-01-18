#include "pch.h"

unsigned GameWindow::s_width = 0, GameWindow::s_height = 0;
const unsigned &GameWindow::Width = GameWindow::s_width, &GameWindow::Height = GameWindow::s_height;

int GameWindow::s_instances = 0;

std::unique_ptr<GameWindow> GameWindow::makeUniqueWindow(sf::VideoMode&& mode, const char *windowName) noexcept
{
	if(s_instances > 0)
		return nullptr;

	return std::unique_ptr<GameWindow>(new GameWindow(std::move(mode), windowName));

}


std::unique_ptr<GameWindow> GameWindow::makeUniqueWindow(const char *windowName) noexcept
{
	if(s_instances > 0)
		return nullptr;

	return std::unique_ptr<GameWindow>(new GameWindow({defaultWidth,defaultHeight}, windowName));

}



GameWindow::GameWindow(sf::VideoMode &&mode, const char *windowName) noexcept :
	m_renderWindow(mode, windowName)
{
	m_renderWindow.setFramerateLimit(60);
	m_renderWindow.setVerticalSyncEnabled(true);
	m_event.type = sf::Event::GainedFocus;
	s_width = mode.width;
	s_height = mode.height;
	++s_instances;
}

void GameWindow::updateWindowState() noexcept
{
	m_renderWindow.pollEvent(m_event);

	if (m_event.type == sf::Event::Closed)
		m_renderWindow.close();
}


void GameWindow::setSize(const unsigned width, const unsigned height) noexcept
{
	m_renderWindow.setSize({width, height});
	s_width = width;
	s_height = height;
}
