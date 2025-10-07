#include "GUI.h"

#include <vector>
#include <iostream>

#include <imgui_internal.h>

GUI::GUI()
{
}

void createDockspace()
{
    // Funcao composta majoritariamente por boilerplate. Serve para deixar os dois paineis "controles" e "visualizacao" lado a lado

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDecoration;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(3);

    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    static bool dockspace_initialized = false;
    if (!dockspace_initialized)
    {
        dockspace_initialized = true;
        ImGui::DockBuilderRemoveNode(dockspace_id); // Clear existing layout
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->WorkSize); 

        ImGuiID dock_main_id = dockspace_id;
        ImGuiID left;
        ImGuiID right;
        ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.25f, &left, &right);

        ImGui::DockBuilderDockWindow("Controles", left);
        ImGui::DockBuilderDockWindow("Visualizacao", right);

        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

    ImGui::End();
}

bool GUI::shouldRender()
{
    return shouldRender_;
}

void GUI::render()
{   
    createDockspace();
    renderComponentsPanel();
    renderSimulationPanel();
}

