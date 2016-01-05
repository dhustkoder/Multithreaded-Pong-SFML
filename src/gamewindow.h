#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

class GameWindow final
{

public:
	static std::unique_ptr<GameWindow> makeUniqueWindow(sf::VideoMode mode, const char* windowName) noexcept;

	~GameWindow();
	void updateWindowState() noexcept;
	void setSize(const unsigned width, const unsigned height) noexcept;
	bool isOpen() const noexcept;
	template<typename ...Ts>
	void drawAndDisplay(Ts&& ...args) noexcept;
private:
	GameWindow(sf::VideoMode, const char*) noexcept;
	sf::RenderWindow m_renderWindow;
	sf::Event m_event;
	static int sm_instances;

	// deleted functions
	GameWindow(const GameWindow&) = delete;
	GameWindow(GameWindow&&)      = delete;
};

inline GameWindow::~GameWindow() {
	--sm_instances;
}


inline bool GameWindow::isOpen() const noexcept {
	return m_renderWindow.isOpen();
}


template<typename ...Ts>
inline void GameWindow::drawAndDisplay(Ts &&...args) noexcept
{
	(void)std::initializer_list<int>
	{
		(m_renderWindow.draw(std::forward<Ts>(args)), 0)...
	};

	m_renderWindow.display();
}
#endif // GAMEWINDOW_H
