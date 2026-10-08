#ifndef TEST_CLEAR_COLOUR_HPP
#define TEST_CLEAR_COLOUR_HPP

#include "Test.hpp"
#include <array>

namespace Test
{
    class TestClearColour : public Test
    {
      public:
        TestClearColour();
        ~TestClearColour() override = default;

        void onUpdate(float delta_time) override {};
        void onRender() override;
        void onImGuiRender() override;

      private:
        std::array<float, 4> clear_colour {};
    };
} // namespace Test

#endif
