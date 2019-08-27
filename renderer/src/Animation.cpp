#include "Animation.hpp"

Animation::Animation(/* args */) {
  _lastPos = glm::vec2(0,0);
  _lastOrientation = glm::radians(90.0f);
}

Animation::Animation(const Animation &obj) {
}

void Animation::operator = (const Animation &obj) {
}

Animation::~Animation(){

}

glm::vec2 Animation::getLastPos(void){
  return (_lastPos);
}

void Animation::restartTimer(void){
  _clock.restart();
}

glm::mat4 Animation::pulse(glm::mat4 model, float range, float frequency){
  model = glm::scale(model, glm::vec3( sin( frequency* _clock.getElapsedTime().asSeconds() ) * (range/1000)  + 1));
  return (model);
}

glm::mat4 Animation::disintergrate(glm::mat4 model){ //in progress
  return (model);
}

glm::mat4 Animation::spin(glm::mat4 model, float speed, glm::vec3 axis) {
  model = glm::rotate(model, _clock.getElapsedTime().asSeconds() * speed, axis);
  return (model);
}

glm::mat4 Animation::waddle(glm::mat4 model) {
  model = glm::rotate(model, (float)(sin(20 * _clock.getElapsedTime().asSeconds()) * 0.1), glm::vec3(0.0f, 0.0f, 1.0f));
  return (model);
}

glm::mat4 Animation::orientation(glm::mat4 model, glm::vec2 currentPos) {
  float deltax = _lastPos.x - currentPos.x;
  float deltay = _lastPos.y -  currentPos.y;
  float orientation;
  if (abs(deltax) < 0.001) {
    if (abs(deltay) < 0.001) {
      return (glm::rotate(model, _lastOrientation, glm::vec3(0.0f, 1.0f, 0.0f)));
    }
    // _lastPos = glm::vec2(currentPos);
    if (deltay < 0){
      // _lastOrientation = glm::radians(0.0f);
      orientation = glm::radians(0.0f);
    } else {
      // _lastOrientation = glm::radians(180.0f);
      orientation = glm::radians(180.0f);
    }
    // return (glm::rotate(model, _lastOrientation, glm::vec3(0.0f, 1.0f, 0.0f)));
  } else {
    float gradient = deltay / deltax;
    if (deltay >= 0 && deltax >= 0) {
      orientation = (float) (-atan(gradient) - glm::radians(90.0f));
    } else if (deltay >= 0 && deltax <= 0) {
      orientation = (float) (-atan(gradient) - glm::radians(90.0f) - glm::radians(180.0f));
    } else if (deltay <= 0 && deltax <= 0) {
      orientation = (float) (-atan(gradient) - glm::radians(90.0f) - glm::radians(180.0f));
    } else if (deltay <= 0 && deltax >= 0) {
      orientation = (float) (-atan(gradient) - glm::radians(90.0f));
    }
  }

    // testing interpolated orientation
    while (orientation < glm::radians(-180.0f) || orientation > glm::radians(180.0f)) {
      if (orientation < glm::radians(-180.0f)) orientation += glm::radians(360.0f);
      if (orientation > glm::radians(180.0f)) orientation -= glm::radians(360.0f);
    }
    while (_lastOrientation < glm::radians(-180.0f) || _lastOrientation > glm::radians(180.0f)) {
      if (_lastOrientation < glm::radians(-180.0f)) _lastOrientation += glm::radians(360.0f);
      if (_lastOrientation > glm::radians(180.0f)) _lastOrientation -= glm::radians(360.0f);
    }
    if (abs(_lastOrientation - orientation) > 0.2) {
      if ((_lastOrientation - orientation > 0 && _lastOrientation - orientation < glm::radians(180.0f)) || _lastOrientation - orientation < glm::radians(-180.0f)) {
        orientation = _lastOrientation - 0.2; 
      } else {
        orientation = _lastOrientation + 0.2; 
      }
    }

  model = glm::rotate(model, orientation, glm::vec3(0.0f, 1.0f, 0.0f));
  _lastPos = glm::vec2(currentPos);
  _lastOrientation = orientation;

  return (model);
}

glm::mat4 Animation::floating(glm::mat4 model) {
  model = glm::translate(model, glm::vec3(0.0f, (sin(2*_clock.getElapsedTime().asSeconds())+1.0f) / 4 + 0.5f, 0.0f));
  return (model);
}