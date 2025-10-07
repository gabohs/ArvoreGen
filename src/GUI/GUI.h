#pragma once

#include <imgui.h>
#include "Theme/colors.h"

class GUI
{
private:
    bool shouldRender_ = true;

private: 
    void renderComponentsPanel();
    void renderSimulationPanel();

public:
    GUI();
    bool shouldRender();

    void render();
};