#include "Camera.hpp"

void Camera::updateCameraVectors(void) {
  glm::vec3 front;
  front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
  front.y = sin(glm::radians(_pitch));
  front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
  _front = glm::normalize(front);
  _right = glm::normalize(glm::cross(_front, _worldUp));
  _up = glm::normalize(glm::cross(_right, front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch):
  _position(position),
  _up(up),
  _worldUp(up),
  _yaw(yaw),
  _pitch(pitch),
  _zoom(45)
{
  updateCameraVectors();
}

Camera::~Camera() {

}

glm::mat4 Camera::getViewMatrix(void) {
  return (glm::lookAt(_position, _position + _front, _up));
}

void Camera::setPosition(glm::vec3 position) {
  _position = position;
}

void Camera::setPitch(float pitch) {
  _pitch = pitch;
  updateCameraVectors();
}

void Camera::setYaw(float yaw) {
  _yaw = yaw;
  updateCameraVectors();  
}

void Camera::setZoom(float zoom) {
  _zoom = zoom;
}

glm::vec3 Camera::getPosition(void) {
  return(_position);
}

float Camera::getPitch(void) {
  return (_pitch);
}

float Camera::getYaw(void) {
  return (_yaw);
}

float Camera::getZoom(void) {
  return (_zoom);
}