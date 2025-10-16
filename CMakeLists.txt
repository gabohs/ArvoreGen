cmake_minimum_required(VERSION 3.10)
project(ArvoreGen LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add GLFW subdirectory
add_subdirectory(vendor/glfw)

# Set ImGui directory
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)


# List ImGui source files
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Add ImGui as a static library
add_library(imgui STATIC ${IMGUI_SOURCES})

# Include directories for ImGui
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link ImGui dependencies
target_link_libraries(imgui PUBLIC
    glfw
    OpenGL::GL
)

# Create the executable
add_executable(ArvoreGen
    src/core/Window/Window.cpp
    src/core/App.cpp
    src/core/Run.cpp
    src/core/main.cpp

    src/gui/theme/StyleManager.cpp
    src/gui/GuiLayer.cpp
    src/gui/janelas/JanelaControles.cpp
    src/gui/janelas/JanelaVisualiza.cpp
    
    src/backend/Pessoa.cpp
    src/backend/ArvoreGenealogica.cpp
)

# Link the executable with ImGui and dependencies
target_link_libraries(ArvoreGen PRIVATE imgui)