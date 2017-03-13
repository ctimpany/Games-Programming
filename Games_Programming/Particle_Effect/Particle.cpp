#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include "Particle.h"

Particle::Particle(Particle_Type type, glm::vec3 velocity, glm::vec3 position) {
	this->type = type;
	m_Velocity = velocity;
	m_Position = position;
	Init();
}

Particle::Particle() {};

void Particle::Init() {
	switch (type) {
	case PRIMARY_EMITTER: 
		lifeTime = NULL;
		break;
	case SECONDARY_EMITTER:
		lifeTime = 5;
		break;
	case PARTICLE:
		lifeTime = 7;
		break;
	}
	age = 0;
	oldTime = NULL;
	//m_Velocity = glm::vec3(0.0, 0.0, 0.0);
	m_gravity = glm::vec3(0.0, gravity, 0.0);
	m_resistance = glm::vec3(resistance, 0.0, 0.0);
	//m_Force = glm::vec3(5.0, 0.0, 0.0);
	m_Displacement = glm::vec3(0.0, 0.0, 0.0);
	//m_Velocity = glm::vec3(0.0, 20000.0, 0.0)/1000000.0f;
}

bool Particle::isDead() {
	if (lifeTime - age <= 0)
		return true;
	else
		return false;
}

//particle.m_Velocity += ( m_Force * fDeltaTime );
//particle.m_Position += (particle.m_Velocity * fDeltaTime);
void Particle::Update() {
	float timeDif;
	if (oldTime == NULL) {
		oldTime = clock();
	}
	newTime = clock();

	timeDif = (newTime - oldTime) / CLOCKS_PER_SEC;


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

	oldTime = newTime;
}


glm::vec3 Particle::getPosition() {
	return m_Position;
}

glm::vec3 Particle::getDisplacement() {
	return m_Displacement;
}

glm::vec3 Particle::getVelocity() {
	return m_Velocity;
}


void Particle::setPosition(glm::vec3 pos) {
	this->m_Position = pos;
}