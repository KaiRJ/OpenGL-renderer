#include "Menu.hpp"

#include "ClearColour.hpp"
#include "imgui.h"

namespace Test
{
    Menu::Menu() : current_test {nullptr} { registerTests(); }

    Menu::Menu(Test*& test) : current_test {test} { registerTests(); }

    void Menu::onUpdate(float delta_time)
    {
        if (current_test != nullptr)
        {
            current_test->onUpdate(delta_time);
        }
    }

    void Menu::onRender()
    {
        if (current_test != nullptr)
        {
            current_test->onRender();
        }
    }

    void Menu::onImGuiRender()
    {
        if (current_test != nullptr)
        {
            if (ImGui::Button("<-"))
            {
                current_test.reset();
            }
            else
            {
                current_test->onImGuiRender();
            }
        }
        else
        {
            addTestButtons();
        }
    }

    void Menu::registerTests()
    {
        registerTest<ClearColour>("Clear Colour");
        // registerTest<ClearColour>("Clear Colour");
    }

    void Menu::addTestButtons()
    {
        for (auto& test : tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                current_test = test.second();
            }
        }
    }

} // namespace Test
