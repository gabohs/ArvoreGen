#include "Node.h"

#include "../theme/colors.h"

NodeArvore::NodeArvore(Pessoa *pessoa)
    : m_Pessoa(pessoa), cor(ImGui::ColorConvertFloat4ToU32(Colors::Aqua))
{   
}
