#ifndef PARTICLE_H
#define PARTICLE_H


#include <sstream>
#include <list>
#include <memory>
#include <random>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>







/* Enum for particle distribution type */
namespace ParticleShape { enum { CIRCLE, SQUARE }; }

/* Particle Structure */
struct Particle final : public sf::Drawable
{
	/* Data Members */
	sf::Vertex drawVertex; /*< To replace pos */
	sf::Vector2f vel; // Velocity

	/* Member Functions */
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override final { 
		target.draw(&drawVertex, 1, sf::Points, states); 
	}

};



class ParticleSystem final : public sf::Drawable
{
	using UniRealDist = std::uniform_real_distribution<>;
	using UniIntDist = std::uniform_int_distribution<>;
	using ParticlePtr = std::unique_ptr<Particle>;
public:

	/* Constructors/Destructor */

	ParticleSystem(sf::Vector2u canvasSize);
	~ParticleSystem(void);

	/* Getters and Setters */

	int getDissolutionRate(void) const { return m_dissolutionRate; }
	size_t getNumberOfParticles(void) const { return m_particles.size(); }
	float getParticleSpeed(void) const { return m_particleSpeed; }
	const std::string getNumberOfParticlesString(void) const;

	void setCanvasSize(const sf::Vector2u newSize) { m_canvasSize = newSize; }
	void setDissolutionRate(const sf::Uint8 rate) { m_dissolutionRate = rate; }
	void setDissolve(void) { m_dissolve = !m_dissolve; }
	void setDistribution(void) { m_shape = (m_shape + 1) % 2; }
	void setGravity(const float x, const float y) { m_gravity.x = x; m_gravity.y = y; }
	void setGravity(const sf::Vector2f gravity) { m_gravity = gravity; }
	void setParticleSpeed(const float speed) { m_particleSpeed = speed; }
	void setPosition(const float x, const float y) { m_startPos.x = x; m_startPos.y = y; }
	void setPosition(const sf::Vector2f position) { m_startPos = position; }
	void setShape(const sf::Uint8 shape) { m_shape = shape; }
	void setColor(const sf::Color color) { m_setedColor = color; m_useSetedColor = true; }
	void unsetColor() { m_useSetedColor = false; }
	/* Member Functions */

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override final;

	void fuel(const int particles);     /*< Adds new particles */
	void update(const float deltaTime); /*< Updates particles */

private:
  /* Data Members */

	bool m_dissolve;       /*< Dissolution enabled? */
	float m_particleSpeed;  /*< Pixels per second (at most) */

	sf::Color m_transparent;    /*< sf::Color(0, 0, 0, 0) */
	sf::Color m_setedColor;
	bool m_useSetedColor;	
	sf::Uint8   m_dissolutionRate;/*< Rate particles disolve */
	sf::Uint8   m_shape;          /*< Shape of distribution */

	sf::Vector2f    m_gravity;    /*< Influences particle velocities */
	sf::Vector2f    m_startPos;   /*< Particle origin */
	sf::Vector2u    m_canvasSize;/*< Limits of particle travel */

	/* Container */
	std::vector<ParticlePtr> m_particles;

};






#endif // PARTICLE_H