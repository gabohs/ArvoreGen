#include "mouse.h"

namespace utils
{
    bool mouseDentroDeRect(ImVec2 VIRect, ImVec2 VFRect)
    {   
        ImVec2 mousePos = ImGui::GetMousePos();
         
        return (mousePos.x > VIRect.x) && (mousePos.x < VFRect.x) &&
               (mousePos.y > VIRect.y) && (mousePos.y < VFRect.y);
    }
}   