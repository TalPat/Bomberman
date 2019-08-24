#include "Animation.hpp"

Animation::Animation(/* args */) {
  _lastPos = glm::vec2(0,0);
  /**/std::cout << "animator constructor" << std::endl;
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

glm::mat4 Animation::disintergrate(glm::mat4 model){

}

glm::mat4 Animation::orientation(glm::mat4 model, glm::vec2 currentPos) {
  float deltax = _lastPos.x - currentPos.x;
  float deltay = _lastPos.y -  currentPos.y;
  if (abs(deltax) < 0.001) {
    if (abs(deltay) < 0.001) {
      return (glm::rotate(model, _lastOrientation, glm::vec3(0.0f, 1.0f, 0.0f)));
    }
    _lastPos = glm::vec2(currentPos);
    if (deltay < 0){
      _lastOrientation = glm::radians(0.0f);
    } else {
      _lastOrientation = glm::radians(180.0f);
    }
    return (glm::rotate(model, _lastOrientation, glm::vec3(0.0f, 1.0f, 0.0f)));
  }
  float gradient = deltay / deltax;
  /**/std::cout << deltay << "/" << deltax << " gradient: " << gradient << std::endl;
  float orientation;
  if (deltay >= 0 && deltax >= 0) {
    std::cout << "a" << std::endl;
    orientation = (float) (-atan(gradient) - glm::radians(90.0f));
  } else if (deltay >= 0 && deltax <= 0) {
    std::cout << "b" << std::endl;
    orientation = (float) (-atan(gradient) - glm::radians(90.0f) - glm::radians(180.0f));
  } else if (deltay <= 0 && deltax <= 0) {
    std::cout << "c" << std::endl;
    orientation = (float) (-atan(gradient) - glm::radians(90.0f) - glm::radians(180.0f));
  } else if (deltay <= 0 && deltax >= 0) {
    std::cout << "d" << std::endl;
    orientation = (float) (-atan(gradient) - glm::radians(90.0f));
  }
  /**/std::cout << " orientation: " << glm::degrees(orientation) << std::endl;
  model = glm::rotate(model, orientation, glm::vec3(0.0f, 1.0f, 0.0f));
  _lastPos = glm::vec2(currentPos);
  _lastOrientation = orientation;

  return (model);
}

glm::mat4 Animation::floating(glm::mat4 model) {
  model = glm::translate(model, glm::vec3(0.0f, (sin(2*_clock.getElapsedTime().asSeconds())+1.0f) / 4 + 0.5f, 0.0f));
  return (model);
}