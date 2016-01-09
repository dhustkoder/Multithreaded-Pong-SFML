#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "ball.h"
#include "gamewindow.h"
#include "particlesystem/particle.h"
#include "utility.h"

static ParticleSystem g_particleSys({GameWindow::Width, GameWindow::Height});


Ball::Ball() noexcept : 
	Shape({cexpr_div(ballRadius, 2.f), cexpr_div(ballRadius, 2.f)},
	      std::make_unique<sf::CircleShape>(ballRadius))
{
	m_shape->setFillColor(sf::Color::Red);
	this->setPosition(Position::Middle);
	m_velocity->y = m_velocity->x = ballVelocity;

}

void Ball::treatCollisionWith(const Shape &collidedShape) noexcept
{

	float middle_of_collided_shape = (collidedShape.getBottom() + collidedShape.getTop()) / 2.0F;
	float middle_of_ball = ( getBottom() + getTop() ) / 2.0F;

	(middle_of_ball > middle_of_collided_shape) ? m_velocity->y = ballVelocity : m_velocity->y = -ballVelocity;
	
	m_velocity->x = (m_velocity->x == ballVelocity) ? -ballVelocity : ballVelocity;
	
}


void Ball::update() noexcept
{
	
	if (getTop() <= 0)
		m_velocity->y = ballVelocity;
	else if(getBottom() >= GameWindow::Height)
		m_velocity->y = -ballVelocity;

	if(getLeft() <= 0)
		m_velocity->x = ballVelocity;
	else if(getRight() >= GameWindow::Width)
		m_velocity->x = -ballVelocity;

	m_shape->rotate(m_velocity->y);
	m_shape->move(*m_velocity);

	if(g_particleSys.getNumberOfParticles() < 400)
		g_particleSys.fuel(1000);

	/* Update particle system */
	g_particleSys.update(20.f / 1000);
}

#include <ctime>
static std::clock_t clk = std::clock();
void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	auto ballPos = m_shape->getPosition();
	if((std::clock() - clk) > CLOCKS_PER_SEC) {
		g_particleSys.setPosition(ballPos.x, ballPos.y);
		clk = std::clock();
	}

	g_particleSys.setGravity(ballPos.x / 2.f, ballPos.y / 2.f);
	target.draw(*m_shape, states);
	g_particleSys.draw(target, states);
	
}
