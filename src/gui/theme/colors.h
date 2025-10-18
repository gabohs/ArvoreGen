#pragma once

#pragma once

#include <imgui.h>

struct Colors
{   
    static ImVec4 Green;
    static ImVec4 LightBlue;
    static ImVec4 DarkBlue;
    static ImVec4 Aqua;
    static ImVec4 Orange;
    static ImVec4 LightOrange;
    static ImVec4 Red;
    static ImVec4 BrightRed;
    static ImVec4 Gray;
    static ImVec4 DarkGray;
    static ImVec4 Purple;
    static ImVec4 Yellow;
    static ImVec4 DarkYellow;
};

ImVec4 Colors::Green       = ImVec4(184.f / 255.f, 187.f / 255.f, 38.f / 255.f, 1.f); 
ImVec4 Colors::LightBlue   = ImVec4(131.f / 255.f, 165.f / 255.f, 152.f / 255.f, 1.f); 
ImVec4 Colors::DarkBlue    = ImVec4(69.f / 255.f, 133.f / 255.f, 136.f / 255.f, 1.f); 
ImVec4 Colors::Aqua        = ImVec4(142.f / 255.f, 192.f / 255.f, 124.f / 255.f, 0.7f);
ImVec4 Colors::Orange      = ImVec4(254.f / 255.f, 128.f / 255.f, 25.f / 255.f, 1.f); 
ImVec4 Colors::LightOrange = ImVec4(255.f / 255.f, 163.f / 255.f, 79.f / 255.f, 1.f);
ImVec4 Colors::Red         = ImVec4(251.f / 255.f, 73.f / 255.f, 52.f / 255.f, 1.f); 
ImVec4 Colors::BrightRed   = ImVec4(204.f / 255.f, 36.f / 255.f, 29.f / 255.f, 1.f);  
ImVec4 Colors::Gray        = ImVec4(146.f / 255.f, 131.f / 255.f, 116.f / 255.f, 1.f); 
ImVec4 Colors::DarkGray    = ImVec4(50.f / 255.f, 48.f / 255.f, 47.f / 255.f, 1.f);   
ImVec4 Colors::Purple      = ImVec4(211.f / 255.f, 134.f / 255.f, 155.f / 255.f, 1.f);
ImVec4 Colors::Yellow      = ImVec4(250.f / 255.f, 189.f / 255.f, 47.f  / 255.f, 1.f);
ImVec4 Colors::DarkYellow  = ImVec4(204.f / 255.f, 153.f / 255.f, 30.f / 255.f, 1.f);