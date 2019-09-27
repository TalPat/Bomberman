#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

struct Model_vals_st {
	int id;
	sf::Clock lifeClock;
	glm::vec2 lastPos;
	float lastOrientation;
	glm::vec2 deltas;
};

class Animation
{
private:
	std::vector<Model_vals_st> modeldata;
	float x, y;
	int curIdx;

public:
	Animation(/* args */);
	~Animation();

	Animation(const Animation &obj);
	void operator=(const Animation &obj);

	void primeData(Model_vals_st);
	void setDeltas(glm::vec2 pos);

	glm::vec2 getLastPos(void);

	void restartTimer(void);
	glm::mat4 pulse(glm::mat4 model, float range, float frequency);
	glm::mat4 disintergrate(glm::mat4 model);
	glm::mat4 spin(glm::mat4 model, float speed, glm::vec3 axis);
	glm::mat4 floating(glm::mat4 model);
	glm::mat4 waddle(glm::mat4 model);

	glm::mat4 leftFoot(glm::mat4 model);
	glm::mat4 rightFoot(glm::mat4 model);

	glm::mat4 orientation(glm::mat4 model, glm::vec2 currentPos);
};

#endif
