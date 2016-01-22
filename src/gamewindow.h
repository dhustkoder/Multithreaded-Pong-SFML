#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

class GameWindow final
{
	static constexpr unsigned defaultWidth = 800;
	static constexpr unsigned defaultHeight = 420;
public:
	static const unsigned &Width, &Height;

public:
	static std::unique_ptr<GameWindow> 
		makeUniqueWindow(const sf::VideoMode &&mode = {defaultWidth, defaultHeight, 32},
				 const char* windowName = "Game-Window") noexcept;
	static std::unique_ptr<GameWindow> 
		makeUniqueWindow(const char* windowName) noexcept;

	~GameWindow();
	void clear(const sf::Color color) noexcept;
	void updateWindowState() noexcept;
	const sf::Event& getEvent() const noexcept;
	void setSize(const unsigned Width, const unsigned Height) noexcept;
	sf::Vector2u getSize() const noexcept;
	bool isOpen() const noexcept;
	
	template<typename ...Ts>
	void drawAndDisplay(Ts&& ...args) noexcept;

private:
	GameWindow(const sf::VideoMode&&, const char*) noexcept;


	sf::RenderWindow m_renderWindow;
	sf::Event m_event;
	static int s_instances;
	static unsigned s_width, s_height;

	// deleted functions
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

};


inline GameWindow::~GameWindow() {
	--s_instances;
	s_width = s_height = 0;
}

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


// sends all args to sf::RenderWindow draw fuction. 
// (the arguments need to be implicit conversible to sf::Drawable)
template<typename ...Ts>
void GameWindow::drawAndDisplay(Ts &&...args) noexcept
{
	(void)std::initializer_list<int>
	{
		(m_renderWindow.draw(std::forward<Ts>(args)), 0)...
	};

	m_renderWindow.display();
}



#endif // GAMEWINDOW_H
