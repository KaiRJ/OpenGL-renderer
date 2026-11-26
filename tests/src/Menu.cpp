#include "Menu.hpp"
#include "ClearColour.hpp"
#include "DemoWindow.hpp"
#include "Triangles.hpp"
#include "imgui.h"
#include <iostream>

namespace Test
{
    Menu::Menu() : current_test {nullptr} { registerTests(); }

    Menu::Menu(Test*& test) : current_test {test} { registerTests(); }

    void Menu::onUpdate(float delta_time)
    {
        if (current_test)
        {
            current_test->onUpdate(delta_time);
        }
    }

    void Menu::onRender()
    {
        if (current_test)
        {
            current_test->onRender();
        }
    }

    void Menu::onImGuiRender()
    {
        if (current_test)
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

    void Menu::setTest(const std::string& test_id)
    {
        for (const auto& test : tests)
        {
            if (test_id == test.id)
            {
                current_test = test.create();
                return;
            }
        }

        std::cout << "Invalid test ID!" << "\n";
        listTests();
    }

    void Menu::registerTests()
    {
        registerTest<DemoWindow>("imgui", "ImGui Demo Window");
        registerTest<ClearColour>("clear", "Clear Colour");
        registerTest<Triangles>("triangles", "Triangles");
    }

    void Menu::addTestButtons()
    {
        for (const auto& test : tests)
        {
            if (ImGui::Button(test.name.c_str()))
            {
                current_test = test.create();
            }
        }
    }

    void Menu::listTests() const
    {
        std::cout << "Available tests:\n";
        for (const auto& test : tests)
        {
            std::cout << "  " << test.id << "\t" << test.name << '\n';
        }
    }
} // namespace Test
