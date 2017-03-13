#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include "PhysicsSphere.h"

PhysicsSphere::PhysicsSphere(){
	Init();
}


void PhysicsSphere::Init(){
	oldTime = NULL;
	m_Position = glm::vec3(0.0, 0.0, 0.0);
	m_Velocity = glm::vec3(0.0, 0.0, 0.0);
	m_gravity = glm::vec3(0.0, gravity, 0.0);
	m_resistance = glm::vec3(resistance, 0.0, 0.0);
	m_Force = glm::vec3(5.0, 100.0, 0.0);
	m_Displacement = glm::vec3(0.0, 0.0, 0.0);
}

void PhysicsSphere::Update() {
	float timeDif;
	if (oldTime == NULL) {
		oldTime = clock();
	}
	newTime = clock();

	timeDif = (newTime - oldTime)/CLOCKS_PER_SEC;

	if (m_Force.x > 0.0) {
		m_Force -= m_resistance;
		if (m_Force.x < 0.0)
			m_Force.x = 0.0;
	}
	else if (m_Force.x < 0.0) {
		m_Force += m_resistance;
		if (m_Force.x > 0.0)
			m_Force.x = 0.0;
	}

	if (m_Force.y != gravity) {
		m_Force += m_gravity;
		if (m_Force.y < gravity)
			m_Force.y = gravity;
	}

	m_Displacement = (m_Velocity*timeDif) + (0.5f * (m_Force *(timeDif*timeDif)));

	m_Position += m_Displacement;

	m_Velocity = m_Velocity + (m_Force * timeDif);

	if (m_Position.y <= -20.0) {
		if (m_Velocity.y > 1.0 || m_Velocity.y < -1.0) {
			m_Velocity.y = (-m_Velocity.y)*0.9;
			m_Velocity.x *= 0.9;
		}else {
			m_Velocity.y = 0.0;
			m_Force.y = 0.0;
			m_Position.y = -20.0;
		}
	}
	
	if (m_Position.x <= -20.0 || m_Position.x >= 20.0) {
		m_Velocity.x = (-m_Velocity.x)*0.9;
		m_Velocity.y *= 0.9;
	}

	oldTime = newTime;
}


glm::vec3 PhysicsSphere::getPosition() {
	return m_Position;
}

glm::vec3 PhysicsSphere::getDisplacement() {
	return m_Displacement;
}

glm::vec3 PhysicsSphere::getVelocity() {
	return m_Velocity;
}