#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include "vec3.h"

class PhysicsSphere {
public:
	PhysicsSphere();
	void Update();
	glm::vec3 getPosition();
	glm::vec3 getDisplacement();
	glm::vec3 getVelocity();

protected:
	const float gravity = -9.81;
	const float resistance = 0.1;
	glm::vec3 m_Position, m_Displacement, m_Velocity, m_Force, m_gravity, m_resistance;
	float oldTime, newTime;
	void Init();

};