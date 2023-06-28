#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input {
   public:
    Input(GLFWwindow* window);

    void Update();

    static bool IsKeyPressed(int key);
    static bool IsMouseButtonPressed(int button);
    static double GetMouseX();
    static double GetMouseY();
    static double GetScrollX();
    static double GetScrollY();

   private:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow* window_;

    static bool keys[GLFW_KEY_LAST];
    static bool buttons[GLFW_MOUSE_BUTTON_LAST];
    static double mouseX;
    static double mouseY;
    static double scrollX;
    static double scrollY;
};

#endif  // INPUT_H