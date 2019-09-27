#include "Particle.hpp"
#include <stdlib.h>
#include <iostream>
#include <math.h>

Particle::Particle()
{
	m_x = ((double)rand() / RAND_MAX) * (0.9765 - -0.9765) + -0.9765;
	m_y = ((double)rand() / RAND_MAX) * (pos_y(m_x) / 2 - 0) + 0;
	m_x /= 4;
	m_z = (((double)rand() / RAND_MAX) * (0.9765 - -0.9765) + -0.9765) / 4;

	speed = (0.1 * rand()) / RAND_MAX;
	direction = 2 * M_PI * rand() / RAND_MAX;
}

Particle::~Particle()
{
}

void Particle::update()
{
	double xspeed = speed * cos(direction);

	m_y += xspeed;
	if (m_y < 0 || m_y > pos_y(m_x) / 2)
		m_y = 0;
}

double Particle::pos_y(double x)
{
	int seed = -5;
	double y = 0.0;
	for (int n = 0; n < 10; n++)
	{
		y += pow(0.3, n) * cos(pow(seed, n) * M_PI * x);
	}
	y += 1.233;
	return y;
}