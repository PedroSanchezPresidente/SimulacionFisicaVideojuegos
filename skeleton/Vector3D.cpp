#include "Vector3D.h"
#include <math.h>

float Vector3D::magnitude() {
	return sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalize() {
	float mag = magnitude();
	Vector3D v;
	v.x = x / mag;
	v.y = y / mag;
	v.z = z / mag;

	return v;
}

float Vector3D::dot(Vector3D v) {
	return x * v.x + y * v.y + z * v.z;
}

Vector3D operator+(Vector3D v1, Vector3D v2) {
	return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3D operator-(Vector3D v1, Vector3D v2) {
	return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3D operator*(Vector3D v1, float v2) {
	return Vector3D(v1.x * v2, v1.y * v2, v1.z * v2);
}

Vector3D operator*(float v2, Vector3D v1) {
	return Vector3D(v1.x * v2, v1.y * v2, v1.z * v2);
}

Vector3D operator*(Vector3D v1, Vector3D v2) {
	return Vector3D(v1.y * v2.z - v2.y *v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y);
}