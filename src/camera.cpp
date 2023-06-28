#include "camera.h"

#include "input.h"
#include "maths.h"

Camera::Camera(const Vector3f& position, const Vector3f& rotation, float FOV, float nearClip, float farClip, float width, float height) : position(position), rotation(rotation), FOV(FOV), nearClip(nearClip), farClip(farClip) {
    projection = Matrix4f::perspective(FOV, width / height, nearClip, farClip);
}

void Camera::Update() {
    newMouseX = Input::GetMouseX();
    newMouseY = Input::GetMouseY();

    float x = std::sin(toRadians(rotation.y)) * moveSpeed;
    float z = std::cos(toRadians(rotation.y)) * moveSpeed;

    if (Input::IsKeyPressed(GLFW_KEY_A))
        Vector3f::add(position, Vector3f(-z, 0, x));
    if (Input::IsKeyPressed(GLFW_KEY_D))
        Vector3f::add(position, Vector3f(z, 0, -x));
    if (Input::IsKeyPressed(GLFW_KEY_W))
        Vector3f::add(position, Vector3f(-x, 0, -z));
    if (Input::IsKeyPressed(GLFW_KEY_S))
        Vector3f::add(position, Vector3f(x, 0, z));
    if (Input::IsKeyPressed(GLFW_KEY_SPACE))
        Vector3f::add(position, Vector3f(0, moveSpeed, 0));
    if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
        Vector3f::add(position, Vector3f(0, -moveSpeed, 0));

    float dx = static_cast<float>(newMouseX - oldMouseX);
    float dy = static_cast<float>(newMouseY - oldMouseY);

    Vector3f::add(rotation, Vector3f(-dy * mouseSens, -dx * mouseSens, 0));

    // Limit x rotation to a certain range
    if (rotation.x > 90) {
        rotation.x = 90;
    } else if (rotation.x < -90) {
        rotation.x = -90;
    }

    oldMouseX = newMouseX;
    oldMouseY = newMouseY;
}

void Camera::OnResize(float width, float height) {
    projection = Matrix4f::perspective(FOV, width / height, nearClip, farClip);
}

Vector3f Camera::getPosition() {
    return position;
}

Vector3f Camera::getRotation() {
    return rotation;
}

Matrix4f Camera::getProjection() {
    return projection;
}
