#include <math.h>
#include "vec3.h"

vec3::vec3() {
	x = 0;
	y = 0;
	z = 0;
}

vec3::vec3(float x, float y, float z) : x(x), y(y), z(z){}

bool vec3::operator==(vec3 rhs) {
	return(x == rhs.x && y == rhs.y && z == rhs.z);
}

vec3 vec3::operator+(vec3 rhs) {
	return vec3(x + rhs.x,
		y + rhs.y,
		z + rhs.z);
}

vec3 vec3::operator-(vec3 rhs) {
	return vec3(x - rhs.x,
		y - rhs.y,
		z - rhs.z);
}

vec3 vec3::operator*(vec3 rhs) {
	return vec3(x * rhs.x,
		y * rhs.y,
		z * rhs.z);
}

vec3 vec3::operator/(vec3 rhs) {
	return vec3(x / rhs.x,
		y / rhs.y,
		z / rhs.z);
}

vec3 vec3::operator+(float scalar) {
	return vec3(x + scalar,
		y + scalar,
		z + scalar);
}

vec3 vec3::operator-(float scalar) {
	return vec3(x - scalar,
		y - scalar,
		z - scalar);
}

vec3 vec3::operator*(float scalar) {
	return vec3(x * scalar,
		y * scalar,
		z * scalar);
}

vec3 vec3::operator/(float scalar) {
	return vec3(x / scalar,
		y / scalar,
		z / scalar);
}

vec3 vec3::cross(vec3 rhs) {
	return vec3(y * rhs.z - z * rhs.y,
		z * rhs.x - x * rhs.z,
		x * rhs.y - y * rhs.x);
}

vec3 vec3::normalise() {
	float length = vec3(x, y, z).length();
	return vec3((x/length), (y/length), (z/length));
}

vec3 vec3::normaliseCos() {
	vec3 unit = vec3(x, y, z).normalise();
	return vec3((float) cos(x), (float) cos(y), (float) cos(z));
}

float vec3::dot(vec3 rhs) {
	return (x * rhs.x +
		y * rhs.y +
		z * rhs.z);
}

float vec3::length() {
	return float(sqrt(x*x + y*y + z*z));
}