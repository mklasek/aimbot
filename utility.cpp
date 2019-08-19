#include "utility.h"

Vector3D elemx(1, 0, 0);
Vector3D elemy(0, 1, 0);
Vector3D elemz(0, 0, 1);

Vector3D AngleToNVecLR(angle alfa)
{
	Vector3D result;

	angle radalfa = (alfa / 180) * M_PI;

	float y = (sqrtf(1 - cos(radalfa) * cos(radalfa))) / cos(radalfa);

	if (alfa > 0 && alfa < 90)
	{
		result.x = 1;
		result.y = y;
		result.z = 0;
	}
	else if (alfa > 90)
	{
		result.x = -1;
		result.y = -y;
		result.z = 0;
	}
	else if (alfa < 0 && alfa > -90)
	{
		result.x = 1;
		result.y = -y;
		result.z = 0;
	}
	else
	{
		result.x = -1;
		result.y = y;
		result.z = 0;
	}

	return result;
}

Vector3D AngleToNVecUD(angle alfa, Vector3D horvec)					//corrected
{
	Vector3D result;
	result = horvec;
	result.z = 0;

	angle radalfa = (alfa / 180) * M_PI;

	float z = sqrtf(pow(1 / cos(radalfa), 2) - 1) * sqrtf(pow(horvec.x, 2) + pow(horvec.y, 2));


	if (alfa > 0)
	{
		result.z = -z;
	}
	else
	{
		result.z = z;
	}

	return result;
}




angle HorAngle(angle hor, Vector3D ownPos, Vector3D enemyPos)
{
	Vector3D horPOV = AngleToNVecLR(hor);
	Vector3D locVector = SubVectors(enemyPos, ownPos);

	Vector3D halp1, halp2, halp3, halp4;
	halp1 = Project3DVec(horPOV, 'z');
	halp2 = Project3DVec(locVector, 'z');

	angle horizontal = VectorsAngle3D(halp1, halp2);

	halp3 = Xprod(elemx, elemy);
	halp4 = Xprod(halp1, halp2);

	if (Vec3DXscalar(halp3, halp4) < 0)
		horizontal = -horizontal;

	return horizontal;
}

angle VerAngle(angle ver, Vector3D ownPos, Vector3D enemyPos)
{
	Vector3D locVector = SubVectors(enemyPos, ownPos);
	Vector3D verPOV = AngleToNVecUD(ver, locVector);
	Vector3D halp1, halp2, halp3, halp4;
	halp2 = Project3DVec(locVector, 'z');

	angle vertical = VectorsAngle3D(verPOV, locVector);

	halp1 = SubVectors(locVector, verPOV);
	if (halp1.z > 0)
		vertical = -vertical;

	return vertical;

}

Vector3D AngleReg(angle hor, angle ver, int horFoV, int verFoV, int speed)
{
	Vector3D result;
	if (abs(hor) > horFoV || abs(ver) > verFoV)
	{
		result.z = -1;
		return result;
	}

	if (abs(hor) < 0.1)
		result.x = 960;
	else if (hor < 0)
		result.x = (int)(960 - speed * hor);
	else
		result.x = (int)(960 - speed * hor);

	if (abs(ver) < 0.1)
		result.y = 540;
	else if (ver > 0)
		result.y = (int)(540 + speed * ver);
	else
		result.y = (int)(540 + speed * ver);

	return result;
}


float GetDist(Vector3D ownPos, Vector3D enemyPos)
{
	Vector3D locVector;
	locVector = SubVectors(enemyPos, ownPos);
	return Vec3Dlength(locVector);
}