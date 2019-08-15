#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
  glm::vec3 _position, _up, _right, _front, _worldUp;
  float _yaw, _pitch, _zoom;
  void updateCameraVectors(void);
public:
  Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
  ~Camera();

  glm::mat4 getViewMatrix(void);

  void setPosition(glm::vec3 position);
  void setPitch(float pitch);
  void setYaw(float yaw);
  void setZoom(float zoom);

  glm::vec3 getPosition(void);
  float getPitch(void);
  float getYaw(void);
  float getZoom(void);
};

#endif