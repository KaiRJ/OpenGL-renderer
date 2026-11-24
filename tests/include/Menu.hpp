#ifndef MENU_HPP
#define MENU_HPP

#include "Test.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
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

        void setTest(const std::string& test_id);

      private:
        std::unique_ptr<Test> current_test;

        struct RegisteredTest
        {
            std::string id;
            std::string name;
            std::function<std::unique_ptr<Test>()> create;
        };
        std::vector<RegisteredTest> tests;

        void registerTests();
        void addTestButtons();
        void listTests() const;

        template <typename T>
        void registerTest(const std::string& test_id, const std::string& test_name)
        {
            tests.push_back({test_id, test_name, []() { return std::make_unique<T>(); }});
        }
    };
} // namespace Test

#endif
