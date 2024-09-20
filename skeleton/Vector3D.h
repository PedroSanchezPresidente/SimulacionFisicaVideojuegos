#pragma once

class Vector3D {
public:
	float x, y, z;

	Vector3D() { x = 0; y = 0; z = 0; };
	Vector3D(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }

	float magnitude();

	Vector3D normalize();

	float dot(Vector3D);
};