#include "entity.h"


Entity::Entity()
{

}

Entity::Entity(int num)
{
	number = num;
	entPtr = Kevin.Read<DWORD>(Kevin.ClientDLL_base + dwEntityList + 0x10 * (num));
	bonePtr = Kevin.Read<DWORD>(entPtr + dwBoneMatrix);
	teamNum = Kevin.Read<int>(entPtr + iTeamNum);
}

Entity::~Entity()
{

}

void Entity::UpdateHealth()
{
	health = Kevin.Read<int>(entPtr + iHealth);
}

void Entity::UpdateTeam()
{
	teamNum = Kevin.Read<int>(entPtr + iTeamNum);
}

bool Entity::IsDormant()
{
	return Kevin.Read<bool>(entPtr + dormant);
}


Vector3D Entity::GetBone(int bone)
{
	Vector3D result;
	result.x = Kevin.Read<float>(bonePtr + 0x30 * bone + 0x0C);
	result.y = Kevin.Read<float>(bonePtr + 0x30 * bone + 0x1C);
	result.z = Kevin.Read<float>(bonePtr + 0x30 * bone + 0x2C);

	return result;
}

void Entity::SetPtrs()
{
	entPtr = Kevin.Read<DWORD>(Kevin.ClientDLL_base + dwEntityList + 0x10 * (number - 1));
	bonePtr = Kevin.Read<DWORD>(entPtr + dwBoneMatrix);
}

void Entity::SetPtrs(int num)
{
	entPtr = Kevin.Read<DWORD>(Kevin.ClientDLL_base + dwEntityList + 0x10 * (num - 1));
	bonePtr = Kevin.Read<DWORD>(entPtr + dwBoneMatrix);
}










EntityList::EntityList()
{

}

EntityList::~EntityList()
{

}


void EntityList::CycleEntities()
{
	int y = 0;
	int myteam = 0;
	int enteam;
	DWORD localplayer = Kevin.Read<DWORD>(Kevin.ClientDLL_base + dwLocalPlayer);
	myteam = Kevin.Read<int>(localplayer + iTeamNum);

	DWORD enemyplayer;
	for (int i = 1; i < 10; i++)
	{
		enemyplayer = Kevin.Read<DWORD>(Kevin.ClientDLL_base + dwEntityList + 0x10 * (i));
		enteam = Kevin.Read<int>(enemyplayer + iTeamNum);
		if (abs(enteam) > 3)
			continue;
		if (enteam != myteam)
		{
			entlist[y] = Entity(i);
			y++;
		}
	}
}


