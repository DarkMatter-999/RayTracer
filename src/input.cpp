#include "input.h"

bool Input::keys[GLFW_KEY_LAST] = {false};
bool Input::buttons[GLFW_MOUSE_BUTTON_LAST] = {false};
double Input::mouseX = 0.0;
double Input::mouseY = 0.0;
double Input::scrollX = 0.0;
double Input::scrollY = 0.0;

Input::Input(GLFWwindow* window)
    : window_(window) {
    // Set callback functions
    glfwSetKeyCallback(window_, KeyCallback);
    glfwSetMouseButtonCallback(window_, MouseButtonCallback);
    glfwSetCursorPosCallback(window_, CursorPositionCallback);
    glfwSetScrollCallback(window_, ScrollCallback);
}

// Key input callback function
void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key >= 0 && key < GLFW_KEY_LAST) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

// Mouse button callback function
void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
        if (action == GLFW_PRESS)
            buttons[button] = true;
        else if (action == GLFW_RELEASE)
            buttons[button] = false;
    }
}

// Mouse cursor position callback function
void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

// Scroll wheel callback function
void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    scrollX = xoffset;
    scrollY = yoffset;
}

// Update input state
void Input::Update() {
    // Poll for events
    glfwPollEvents();
}

// Check if a key is currently pressed
bool Input::IsKeyPressed(int key) {
    if (key >= 0 && key < GLFW_KEY_LAST)
        return keys[key];

    return false;
}

// Check if a mouse button is currently pressed
bool Input::IsMouseButtonPressed(int button) {
    if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
        return buttons[button];

    return false;
}

// Get the current mouse cursor position
double Input::GetMouseX() {
    return mouseX;
}

double Input::GetMouseY() {
    return mouseY;
}

// Get the scroll wheel offsets
double Input::GetScrollX() {
    return scrollX;
}

double Input::GetScrollY() {
    return scrollY;
}
