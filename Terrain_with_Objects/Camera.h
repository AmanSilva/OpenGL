#pragma once
#include<glm/glm.hpp>

class Camera
{
private:
	glm::vec3 _pos;
	glm::vec3 _dir;
	glm::vec3 _left;
	glm::vec3 _up;
	glm::vec3 _veloc;
	float _scale;
	float _yaw;

	double degToRad(double angle);
	void updateYaw(double dYaw);

public:
	Camera();
	Camera(glm::vec3 pos);

	void activate();

	void update(double dYaw);

	void forth();
	void retreat();
	void left();
	void right();

};

