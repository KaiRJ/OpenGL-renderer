#ifndef TRIANGLES_HPP
#define TRIANGLES_HPP

#include "Test.hpp"

namespace Test
{
    class Triangles : public Test
    {
      public:
        Triangles() = default;
        ~Triangles() override = default;

        void onRender() override;
    };
} // namespace Test

#endif
