#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>
#include <vector>

#include "maths.h"

class Camera {
   private:
    Vector3f position, rotation;
    Matrix4f projection;
    float moveSpeed = 0.25f, mouseSens = 0.25f;
    double oldMouseX = 0, oldMouseY = 0, newMouseX, newMouseY;
    float distance = 2.0f, angle = 0, verticalAngle = 0, horizontalAngle = 0;
    float FOV, nearClip, farClip;

   public:
    Camera(const Vector3f& position, const Vector3f& rotation, float FOV, float nearClip, float farClip, float width, float height);

    void Update();
    void OnResize(float width, float height);

    Vector3f getPosition();
    Vector3f getRotation();
    Matrix4f getProjection();
};

#endif  // CAMERA_H