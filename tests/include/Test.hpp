#ifndef TEST_HPP
#define TEST_HPP

namespace Test
{
    class Test
    {
      public:
        Test() = default;
        virtual ~Test() = default;

        virtual void onUpdate(float delta_time) {};
        virtual void onRender() {};
        virtual void onImGuiRender() {};
    };
} // namespace Test

#endif
