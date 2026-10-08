#ifndef TEST_HPP
#define TEST_HPP

namespace Test
{
    class Test
    {
      public:
        Test() = default;
        virtual ~Test() = default;

        virtual void onUpdate(float delta_time) = 0;
        virtual void onRender() = 0;
        virtual void onImGuiRender() = 0;
    };
} // namespace Test

#endif
