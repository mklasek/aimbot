#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

typedef float angle;

class Vector3D
{

public:
	float x;
	float y;
	float z;

	Vector3D();
	Vector3D(float xx, float yy, float zz);

	~Vector3D();

};



float Vec3Dlength(Vector3D A);
angle VectorsAngle3D(Vector3D A, Vector3D B);

Vector3D AddVectors(Vector3D A, Vector3D B);
Vector3D SubVectors(Vector3D A, Vector3D B);
Vector3D Xprod(Vector3D A, Vector3D B);
float Vec3DXscalar(Vector3D A, Vector3D B);


Vector3D Project3DVec(Vector3D vec, const char axis);
Vector3D VecNormalize(Vector3D vec);





