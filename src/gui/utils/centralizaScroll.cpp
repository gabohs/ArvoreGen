#include "centralizaScroll.h"

#include "imgui.h"

namespace utils
{
    void centralizaScrollEmX()
    {   
        ImGui::SetScrollHereX(0.5f);
    }

    void centralizaScrollEmXY()
    {
        ImGui::SetScrollHereX(0.5f);
        ImGui::SetScrollHereY(0.5f);
    }
}