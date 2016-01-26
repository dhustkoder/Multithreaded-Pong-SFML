#include "pch.h"
#include "SpriteEffect.h"
#include "Shape.h"

unsigned GameWindow::s_width = 0, GameWindow::s_height = 0;
const unsigned &GameWindow::Width = GameWindow::s_width;
const unsigned &GameWindow::Height = GameWindow::s_height;
int GameWindow::s_instances = 0;
std::vector<const Shape*> GameWindow::s_shapeVector;
std::vector<SpriteEffect*> GameWindow::s_spriteEffectVector;

std::unique_ptr<GameWindow> GameWindow::makeUniqueWindow(const sf::VideoMode&& mode, const char *windowName) noexcept
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





GameWindow::GameWindow(const sf::VideoMode &&mode, const char *windowName) noexcept :
	m_renderWindow(mode, windowName)
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

void GameWindow::updateWindowEvents() noexcept
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


void GameWindow::pushShape(const Shape& shape) {
	s_shapeVector.push_back(&shape);
}

void GameWindow::pushSpriteEffect(SpriteEffect& spriteEffect) {
	s_spriteEffectVector.push_back(&spriteEffect);
}

void GameWindow::popShape(const Shape& shape) 
{
	auto itr = std::find(s_shapeVector.begin(),
		s_shapeVector.end(), (&shape));

	if (itr != s_shapeVector.end())
		s_shapeVector.erase(itr);
}

void GameWindow::popSpriteEffect(const SpriteEffect& spriteEffect) 
{
	auto itr = std::find(s_spriteEffectVector.begin(), 
		s_spriteEffectVector.end(), (&spriteEffect));
	
	if (itr != s_spriteEffectVector.end())
		s_spriteEffectVector.erase(itr);
}


void GameWindow::drawAndDisplay()
{
	for (auto& drawablePtr : s_shapeVector) {
		m_renderWindow.draw(*drawablePtr);
	}
	
	for (auto itr = s_spriteEffectVector.begin(); itr != s_spriteEffectVector.end(); ++itr)
	{
		if ((*itr)->isActive()) {
			m_renderWindow.draw(*(*itr));
			(*itr)->update();
		}
		else {
			itr = s_spriteEffectVector.erase(itr);
			if (itr == s_spriteEffectVector.end())
				break;
		}
	}

	m_renderWindow.display();
}
