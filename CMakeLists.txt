cmake_minimum_required(VERSION 3.10)
project(ArvoreGen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenGL REQUIRED)
add_subdirectory(vendor/glfw)


set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# adiciona imgui como biblioteca estatica
add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(imgui PUBLIC
    glfw
    OpenGL::GL
)

# =--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=

add_executable(ArvoreGen
    src/core/Window/Window.cpp
    src/core/App.cpp
    src/core/Run.cpp
    src/core/main.cpp

    src/backend/Pessoa.cpp
    src/backend/ArvoreGenealogica.cpp

    src/gui/theme/StyleManager.cpp
    src/gui/theme/colors.cpp
    src/gui/GuiLayer.cpp

    src/gui/janelas/JanelaControles.cpp
    src/gui/janelas/JanelaVisualiza.cpp

    src/gui/arvore/Node.cpp

    src/gui/arvore/ArvoreRender.cpp

    src/gui/utils/mouse.cpp
    src/gui/utils/truncaNome.cpp
)

# =--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=

# Linkando 
target_link_libraries(ArvoreGen PRIVATE imgui)