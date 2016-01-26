#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <memory>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
class SpriteEffect;
class Shape;

class GameWindow final
{
	static constexpr unsigned defaultWidth = 800;
	static constexpr unsigned defaultHeight = 420;
public:
	static const unsigned &Width, &Height;

public:
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
	
	static std::unique_ptr<GameWindow> 
		makeUniqueWindow(const sf::VideoMode &&mode = {defaultWidth, defaultHeight, 32},
				 const char* windowName = "Game-Window") noexcept;
	static std::unique_ptr<GameWindow> 
		makeUniqueWindow(const char* windowName) noexcept;

	
	/////////////////////////////////////////////////////////
	/// \brief pushShape
	/// push and drawable object into the draw vector
	/// the object will be drawn and displayed when
	/// drawAndDisplay is called
	////////////////////////////////////////////////////////
	static void pushShape(const Shape& drawable);
	
	
	/////////////////////////////////////////////////////////
	/// \brief pushSpriteEffect
	/// this will draw  and  update the SpriteEffect
	/// when drawAndDisplay is called, if effect ends
	/// then it is pushed out of SpriteEffect vector
	////////////////////////////////////////////////////////
	static void pushSpriteEffect(SpriteEffect& spriteEffect);
	

	static void popShape(const Shape& drawable);
	static void popSpriteEffect(const SpriteEffect& spriteEffect);
	
	
	/////////////////////////////////////////////////////////
	/// \brief drawAndDisplay
	/// draws into render window all objects pushed
	/// into Shape and SpriteEffect vectors then calls display
	////////////////////////////////////////////////////////
	void drawAndDisplay();




	void setSize(const unsigned Width, const unsigned Height) noexcept;
	void updateWindowEvents() noexcept;
	void clear(const sf::Color color) noexcept;
	void close() noexcept;

	bool isOpen() const noexcept;
	sf::Vector2u getSize() const noexcept;
	const sf::Event& getEvent() const noexcept;
	
	
	

	
	~GameWindow();
private:
	GameWindow(const sf::VideoMode&&, const char*) noexcept;

	sf::RenderWindow m_renderWindow;
	sf::Event m_event;
	
	static std::vector<const Shape*> s_shapeVector;
	static std::vector<SpriteEffect*> s_spriteEffectVector;
	static int s_instances;
	static unsigned s_width, s_height;



};


inline sf::Vector2u GameWindow::getSize() const noexcept {
	return m_renderWindow.getSize();
}

inline bool GameWindow::isOpen() const noexcept {
	return m_renderWindow.isOpen();
}

inline const sf::Event& GameWindow::getEvent() const noexcept {
	return m_event;
}

inline void GameWindow::clear(const sf::Color color) noexcept {
	return m_renderWindow.clear(color);
}

inline void GameWindow::close() noexcept {
	m_renderWindow.close();
}




#endif // GAMEWINDOW_H
