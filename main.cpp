#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "gl3w.h"
#include "glfw3.h"

#include <iostream>

int main()
{
    // Initialize GLFW and create a window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "FPS Calculator", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Initialize GL3W
    gl3wInit();

    // Initialize ImGui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    // Main loop
    float frameTimeSum = 0.0f;
    int frameCount = 0;
    float fps = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        // Poll events
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Calculate the frame time and FPS
        float currentFrameTime = (float)glfwGetTime();
        frameTimeSum += currentFrameTime;
        ++frameCount;
        if (frameTimeSum >= 1.0f)
        {
            fps = (float)frameCount / frameTimeSum;
            frameTimeSum = 0.0f;
            frameCount = 0;
        }

        // Display the FPS in the ImGui window
        ImGui::Begin("FPS Calculator");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / fps, fps);
        ImGui::End();

        // Render the ImGui frame
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Clean up
    ImGui_ImplOpenGL3_Shutdown();
}