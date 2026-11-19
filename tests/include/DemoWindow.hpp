#ifndef DEMO_WINDOW_HPP
#define DEMO_WINDOW_HPP

#include "Test.hpp"

namespace Test
{
    class DemoWindow : public Test
    {
      public:
        ~DemoWindow() override = default;

        void onImGuiRender() override;
    };
} // namespace Test

#endif
