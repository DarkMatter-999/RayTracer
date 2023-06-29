#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "camera.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "input.h"
#include "mesh.h"
#include "shader.h"

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "RayTracer", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(1);  // or handle the error in a nicer way

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    Shader shader = Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

    ImVec4 clear_color = ImVec4(0.07f, 0.14f, 0.17f, 1.00f);

    // Sample vertices
    std::vector<float> vertices = {
        // Position (x, y, z)
        -1.0f, -1.0f, 0.0f,  // Vertex 1
        -1.0f, 1.0f, 0.0f,   // Vertex 2
        1.0f, 1.0f, 0.0f,    // Vertex 3
        1.0f, -1.0f, 0.0f    // Vertex 4
    };

    // Sample indices
    std::vector<unsigned int> indices = {
        0, 1, 2,  // Triangle indices
        0, 2, 3};

    // Sample colors
    std::vector<float> colors = {
        // Color (R, G, B)
        1.0f, 0.0f, 0.0f,  // Vertex 1 color (red)
        0.0f, 1.0f, 0.0f,  // Vertex 2 color (green)
        0.0f, 0.0f, 1.0f,  // Vertex 3 color (blue)
        1.0f, 1.0f, 1.0f   // Vertex 4 color (white)
    };

    // Create a Mesh object
    Mesh mesh(vertices, indices, colors);

    double prevFrameTime = glfwGetTime();
    int width, height;
    bool vsync = true;
    float FOV = 70.0f;

    glfwGetWindowSize(window, &width, &height);

    Input input = Input(window);
    Camera camera = Camera(Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 0.0), FOV, 0.01f, 1000.0f, width, height);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        input.Update();
        camera.Update();

        double currFrameTime = glfwGetTime();
        double frameTime = (currFrameTime - prevFrameTime);

        glfwGetWindowSize(window, &width, &height);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // render your GUI
        ImGui::Begin("Triangle Position/Color");

        if (ImGui::Checkbox("Vsync", &vsync)) {
            glfwSwapInterval(vsync ? 1 : 0);
        }

        ImGui::Text("%.0f FPS | %.2f ms", (1.0f / frameTime), (frameTime * 1000.0f));

        static float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        //  color picker
        ImGui::ColorEdit3("color", color);
        //  multiply triangle's color with this color
        shader.setUniform("color", color[0], color[1], color[2]);
        ImGui::End();

        shader.setUniform("iResolution", (float)width, (float)height);

        shader.setUniform("position", camera.getPosition());
        shader.setUniform("dimension", Vector2f(width, height));
        shader.setUniform("rotation", camera.getRotation());
        shader.setUniform("delta", camera.getDelta());
        shader.setUniform("projection", camera.getProjection());

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.render(shader);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        prevFrameTime = currFrameTime;
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}