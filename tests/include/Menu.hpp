#ifndef MENU_HPP
#define MENU_HPP

#include "Test.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Test
{
    class Menu : public Test
    {
      public:
        Menu();
        Menu(Test*& test);
        ~Menu() override = default;

        void onUpdate(float delta_time) override;
        void onRender() override;
        void onImGuiRender() override;

      private:
        std::unique_ptr<Test> current_test;
        std::vector<std::pair<std::string, std::function<std::unique_ptr<Test>()>>> tests;

        void registerTests();
        void addTestButtons();

        template <typename T>
        void registerTest(const std::string& name)
        {
            std::cout << "Registering test: " << name << "\n";
            tests.push_back(std::make_pair(name, []() { return std::make_unique<T>(); }));
        }
    };
} // namespace Test

#endif
