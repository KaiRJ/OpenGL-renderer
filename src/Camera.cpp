#include "Camera.hpp"

float Camera::getZoom() const { return zoom; }

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::handleKeyboard(Direction direction, float delta_time)
{
    const float velocity {move_speed * delta_time};
    switch (direction)
    {
    case forward:
        position += front * velocity;
        return;
    case backward:
        position -= front * velocity;
        return;
    case rightward:
        position += right * velocity;
        return;
    case leftward:
        position -= right * velocity;
        return;
    }
}

void Camera::handleScrollCallback(float x_offset, float y_offset)
{
    zoom -= y_offset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::handleMouseCallback(float x_pos, float y_pos)
{
    if (first_mouse)
    {
        last_x = x_pos;
        last_y = y_pos;
        first_mouse = false;
    }

    float x_offset {x_pos - last_x};
    float y_offset {last_y - y_pos}; // reversed since y goes from bottom to top

    last_x = x_pos;
    last_y = y_pos;

    processMouseMovement(x_offset, y_offset);
    updateCameraVectors();
}

void Camera::processMouseMovement(float x_offset, float y_offset)
{
    x_offset *= look_speed;
    y_offset *= look_speed;

    yaw += x_offset;
    pitch += y_offset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void Camera::updateCameraVectors()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}
