#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>

class PhysicsSphere {
public:
	PhysicsSphere();
	void Load();
	void Draw();
	void Update();
	float getDisplacement();
	void  checkErrorShader(GLuint shader);

	vector<GLfloat> vertexPositions;

	GLuint          program;
	GLuint          vao;
	GLuint          buffer;
	GLint           mv_location;
	GLint           proj_location;
	GLint           color_location;
	glm::mat4		proj_matrix = glm::mat4(1.0f);
	glm::mat4		mv_matrix = glm::mat4(1.0f);

	glm::vec4 fillColor = glm::vec4(1.0, 0.0, 0.0, 1.0);
	glm::vec4 lineColor = glm::vec4(0.0, 0.0, 0.0, 1.0);
	float lineWidth = 2.0f;

protected:
	const float gravity = 9.81;
	float _displacement, _acceleration, _initialVelocity, _finalVelocity;
	float oldTime, newTime;
	string rawData;			// Import obj file from Blender (note: no textures or UVs).
	void LoadObj();
	void Init();

};