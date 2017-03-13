#ifndef __PARTICLEEFFECT_H__
#define __PARTICLEEFFECT_H__

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
#include "Particle.h"

class ParticleEffect {
public:
	ParticleEffect(glm::vec3 position, int numParticles);
	ParticleEffect();
	void Draw();
	void Update();
	void Init();
	glm::vec3 getPosition();

	vector<Particle> particles;

	float RandRange(float fMin, float fMax);
	glm::vec3 RandUnitVec();
	float Random();

protected:
	bool first;
	//vector<Particle> particles;
	glm::vec3 m_Position;
	float oldTime, newTime;
	int numParticles;

};

#endif