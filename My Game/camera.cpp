#include "camera.h"

float Camera::camera_speed = 2.5f;
float Camera::sensitivity = 0.05f;
float Camera::fov = glm::radians(45.0f);
float Camera::pitch = 0.0f;
float Camera::yaw = -90.0f;
float Camera::last_x = 0.0f;
float Camera::last_y = 0.0f;

glm::vec3 Camera::pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Camera::front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

void Camera::process_keyboard_input(CAMERA_DIRECTIONS direction, float delta_time) {
	float velocity = camera_speed * delta_time;

	switch (direction) {
	case FORWARD:
		pos += velocity * front;
		break;
	case BACKWARD:
		pos -= velocity * front;
		break;
	case LEFT:
		pos -= velocity * glm::normalize(glm::cross(front, up));
		break;
	case RIGHT:
		pos += velocity * glm::normalize(glm::cross(front, up));
		break;
	case UP:
		pos += velocity * up;
		break;
	case DOWN:
		pos -= velocity * up;
	}
}

void Camera::process_mouse_input(double xpos, double ypos) {
	float x_offset = sensitivity * ((float)xpos - last_x);
	float y_offset = sensitivity * (last_y - (float)ypos);

	last_x = xpos;
	last_y = ypos;

	yaw += x_offset;

	if (pitch > -89.0f && pitch < 89.0f) {
		pitch += y_offset;
	}

	glm::vec3 vec;
	vec.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	vec.y = sin(glm::radians(pitch));
	vec.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	front = glm::normalize(vec);
}