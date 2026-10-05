#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

class Camera
{
  public:
    enum Direction : std::int8_t
    {
        forward,
        backward,
        rightward,
        leftward
    };

    Camera() = default;
    ~Camera() = default;

    [[nodiscard]] float getZoom() const;
    [[nodiscard]] glm::mat4 getViewMatrix() const;

    void handleKeyboard(Direction direction, float delta_time);
    void handleScrollCallback(float x_offset, float y_offset);
    void handleMouseCallback(float x_pos, float y_pos);

    bool first_mouse {true};

  private:
    void processMouseMovement(float x_offset, float y_offset);
    void processScrollMovement(float y_offset);
    void updateCameraVectors();

    float move_speed {5.0};
    float look_speed {0.1};

    glm::vec3 position {0.0, 0.0, 3.0};
    glm::vec3 up {0.0, 1.0, 0.0};
    glm::vec3 front {0.0, 0.0, -1.0};
    glm::vec3 right {1.0, 0.0, 0.0};

    float yaw {-90.0};
    float pitch {0.0};
    float zoom {45.0};

    glm::vec3 world_up {0.0, 1.0, 0.0};

    float last_x {};
    float last_y {};
};

#endif
