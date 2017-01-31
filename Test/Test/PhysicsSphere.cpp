#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GLM/glm.hpp>
//#include <GLM/gtx/transform.hpp>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "PhysicsSphere.h"

PhysicsSphere::PhysicsSphere(float xCoord, float yCoord, float zCoord, float radius, int polygons){

	float theta1 = 0.0, theta2 = 0.0, theta3 = 0.0;

	float ex = 0.0f, ey = 0.0f, ez = 0.0f;

	float px = 0.0f, py = 0.0f, pz = 0.0f;

	//std::vector<GLfloat> vertices(polygons * 6 + 6), normals(polygons * 6 + 6), texCoords(polygons * 4 + 4);

	GLfloat v[1];

	GLfloat vertices[10 * 6 + 6], normals[10 * 6 + 6], texCoords[10 * 4 + 4];



	if (radius < 0)

		radius = -radius;



	if (polygons < 0)

		polygons = -polygons;



	for (int i = 0; i < polygons / 2; ++i)

	{

		theta1 = i * (M_PI * 2) / polygons - M_PI_2;

		theta2 = (i + 1) * (M_PI * 2) / polygons - M_PI_2;



		for (int j = 0; j <= polygons; ++j)

		{

			theta3 = j * (M_PI * 2) / polygons;



			ex = cosf(theta2) * cosf(theta3);

			ey = sinf(theta2);

			ez = cosf(theta2) * sinf(theta3);

			px = xCoord + radius * ex;

			py = yCoord + radius * ey;

			pz = zCoord + radius * ez;



			vertices[(6 * j) + (0 % 6)] = px;

			vertices[(6 * j) + (1 % 6)] = py;

			vertices[(6 * j) + (2 % 6)] = pz;



			normals[(6 * j) + (0 % 6)] = ex;

			normals[(6 * j) + (1 % 6)] = ey;

			normals[(6 * j) + (2 % 6)] = ez;



			texCoords[(4 * j) + (0 % 4)] = -(j / (float)polygons);

			texCoords[(4 * j) + (1 % 4)] = 2 * (i + 1) / (float)polygons;





			ex = cosf(theta1) * cosf(theta3);

			ey = sinf(theta1);

			ez = cosf(theta1) * sinf(theta3);

			px = xCoord + radius * ex;

			py = yCoord + radius * ey;

			pz = zCoord + radius * ez;



			vertices[(6 * j) + (3 % 6)] = px;

			vertices[(6 * j) + (4 % 6)] = py;

			vertices[(6 * j) + (5 % 6)] = pz;



			normals[(6 * j) + (3 % 6)] = ex;

			normals[(6 * j) + (4 % 6)] = ey;

			normals[(6 * j) + (5 % 6)] = ez;



			texCoords[(4 * j) + (2 % 4)] = -(j / (float)polygons);

			texCoords[(4 * j) + (3 % 4)] = 2 * i / (float)polygons;

		}

		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glNormalPointer(GL_FLOAT, 0, normals);

		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, (polygons + 1) * 2);
	}
}