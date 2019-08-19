// INCLUDES
#include <iostream>
#include "vector.h"
#include "memory.h"
#include "utility.h"
#include "offsets.h"
#include "entity.h"
#include <chrono>
#include <cmath>
#include <vector>
//-------------------------------------------------------------------------------
// GLOBAL VARS
int boneID = 6;
int horFoV = 2;
int verFoV = 3;
int speed = 7;
int counter = 0;

DWORD localplayer;
DWORD clientstate;
DWORD entityptr;
DWORD boneptr;

EntityList entlist;
//-------------------------------------------------------------------------------
// AIMBOT THREAD
DWORD WINAPI aimboat(LPVOID In)
{
	Vector3D ownPos;
	Vector3D enemyPos;
	Vector3D coords;
	angle hor, hor2;
	angle ver, ver2;
	while (true)
	{
		Sleep(3);
		// CONTROLS
		if ((GetAsyncKeyState(VK_TAB) & 0x8000) || (GetAsyncKeyState(VK_LBUTTON) & 0x8000))		// quick help
		{
			Sleep(100);
			continue;
		}
		//-------------------------------------------------------------------------------
		// OWN READS
		ownPos.x = Kevin.Read<float>(localplayer + vecOrigin);
		ownPos.y = Kevin.Read<float>(localplayer + vecOrigin + 4);
		ownPos.z = Kevin.Read<float>(localplayer + vecOrigin + 8) + Kevin.Read<float>(localplayer + vecOffset + 8);

		ver = Kevin.Read<float>(clientstate + viewAngles);
		hor = Kevin.Read<float>(clientstate + viewAngles + 4);
		//-------------------------------------------------------------------------------
		// BEEP INFO
		if (GetAsyncKeyState(VK_LMENU) & 0x8000)						
		{
			counter = 0;
			for (int j = 0; j < 5; j++)
			{
				entlist.entlist[j].UpdateHealth();
				if (entlist.entlist[j].health == 0)
					continue;

				enemyPos = entlist.entlist[j].GetBone(boneID);
				if (abs(enemyPos.x) + abs(enemyPos.y) + abs(enemyPos.z) > 5000)
					continue;

				hor2 = HorAngle(hor, ownPos, enemyPos);
				ver2 = VerAngle(ver, ownPos, enemyPos);
				if (abs(hor2) > 55 || abs(ver2) > 34)
					continue;
				else
					counter++;
			}

			
            if (counter > 0)
            {
                switch (counter)
                {
                case 1:
                    Beep(200, 500);
                    break;
                case 2:
                    Beep(300, 500);
                    break;
                case 3:
                    Beep(1000, 500);
                    break;
                case 4:
                    Beep(2500, 500);
                    break;
                default:
                    Beep(6000, 500);
                    break;
                }
            }

			Sleep(500);
			continue;
		}
		//-------------------------------------------------------------------------------
		// ENEMY READS AND ACTION
		for (int j = 0; j < 5; j++)
		{
			if (entlist.entlist[j].IsDormant())
				continue;

			enemyPos = entlist.entlist[j].GetBone(boneID);
			if (abs(enemyPos.x) + abs(enemyPos.y) + abs(enemyPos.z) > 5000)
				continue;

			hor2 = HorAngle(hor, ownPos, enemyPos);
			ver2 = VerAngle(ver, ownPos, enemyPos);
			coords = AngleReg(hor2, ver2, horFoV, verFoV, speed);

			if (coords.z == -1)
				continue;
			else
			{
				SetCursorPos(coords.x, coords.y);
				break;
			}
		}
		//-------------------------------------------------------------------------------
	}
}
//-------------------------------------------------------------------------------

DWORD WINAPI proxbeep(LPVOID In)
{
	Vector3D ownPos;
	Vector3D enemyPos;
	float distance = 0;
	angle hor, hor2;
	int freq, radius;
	while (true)
	{
		// OWN READS
		ownPos.x = Kevin.Read<float>(localplayer + vecOrigin);
		ownPos.y = Kevin.Read<float>(localplayer + vecOrigin + 4);
		ownPos.z = Kevin.Read<float>(localplayer + vecOrigin + 8) + Kevin.Read<float>(localplayer + vecOffset + 8);
		//-------------------------------------------------------------------------------
		// MAIN LOOP
		for (int j = 0; j < 5; j++)
		{
			entlist.entlist[j].UpdateHealth();
			if (entlist.entlist[j].IsDormant() || entlist.entlist[j].health <= 0)
				continue;

			hor = Kevin.Read<float>(clientstate + viewAngles + 4);
			hor2 = HorAngle(hor, ownPos, enemyPos);

			enemyPos = entlist.entlist[j].GetBone(boneID);
			distance = GetDist(ownPos, enemyPos);

			if (abs(hor2) > 90)
			{
				freq = 1200;
				radius = 1000;
			}
			else
			{
				freq = 400;
				radius = 600;
			}


			if (distance < radius)
			{
				Beep(freq, 250);
				Sleep(400 * pow(distance/radius,2));
				break;
			}
			else
				continue;
		}
	}
		//-------------------------------------------------------------------------------
}


int main()
{
	// INITIALIZATION
	bool toggle = false;
	bool toggle2 = false;
	bool gunmode = false;

	Kevin.GetHandle("csgo.exe");
	Kevin.GetModules();

	localplayer = Kevin.Read<DWORD>(Kevin.ClientDLL_base + dwLocalPlayer);
	clientstate = Kevin.Read<DWORD>(Kevin.EngineDLL_base + dwClientState);

	entlist.CycleEntities();

	HANDLE aimthread = CreateThread(NULL, 0, aimboat, NULL, CREATE_SUSPENDED, NULL);
	HANDLE proxthread = CreateThread(NULL, 0, proxbeep, NULL, CREATE_SUSPENDED, NULL);

	std::cout << "F6 to update entities" << std::endl << "F7 to switch head/chest" << std::endl << "Caps Lock to toggle aimbot" << std::endl;
	std::cout << "left Alt for screen beep check" << std::endl;
	//-------------------------------------------------------------------------------
	// CONTROLS

	while (true)
	{
		Sleep(500);
		if (GetAsyncKeyState(VK_CAPITAL))		// toggle aimbot thread
		{
			if (!toggle)
				ResumeThread(aimthread);
			else
				SuspendThread(aimthread);

			toggle = !toggle;
		}

		if (GetAsyncKeyState(VK_NUMLOCK))		// toggle aimbot thread
		{
			if (!toggle)
				ResumeThread(proxthread);
			else
				SuspendThread(proxthread);

			toggle2 = !toggle2;
		}
		
		if (GetAsyncKeyState(VK_F7))		// toggle head/chest
		{
			if (!gunmode)
				boneID = bone_chest;
			else
				boneID = bone_head;

			gunmode = !gunmode;
		}
		if (GetAsyncKeyState(VK_F6))
		{
			entlist.CycleEntities();			// update entity list
		}
	}
	//--------------------------------------------------------------------------------

	return 0;
}
