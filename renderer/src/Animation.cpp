#include "Animation.hpp"

Animation::Animation(/* args */)
{
}

Animation::Animation(const Animation &obj)
{
}

void Animation::operator=(const Animation &obj)
{
}

Animation::~Animation()
{
}

glm::vec2 Animation::getLastPos(void)
{
	return (modeldata[curIdx].lastPos);
}

void Animation::restartTimer(void)
{
	modeldata[curIdx].lifeClock.restart();
}

glm::mat4 Animation::pulse(glm::mat4 model, float range, float frequency)
{
	model = glm::scale(model, glm::vec3(sin(frequency * modeldata[curIdx].lifeClock.getElapsedTime().asSeconds()) * (range / 1000) + 1));
	return (model);
}

glm::mat4 Animation::disintergrate(glm::mat4 model)
{ //in progress
	return (model);
}

glm::mat4 Animation::spin(glm::mat4 model, float speed, glm::vec3 axis)
{
	model = glm::rotate(model, modeldata[curIdx].lifeClock.getElapsedTime().asSeconds() * speed, axis);
	return (model);
}

glm::mat4 Animation::waddle(glm::mat4 model)
{
	float deltax = modeldata[curIdx].deltas.x;
	float deltay = modeldata[curIdx].deltas.y;
	if (abs(deltax) < 0.001 && abs(deltay) < 0.001)
		return (model);
	model = glm::rotate(model, (float)(sin(20 * modeldata[curIdx].lifeClock.getElapsedTime().asSeconds()) * 0.1), glm::vec3(0.0f, 0.0f, 1.0f));
	return (model);
}

glm::mat4 Animation::orientation(glm::mat4 model, glm::vec2 currentPos)
{
	float deltax = modeldata[curIdx].lastPos.x - currentPos.x;
	float deltay = modeldata[curIdx].lastPos.y - currentPos.y;
	float orientation;
	if (abs(deltax) < 0.001)
	{
		if (abs(deltay) < 0.001)
		{
			return (glm::rotate(model, modeldata[curIdx].lastOrientation, glm::vec3(0.0f, 1.0f, 0.0f)));
		}
		if (deltay < 0)
		{
			orientation = glm::radians(0.0f);
		}
		else
		{
			orientation = glm::radians(180.0f);
		}
	}
	else
	{
		float gradient = deltay / deltax;
		if (deltay >= 0 && deltax >= 0)
		{
			orientation = (float)(-atan(gradient) - glm::radians(90.0f));
		}
		else if (deltay >= 0 && deltax <= 0)
		{
			orientation = (float)(-atan(gradient) - glm::radians(90.0f) - glm::radians(180.0f));
		}
		else if (deltay <= 0 && deltax <= 0)
		{
			orientation = (float)(-atan(gradient) - glm::radians(90.0f) - glm::radians(180.0f));
		}
		else if (deltay <= 0 && deltax >= 0)
		{
			orientation = (float)(-atan(gradient) - glm::radians(90.0f));
		}
	}

	// testing interpolated orientation
	while (orientation < glm::radians(-180.0f) || orientation > glm::radians(180.0f))
	{
		if (orientation < glm::radians(-180.0f))
			orientation += glm::radians(360.0f);
		if (orientation > glm::radians(180.0f))
			orientation -= glm::radians(360.0f);
	}
	while (modeldata[curIdx].lastOrientation < glm::radians(-180.0f) || modeldata[curIdx].lastOrientation > glm::radians(180.0f))
	{
		if (modeldata[curIdx].lastOrientation < glm::radians(-180.0f))
			modeldata[curIdx].lastOrientation += glm::radians(360.0f);
		if (modeldata[curIdx].lastOrientation > glm::radians(180.0f))
			modeldata[curIdx].lastOrientation -= glm::radians(360.0f);
	}
	if (abs(modeldata[curIdx].lastOrientation - orientation) > 0.2)
	{
		if ((modeldata[curIdx].lastOrientation - orientation > 0 && modeldata[curIdx].lastOrientation - orientation < glm::radians(180.0f)) || modeldata[curIdx].lastOrientation - orientation < glm::radians(-180.0f))
		{
			orientation = modeldata[curIdx].lastOrientation - 0.2;
		}
		else
		{
			orientation = modeldata[curIdx].lastOrientation + 0.2;
		}
	}

	model = glm::rotate(model, orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	modeldata[curIdx].lastPos = glm::vec2(currentPos);
	modeldata[curIdx].lastOrientation = orientation;

	return (model);
}

glm::mat4 Animation::leftFoot(glm::mat4 model)
{
	float deltax = modeldata[curIdx].deltas.x;
	float deltay = modeldata[curIdx].deltas.y;
	if (abs(deltax) < 0.001 && abs(deltay) < 0.001)
		return (model);
	model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
	model = glm::rotate(model, (float)glm::radians(sin(20 * modeldata[curIdx].lifeClock.getElapsedTime().asSeconds()) * 30), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
	return (model);
}

glm::mat4 Animation::rightFoot(glm::mat4 model)
{
	float deltax = modeldata[curIdx].deltas.x;
	float deltay = modeldata[curIdx].deltas.y;
	if (abs(deltax) < 0.001 && abs(deltay) < 0.001)
		return (model);
	model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
	model = glm::rotate(model, (float)glm::radians(-1 * sin(20 * modeldata[curIdx].lifeClock.getElapsedTime().asSeconds()) * 30), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
	return (model);
}

glm::mat4 Animation::floating(glm::mat4 model)
{
	model = glm::translate(model, glm::vec3(0.0f, (sin(2 * modeldata[curIdx].lifeClock.getElapsedTime().asSeconds()) + 1.0f) / 4 + 0.5f, 0.0f));
	return (model);
}

void Animation::primeData(Model_vals_st mdata)
{
	int i;
	for (i = 0; i < modeldata.size(); i++)
	{
		if (modeldata[i].id == mdata.id)
		{
			curIdx = i;
			return;
		}
	}

	modeldata.push_back(mdata);
	curIdx = i;
}

void Animation::setDeltas(glm::vec2 pos)
{
	float deltax = modeldata[curIdx].lastPos.x - pos.x;
	float deltay = modeldata[curIdx].lastPos.y - pos.y;
	modeldata[curIdx].deltas = glm::vec2(deltax, deltay);
}
