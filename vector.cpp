#include "vector.h"

Vector3D elementx(1, 0, 0);
Vector3D elementy(0, 1, 0);
Vector3D elementz(0, 0, 1);

//Constructors and destructors

Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}

Vector3D::~Vector3D()
{

}



//vector operations

float Vec3DXscalar(Vector3D A, Vector3D B)
{
	return A.x * B.x + A.y * B.y + A.z * B.z;
}



float Vec3Dlength(Vector3D A)
{
	return sqrtf(A.x*A.x + A.y*A.y + A.z*A.z);
}



angle VectorsAngle3D(Vector3D A, Vector3D B)
{
	angle result;
	//result = (acos(Vec3DXscalar(A, B) / (Vec3Dlength(A)*Vec3Dlength(B))))*(180 / M_PI);
	result = Vec3DXscalar(A, B) / (Vec3Dlength(A)*Vec3Dlength(B));
	if (result >=1)
		return 0.0001f;
	
	result = acos(result)*(180 / M_PI);
	return result;
}




Vector3D AddVectors(Vector3D A, Vector3D B)
{
	Vector3D result;
	result.x = A.x + B.x;
	result.y = A.y + B.y;
	result.z = A.z + B.z;

	return result;
}


Vector3D SubVectors(Vector3D A, Vector3D B)
{
	Vector3D result;
	result.x = A.x - B.x;
	result.y = A.y - B.y;
	result.z = A.z - B.z;

	return result;
}









Vector3D Project3DVec(Vector3D vec, const char axis)
{
	Vector3D result;
	result = vec;
	if (axis == 'x')
	{
		result.x = 0;
	}
	else if (axis == 'y')
	{
		result.y = 0;
	}
	else if (axis == 'z')
	{
		result.z = 0;
	}
	else
		return result;

	return result;
}


Vector3D Xprod(Vector3D A, Vector3D B)
{
	Vector3D result;
	result.x = A.y*B.z - A.z*B.y;
	result.y = A.z*B.x - A.x*B.z;
	result.z = A.x*B.y - A.y*B.x;

	return result;
}

Vector3D VecNormalize(Vector3D vec)
{
	Vector3D result;
	float size = Vec3Dlength(vec);
	result.x = vec.x / size;
	result.y = vec.y / size;
	result.z = vec.z / size;

	return result;
}
























