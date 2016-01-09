#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "ball.h"
#include "gamewindow.h"
#include "particlesystem/particle.h"
#include "utility.h"

static ParticleSystem *g_particleSys;


Ball::Ball() noexcept : 
	Shape({cexpr_div(ballRadius, 2.f), cexpr_div(ballRadius, 2.f)},
	      std::make_unique<sf::CircleShape>(ballRadius))
{
	static ParticleSystem particleSys({GameWindow::Width, GameWindow::Height});
	g_particleSys = &particleSys;
	m_shape->setFillColor(sf::Color::Red);
	this->setPosition(Position::Middle);
	m_velocity->y = m_velocity->x = ballVelocity;
	g_particleSys->setDissolutionRate(5);
	g_particleSys->setShape(ParticleShape::CIRCLE);


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

	const auto ballPos = m_shape->getPosition();	

	g_particleSys->setDissolve();
	g_particleSys->setPosition(ballPos.x, ballPos.y);
	g_particleSys->setGravity(-m_velocity->x, -m_velocity->y);
	g_particleSys->fuel(25);
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	g_particleSys->draw(target, states);	
	target.draw(*m_shape, states);
	g_particleSys->update(20.f / 1000);
}
