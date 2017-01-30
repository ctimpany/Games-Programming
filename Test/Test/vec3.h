#ifndef vec3_H
#define vec3_H
class vec3 {
public:
	vec3();
	vec3(float, float, float);
	bool operator==(vec3 rhs);
	vec3 operator+(vec3 rhs);
	vec3 operator-(vec3 rhs);
	vec3 operator*(vec3 rhs);
	vec3 operator/(vec3 rhs);
	vec3 operator+(float scalar);
	vec3 operator-(float scalar);
	vec3 operator*(float scalar);
	vec3 operator/(float scalar);
	vec3 cross(vec3 rhs);
	vec3 normalise();
	vec3 normaliseCos();
	float dot(vec3 rhs);
	float length();

	float x;
	float y;
	float z;

};
#endif