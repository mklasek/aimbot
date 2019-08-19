#pragma once

#include "offsets.h"
#include "memory.h"
#include "vector.h"
#include <vector>
#include <iostream>


class Entity
{
public:
	int number;
	int health;
	int teamNum;
	unsigned int entPtr;
	unsigned int bonePtr;

	Entity();
	Entity(int num);
	~Entity();

	void UpdateHealth();
	void UpdateTeam();
	bool IsDormant();
	void SetPtrs();
	void SetPtrs(int num);
	
	Vector3D GetBone(int bone);

	
};

class EntityList
{
public:
	Entity entlist[5];

	EntityList();
	~EntityList();

	void CycleEntities();
};

