#include "DemoWindow.hpp"
#include "imgui.h"

namespace Test
{
    void DemoWindow::onImGuiRender() { ImGui::ShowDemoWindow(); }
} // namespace Test
