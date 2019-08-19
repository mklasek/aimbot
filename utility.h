#pragma once

#include "vector.h"


Vector3D AngleToNVecLR(angle alfa);
Vector3D AngleToNVecUD(angle A, Vector3D horvec);

angle HorAngle(angle hor, Vector3D ownPos, Vector3D enemyPos);
angle VerAngle(angle ver, Vector3D ownPos, Vector3D enemyPos);

Vector3D AngleReg(angle hor, angle ver, int horFoV, int verFoV, int speed);
float GetDist(Vector3D ownPos, Vector3D enemyPos);
