#include "centralizaScroll.h"

#include "imgui.h"

namespace utils
{
    void centralizaScrollEmX()
    {   
        static bool rodou = false;

        if (rodou)
            return;

        ImGui::SetScrollHereX(0.5f);

        rodou = true;
    }

    void centralizaScrollEmXY()
    {
        static bool rodou = false;

        if (rodou)
            return;

        ImGui::SetScrollHereX(0.5f);
        ImGui::SetScrollHereY(0.5f);

        rodou = true;
    }
}