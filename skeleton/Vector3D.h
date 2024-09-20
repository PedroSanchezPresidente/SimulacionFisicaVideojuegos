#pragma once

class Vector3D {
public:
	float x, y, z;

	Vector3D() { x = 0; y = 0; z = 0;};
	Vector3D(float nx, float ny, float nz) { x = nx; y = ny; z = nz; };

	float magnitude();

	Vector3D normalize();

	float dot(Vector3D);

	Vector3D operator+(const Vector3D& v2) {
		return Vector3D(x + v2.x, y + v2.y, z + v2.z);
	}

	Vector3D operator-(const Vector3D& v2) {
		return Vector3D(x - v2.x, y - v2.y, z - v2.z);
	}

	Vector3D operator*(const float v2) {
		return Vector3D(x * v2, y * v2, z * v2);
	}

	Vector3D operator*(const Vector3D& v2) {
		return Vector3D(y * v2.z - v2.y * z, z * v2.x - v2.z * x, x * v2.y - v2.x * y);
	}

	Vector3D& operator=(const Vector3D& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
};