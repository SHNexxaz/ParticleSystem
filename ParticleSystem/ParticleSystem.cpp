// ParticleSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

int n = 500;
int i = 1000;
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Quads, count * 4),
		m_lifetime(sf::seconds(3)),
		m_emitter(0, 0)
	{
	}

	void setEmitter(sf::Vector2f position)
	{
		m_emitter = position;
	}

	void update(sf::Time elapsed)
	{
		for (std::size_t i = 0; i < m_particles.size(); i += 4)
		{
			// update the particle lifetime

			m_particles[i].velocity.y += m_particles[i].gravity.y * elapsed.asSeconds();
			Particle& p = m_particles[i];
			p.lifetime -= elapsed;

			// if the particle is dead, respawn it
			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);

			// update the position of the corresponding vertex
			m_vertices[i].position += (p.velocity)  * elapsed.asSeconds();
			p.location = m_vertices[i].position;

			m_vertices[i + 1].position = m_vertices[i].position + sf::Vector2f(25, 0);
			m_vertices[i + 2].position = m_vertices[i].position + sf::Vector2f(25, 25);
			m_vertices[i + 3].position = m_vertices[i].position + sf::Vector2f(0, 25);

			//update texture position
			m_vertices[i].texCoords = sf::Vector2f(0, 0);
			m_vertices[i + 1].texCoords = sf::Vector2f(200, 0);
			m_vertices[i + 2].texCoords = sf::Vector2f(200, 112.5);
			m_vertices[i + 3].texCoords = sf::Vector2f(0, 112.5);

			// update the alpha (transparency) of the particle according to its lifetime
			float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
			m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		}
	}

	void loadTexture()
	{
		m_texture.loadFromFile("smoke.png");
	}

	void resizeParticles()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			n += 100;
			m_vertices.resize(n);
			m_particles.resize(n);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (n > 0)
			{
				n -= 100;
				m_vertices.resize(n);
				m_particles.resize(n);

			}
		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// our particles don't use a texture
		states.texture = &m_texture;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::Vector2f location; //keep track of location 
		sf::Vector2f gravity; //add gravity property
		sf::Vector2f accelaration;
	};

	void resetParticle(std::size_t index)
	{

		// give a random velocity and lifetime to the particle
		float angle = ((std::rand()) % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		//while (index % 4 == 0)
		//{
		m_particles[index].gravity = sf::Vector2f(0.0f, 150.0f);
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
		//m_vertices[index + 1].position.x = (10 + m_emitter.x);
		//m_vertices[index + 1].position.y = m_emitter.y;
		//m_vertices[index + 2].position.x = (10 + m_emitter.x);
		//m_vertices[index + 2].position.y = (10 + m_emitter.y);
		//m_vertices[index + 3].position.x = m_emitter.x;
		//m_vertices[index + 3].position.y = m_emitter.y + 10;
		//}


	}

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
	sf::Event event;
	sf::Texture m_texture; //add texture

};

//another particle system
class ParticleSystemB : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystemB(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Triangles, count * 3),
		m_lifetime(sf::seconds(3)),
		m_emitter(0, 0)
	{
	}

	void setEmitter(sf::Vector2f position)
	{
		m_emitter = position;
	}

	void update(sf::Time elapsed)
	{
		for (std::size_t i = 0; i < m_particles.size(); i += 3)
		{
			// update the particle lifetime

			m_particles[i].velocity.y += m_particles[i].gravity.y * elapsed.asSeconds();
			Particle& p = m_particles[i];
			p.lifetime -= elapsed;

			// if the particle is dead, respawn it
			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);

			// update the position of the corresponding vertex
			m_vertices[i].position += (p.velocity)  * elapsed.asSeconds();
			p.location = m_vertices[i].position + sf::Vector2f(10, 10);
			m_vertices[i + 1].position = m_vertices[i].position + sf::Vector2f(50, 10);
			m_vertices[i + 2].position = m_vertices[i].position + sf::Vector2f(50, 50);

			m_vertices[i].color = sf::Color::Red;
			m_vertices[i + 1].color = sf::Color::Blue;
			m_vertices[i + 2].color = sf::Color::Green;


			// update the alpha (transparency) of the particle according to its lifetime
			float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
			m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		}
	}


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// our particles don't use a texture
		states.texture = NULL;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::Vector2f location; //keep track of location 
		sf::Vector2f gravity; //add gravity property
		sf::Vector2f accelaration;
	};

	void resetParticle(std::size_t index)
	{

		// give a random velocity and lifetime to the particle
		float angle = ((std::rand()) % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		m_particles[index].gravity = sf::Vector2f(0.0f, 150.0f);
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;


	}

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;



};

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

	// create the particle system
	ParticleSystem particles(n);
	ParticleSystemB particlesB(i);
	// create a clock to track the elapsed time
	sf::Clock clock;

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		particles.setEmitter(window.mapPixelToCoords(mouse));
		particlesB.setEmitter(window.mapPixelToCoords(mouse));

		// update it
		sf::Time elapsed = clock.restart();
		particles.loadTexture();
		particles.update(elapsed);
		particlesB.update(elapsed);
		//call resize function
		particles.resizeParticles();

		
	

		// draw it
		window.clear();
		//window.draw(particlesB);
		window.draw(particles);
		//click left mouse button to generate another particle system
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			window.draw(particlesB);

		}
		window.display();
	}

	return 0;
}
