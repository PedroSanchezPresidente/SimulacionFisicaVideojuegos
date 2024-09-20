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

