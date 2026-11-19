#include "ClearColour.hpp"
#include "Renderer.hpp"

#include <array>
#include <glad/glad.h>
#include <imgui.h>

namespace Test
{
    ClearColour::ClearColour()
        : clear_colour {Renderer::default_colour[0], Renderer::default_colour[1],
                        Renderer::default_colour[2], Renderer::default_colour[3]}
    {
    }

    void ClearColour::onRender()
    {
        glClearColor(clear_colour[0], clear_colour[1], clear_colour[2], clear_colour[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void ClearColour::onImGuiRender()
    {
        ImGui::ColorEdit4("Clear Colour", clear_colour.data());
    }
} // namespace Test
