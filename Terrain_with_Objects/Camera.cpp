#include "Camera.h"
#include<Windows.h>
#include <GLFW/glfw3.h>
#include<GL/GLU.h>
#include<iostream>
#include<cmath>

double Camera::degToRad(double angle)
{
	double pi = 3.14159265359;
	return (angle*pi) / 180.0;
}

Camera::Camera()
{
	_pos = glm::vec3(0.f, 0.f, 0.f);
	_dir = glm::vec3(0.f, 0.f, -1.f);
	_left = glm::vec3(-1.f, 0.f, 0.f);
	_up = glm::vec3(0.f, 1.f, 0.f);
	_veloc = glm::vec3(0.f, 0.f, 0.f);
	_scale = 0.25f;
	_yaw = 0.f;
}

Camera::Camera(glm::vec3 pos) : _pos(pos)
{
	_dir = glm::vec3(0, 0, -1);
	_up = glm::vec3(0, 1, 0);
	_left = glm::vec3(-1.f, 0.f, 0.f);
	_veloc = glm::vec3(0.f, 0.f, 0.f);
	_scale = 0.25f;
	_yaw = 0.f;
}

void Camera::activate()
{
	glm::vec3 look = _pos + _dir;
	gluLookAt(_pos.x, _pos.y, _pos.z, look.x, look.y, look.z, _up.x, _up.y, _up.z);

}

void Camera::updateYaw(double dYaw)
{
	_yaw += dYaw;
}

void Camera::update(double dYaw)
{
	updateYaw(dYaw);

	_dir.x = sin(degToRad(_yaw));
	_dir.z = -cos(degToRad(_yaw));
	_dir=glm::normalize(_dir);
	
	_left = glm::cross(_up, _dir);
	_left = glm::normalize(_left);
}

void Camera::forth()
{
	_veloc = _scale*_dir;
	_pos += _veloc;
}

void Camera::retreat()
{
	_veloc = (-_scale)*_dir;
	_pos += _veloc;
}

void Camera::left()
{
	_veloc = _scale*_left;
	_pos += _veloc;
}

void Camera::right()
{
	_veloc = (-_scale)*_left;
	_pos += _veloc;
}
