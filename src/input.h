#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "imgui.h"

class Input {
   public:
    Input(GLFWwindow* window);

    void Update();

    static bool IsKeyPressed(ImGuiKey key);
    static bool IsMouseButtonPressed(ImGuiMouseButton button);
    static double GetMouseX();
    static double GetMouseY();
    static double GetScrollX();
    static double GetScrollY();
    void mouseState(bool state);

   private:
    GLFWwindow* window_;

    static double mouseX;
    static double mouseY;
    static double scrollX;
    static double scrollY;
};

#endif  // INPUT_H