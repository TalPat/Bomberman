#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

struct Particle
{

	double m_x;
	double m_y;
	double m_z;
	double speed;
	double direction;

public:
	Particle();
	virtual ~Particle();
	void update();
	double pos_y(double x);
};

#endif