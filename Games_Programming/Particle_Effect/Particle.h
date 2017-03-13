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

class Particle {
public:
	enum Particle_Type { PRIMARY_EMITTER, SECONDARY_EMITTER, PARTICLE };

	Particle(Particle_Type type, glm::vec3 velocity, glm::vec3 position);
	Particle();
	void Update();
	glm::vec3 getPosition();
	glm::vec3 getDisplacement();
	glm::vec3 getVelocity();
	void setPosition(glm::vec3 pos);
	bool isDead();

	glm::vec3 m_Position, m_Displacement, m_Velocity, m_uVelocity, m_Force, m_gravity, m_resistance;
	const float gravity = -9.81;
	const float resistance = 0.1;

protected:
	Particle_Type type;
	//const float gravity = -9.81;
	//const float resistance = 0.1;
	//float _displacement, _acceleration, _initialVelocity, _finalVelocity;
	//glm::vec3 m_Position, m_Displacement, m_Velocity, m_uVelocity, m_Force, m_gravity, m_resistance;
	float oldTime, newTime, lifeTime, age;
	string rawData;			// Import obj file from Blender (note: no textures or UVs).
	void Init();

};