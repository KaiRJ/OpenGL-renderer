#include "Gui.hpp"
#include "Renderer.hpp"
#include "TestClearColour.hpp"
#include "Window.hpp"

#include <cassert>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
    Window window {};
    Gui::initialise(window.getWindow());
    Renderer::initialise();

    Test::TestClearColour test;

    {                           // ensure objects are destroyed before glfwTerminate()
        float delta_time {0.0}; // time between current frame and last frame
        float last_frame {0.0};
        while (!window.shouldClose())
        {
            Renderer::clear();

            float current_frame {static_cast<float>(glfwGetTime())};
            delta_time = current_frame - last_frame;
            last_frame = current_frame;
            test.onUpdate(delta_time);

            test.onRender();

            Gui::newFrame();
            test.onImGuiRender();
            Gui::render();

            window.swapBuffers();
            glfwPollEvents();
        }
    }

    Gui::shutdown();
    glfwTerminate();

    return 0;
}
