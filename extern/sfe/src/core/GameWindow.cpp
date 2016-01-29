#include "Exceptions.h"
#include "Utility.h"
#include "Entity.h"
#include "GameWindow.h"
SFE_NAMESPACE


unsigned GameWindow::s_width = 0, GameWindow::s_height = 0;
const unsigned &GameWindow::Width = GameWindow::s_width;
const unsigned &GameWindow::Height = GameWindow::s_height;
int GameWindow::s_instances = 0;
std::vector<const sf::Drawable*> GameWindow::s_drawVector;

std::unique_ptr<GameWindow> GameWindow::makeUniqueWindow(const sf::VideoMode&& mode, const char *windowName)
{
	if (s_instances == 0)
	{

		try {
			return std::unique_ptr<GameWindow>(new GameWindow(std::move(mode), windowName));
		}
		catch (std::bad_alloc& err) {
			printException(err, "GameWindow::makeUniqueWindow", true);
		}
	}

	return nullptr;
}


std::unique_ptr<GameWindow> GameWindow::makeUniqueWindow(const char *windowName)
{
	if (s_instances == 0)
	{

		try {
			return std::unique_ptr<GameWindow>(new GameWindow({ defaultWidth,defaultHeight }, windowName));
		}
		catch (std::bad_alloc& err) {
			printException(err, "GameWindow::makeUniqueWindow", true);
		}
	}

	return nullptr;
}



GameWindow::GameWindow(const sf::VideoMode &&mode, const char *windowName) 
	: m_renderWindow(mode, windowName)
{
	m_renderWindow.setFramerateLimit(60);
	m_renderWindow.setVerticalSyncEnabled(true);
	m_event.type = sf::Event::GainedFocus;
	s_width = mode.width;
	s_height = mode.height;
	++s_instances;
}



GameWindow::~GameWindow() {
	--s_instances;
	s_width = s_height = 0;
}




void GameWindow::updateWindowEvents() 
{
	m_renderWindow.pollEvent(m_event);
	if (m_event.type == sf::Event::Closed)
		m_renderWindow.close();
}


void GameWindow::setSize(const unsigned width, const unsigned height)
{
	m_renderWindow.setSize({width, height});
	s_width = width;
	s_height = height;
}



void GameWindow::pushDrawable(const sf::Drawable& drawable) {
	s_drawVector.push_back(&drawable);
}




void GameWindow::popDrawable(const sf::Drawable& drawable) noexcept
{
	auto itr = std::find(s_drawVector.begin(),
		s_drawVector.end(), (&drawable));

	if (itr != s_drawVector.end())
		s_drawVector.erase(itr);
}




void GameWindow::drawAndDisplay()
{
	for (auto& drawablePtr : s_drawVector)
		m_renderWindow.draw(*drawablePtr);
	
	m_renderWindow.display();
}













NAMESPACE_END
