#include "Particle.hpp"

#ifndef SWARM_HPP_
#define SWARM_HPP_

class Swarm
{
	Particle *m_particles;

public:
	const static int NPARTICLES = 200;
	Swarm();
	virtual ~Swarm();
	Particle *getParticles()
	{
		return m_particles;
	}
	void update();
};

#endif