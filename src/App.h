#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

#include "GUI/Theme/colors.h"
#include "GUI/Theme/style.h"

#include "GUI/GUI.h"

class App
{
private:
    GLFWwindow* window_; 

    bool initializeGLFW();
    bool initializeImGui();
    void shutdown();
    void setup();

    GUI gui;

public:
    App();
    ~App();

    bool init();
    void run();

};