#include "input.h"

double Input::mouseX = 0.0;
double Input::mouseY = 0.0;
double Input::scrollX = 0.0;
double Input::scrollY = 0.0;

Input::Input(GLFWwindow* window)
    : window_(window) {
}

// Update input state
void Input::Update() {
    // Poll for events
    glfwPollEvents();

    ImVec2 mousePos = ImGui::GetMousePos();
    mouseX = mousePos.x;
    mouseY = mousePos.y;
}

// Check if a key is currently pressed
bool Input::IsKeyPressed(ImGuiKey key) {
    if (ImGui::IsKeyPressed(key))
        return true;
    return false;
}

// Check if a mouse button is currently pressed
bool Input::IsMouseButtonPressed(ImGuiMouseButton button) {
    if (ImGui::IsMouseClicked(button))
        return true;

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
