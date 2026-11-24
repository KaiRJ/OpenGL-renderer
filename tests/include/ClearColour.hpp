#ifndef CLEAR_COLOUR_HPP
#define CLEAR_COLOUR_HPP

#include "Test.hpp"
#include <array>

namespace Test
{
    class ClearColour : public Test
    {
      public:
        ClearColour();
        ~ClearColour() override = default;

        void onRender() override;
        void onImGuiRender() override;

      private:
        std::array<float, 4> clear_colour {};
    };
} // namespace Test

#endif
