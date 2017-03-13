#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(glm::vec3 position, int numParticles) {
	first = true;
	m_Position = position;
	this->numParticles = numParticles;
	Init();
}

ParticleEffect::ParticleEffect(){}

void ParticleEffect::Init() {
	Particle::Particle_Type particleType;
	for (int i = 0; i < numParticles; i++) {
		/*int random = rand() % 10 + 1;
		if (random == 1)
		particleType = Particle::Particle_Type::SECONDARY_EMITTER;
		else
		particleType = Particle::Particle_Type::PARTICLE;
		particles.push_back(Particle(particleType, glm::vec3(5.0, 5.0, 0.0)));*/

		glm::vec3 velocity;

		particleType = Particle::Particle_Type::PARTICLE;
		glm::vec3 unitVec = RandUnitVec();
		velocity = glm::vec3(unitVec.x*RandRange(-5.0f, 5.0f),
			unitVec.y*RandRange(-5.0f, 5.0f),
			/*unitVec.z*RandRange(-5.0f, 5.0f)*/ 0.0f);
		Particle p = Particle (particleType, velocity, m_Position);
		//p.Load();
		particles.push_back(p);
	}
}

float ParticleEffect::RandRange(float fMin, float fMax)
{
	if (fMin > fMax) std::swap(fMin, fMax);
	return (Random() * (fMax - fMin)) + fMin;
}

glm::vec3 ParticleEffect::RandUnitVec()
{
	float x = (Random() * 2.0f) - 1.0f;
	float y = (Random() * 2.0f) - 1.0f;
	float z = (Random() * 2.0f) - 1.0f;

	return glm::normalize(glm::vec3(x, y, z));
}

float ParticleEffect::Random()
{
	return rand() / (float)RAND_MAX;
}

void ParticleEffect::Update() {
	
	/*float timeDif;
	if (oldTime == NULL) {
		oldTime = clock();
	}
	newTime = clock();

	timeDif = (newTime - oldTime) / CLOCKS_PER_SEC;*/


	for each(Particle p in particles) {
		p.Update();
		/*if (p.m_Force.x > 0.0) {
			p.m_Force -= p.m_resistance;
			if (p.m_Force.x < 0.0)
				p.m_Force.x = 0.0;
		}
		else if (p.m_Force.x < 0.0) {
			p.m_Force += p.m_resistance;
			if (p.m_Force.x > 0.0)
				p.m_Force.x = 0.0;
		}

		if (p.m_Force.y != p.gravity) {
			p.m_Force += p.m_gravity;
			if (p.m_Force.y < p.gravity)
				p.m_Force.y = p.gravity;
		}

		p.m_Displacement = (p.m_Velocity*timeDif) + (0.5f * (p.m_Force *(timeDif*timeDif)));

		p.setPosition(p.m_Position + p.m_Displacement);

		p.m_Velocity = p.m_Velocity + (p.m_Force * timeDif);*/

	}
	//oldTime = newTime;
	
	/*float timeDif;
	if (oldTime == NULL)
		oldTime = clock();
	newTime = clock();
	timeDif = (newTime - oldTime) / CLOCKS_PER_SEC;

	for each (Particle particle in particles) {
		particle.m_Displacement = (particle.m_Velocity*timeDif) + (0.5f * (1 * (timeDif*timeDif)));
		particle.m_Position += particle.m_Displacement;
	}

	oldTime = newTime;*/
}


glm::vec3 ParticleEffect::getPosition() {
	return m_Position;
}


void ParticleEffect::Draw() {
	for each (Particle particle in particles) {
		//particle.Draw();
	}
}