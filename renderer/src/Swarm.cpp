#include "Swarm.hpp"

Swarm::Swarm()
{
	m_particles = new Particle[NPARTICLES];
}

Swarm::~Swarm()
{
	delete[] m_particles;
}

void Swarm::update()
{
	for (int i = 0; i < NPARTICLES; i = i + 2)
	{
		m_particles[i].update();
		m_particles[i + 1].update();
	}
}
