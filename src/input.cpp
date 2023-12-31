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

    if (!mouseLock) {
        ImVec2 mousePos = ImGui::GetMousePos();
        mouseX = mousePos.x;
        mouseY = mousePos.y;
    }
}

// Check if a key is currently pressed
bool Input::IsKeyPressed(ImGuiKey key) {
    if (ImGui::GetIO().KeysDown[key])
        return true;
    return false;
}

// Check if a mouse button is currently pressed
bool Input::IsMouseButtonPressed(ImGuiMouseButton button) {
    if (ImGui::GetIO().MouseDown[button])
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

void Input::mouseState(bool state) {
    // Disable the cursor
    ImGui::SetMouseCursor(state ? ImGuiMouseCursor_Arrow : ImGuiMouseCursor_None);

    // glfwSetInputMode(window_, GLFW_CURSOR, state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Input::setMouseLock(bool state) {
    mouseLock = state;
}