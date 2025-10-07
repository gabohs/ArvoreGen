#include "style.h"

namespace setStyle
{
    void Dark()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowRounding = 10.f;
        style.FrameRounding  = 4.f;
        style.GrabRounding   = 10.f;
        style.PopupRounding  = 4.f;
        style.ScrollbarSize  = 10.f;
    }
}

