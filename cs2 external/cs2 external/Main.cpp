#include "memory.h"
#include <iostream>
#include <thread>
#include "offsets.h"
#include "Vector3.h"




using namespace std;

namespace config {
    bool aimbot = true;
    bool trigger_bot = true;
    bool bunny_hop = true;
    bool team_check = true;
    bool Glow_esp = true;

}






void Trigger_bot(Memory& mem, uintptr_t client) {
    while (true) {
        if (GetAsyncKeyState(VK_SHIFT) && config::trigger_bot) {
            const auto localPlayer = mem.Read<LONGLONG>(client + offsets::dwLocalPlayerPawn);
            const auto playerTeam = mem.Read<int>(localPlayer + offsets::m_iTeamNum);
            const auto entityId = mem.Read<int>(localPlayer + offsets::m_iIDEntIndex);

            if (localPlayer) {
                auto health = mem.Read<LONGLONG>(localPlayer + offsets::m_iHealth);

                if (health && entityId > 0) {
                    auto entList = mem.Read<LONGLONG>(client + offsets::dwEntityList);
                    auto entEntry = mem.Read<LONGLONG>(entList + 0x8 * (entityId >> 9) + 0x10);
                    auto entity = mem.Read<LONGLONG>(entEntry + 120 * (entityId & 0x1FF));
                    auto entityTeam = mem.Read<int>(entity + offsets::m_iTeamNum);

                    bool shouldShoot = true;

                    if (config::team_check) {
                        if (entityTeam == playerTeam) {
                            shouldShoot = false;
                        }
                    }

                    if (shouldShoot) {
                        auto entityHp = mem.Read<int>(entity + offsets::m_iHealth);
                        if (entityHp > 0) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                            std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void bunny_hop(Memory& mem, uintptr_t client) {
    while (true) {
        if (config::bunny_hop == true)
        {

            const auto localPlayer = mem.Read<LONGLONG>(client + offsets::dwLocalPlayerPawn);
            if (localPlayer) {
                int32_t m_fFlags = mem.Read<int32_t>(localPlayer + offsets::fFlags);
                if (GetAsyncKeyState(VK_SPACE) && (m_fFlags & (1 << 0))) {
                    mem.Write<int>(client + offsets::Force_Jump, 65537);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    mem.Write<int>(client + offsets::Force_Jump, 256);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void mainmenu() {
    while (true) {

        cout << "cs2 external" << endl;
        cout << "toggle trigger bot: F1" << endl;
        cout << "toggle bunny hop: F2" << endl;
        cout << "toggle aimbot: F3" << endl;
        cout << "toggle Glow esp: F4" << endl;
        cout << "toggle Team Check: F5" << endl;



        if (GetAsyncKeyState(VK_F1))
        {
            if (config::trigger_bot == true)
            {
                cout << "trigger bot: off" << endl;
                Sleep(800);
                config::trigger_bot = false;
            }
            else
            {
                cout << "trigger bot: on" << endl;
                Sleep(800);
                config::trigger_bot = true;
            }

        }

        if (GetAsyncKeyState(VK_F2))
        {
            if (config::bunny_hop == true)
            {
                cout << "bunny hop: off" << endl;
                Sleep(800);
                config::bunny_hop = false;
            }
            else
            {
                cout << "bunny hop: on" << endl;
                Sleep(800);
                config::bunny_hop = true;
            }

        }

        if (GetAsyncKeyState(VK_F3))
        {
            if (config::aimbot == true)
            {
                cout << "aimbot: off" << endl;
                Sleep(800);
                config::aimbot = false;
            }
            else
            {
                cout << "aimbot: on" << endl;
                Sleep(800);
                config::aimbot = true;
            }

        }

        if (GetAsyncKeyState(VK_F4))
        {
            if (config::Glow_esp == true)
            {
                cout << "Glow esp: off" << endl;
                Sleep(800);
                config::Glow_esp = false;
            }
            else
            {
                cout << "Glow esp: on" << endl;
                Sleep(800);
                config::Glow_esp = true;
            }

        }

        if (GetAsyncKeyState(VK_F5))
        {
            if (config::team_check == true)
            {
                cout << "Team Check: off" << endl;
                Sleep(800);
                config::team_check = false;
            }
            else
            {
                cout << "Team Check: on" << endl;
                Sleep(800);
                config::team_check = true;
            }

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("cls");
    }
}

void aimbot(Memory& mem, uintptr_t client) {
    Vector3 localPlayerPos;

    while (true) {

        uintptr_t localPlayer = mem.Read<uintptr_t>(client + offsets::dwLocalPlayerPawn);
        if (!localPlayer) {
            continue;
        }

        localPlayerPos = mem.Read<Vector3>(localPlayer + offsets::vecOrigin);

        Vector3 viewAngles = mem.Read<Vector3>(client + offsets::dwViewAngles);

        float closestDistance = FLT_MAX;
        uintptr_t closestEntityPawn = 0;

        for (int i = 0; i < 64; i++) {
            uintptr_t Entity = mem.Read<uintptr_t>(client + offsets::dwEntityList);

            uintptr_t listEntity = mem.Read<uintptr_t>(Entity + ((8 * (i & 0x7FFF) >> 9) + 16));
            if (listEntity == 0)
                continue;

            uintptr_t entityController = mem.Read<uintptr_t>(listEntity + (120) * (i & 0x1FF));
            if (entityController == 0)
                continue;

            uintptr_t entityControllerPawn = mem.Read<uintptr_t>(entityController + 0x7E4);
            if (entityControllerPawn == 0)
                continue;

            listEntity = mem.Read<uintptr_t>(Entity + (0x8 * ((entityControllerPawn & 0x7FFF) >> 9) + 16));
            if (listEntity == 0)
                continue;

            uintptr_t entityPawn = mem.Read<uintptr_t>(listEntity + (120) * (entityControllerPawn & 0x1FF));
            if (entityPawn == 0)
                continue;

            int playerTeam = mem.Read<int>(entityPawn + offsets::m_iTeamNum);
            int playerHealth = mem.Read<int>(entityPawn + offsets::m_iHealth);



            if (config::team_check == true )
            {
                if (playerTeam != mem.Read<int>(localPlayer + offsets::m_iTeamNum) && playerHealth > 0)
                {
                    Vector3 enemyPos = mem.Read<Vector3>(entityPawn + offsets::vecOrigin);
                    float distance = sqrt(pow(localPlayerPos.x - enemyPos.x, 2) +
                        pow(localPlayerPos.y - enemyPos.y, 2) +
                        pow(localPlayerPos.z - enemyPos.z, 2));

                    Vector3 vecToEnemy = { enemyPos.x - localPlayerPos.x, enemyPos.y - localPlayerPos.y, enemyPos.z - localPlayerPos.z };
                    Vector3 angleToEnemy = CalcAngle(localPlayerPos, enemyPos);
                    float fov = 3.0f;

                    if (fabs(angleToEnemy.y - viewAngles.y) < fov && distance < closestDistance) {
                        closestDistance = distance;
                        closestEntityPawn = entityPawn;
                    }
                }
            }
    
        else
        {
                if (playerHealth > 0 ) {




                    Vector3 enemyPos = mem.Read<Vector3>(entityPawn + offsets::vecOrigin);
                    float distance = sqrt(pow(localPlayerPos.x - enemyPos.x, 2) +
                        pow(localPlayerPos.y - enemyPos.y, 2) +
                        pow(localPlayerPos.z - enemyPos.z, 2));

                    Vector3 vecToEnemy = { enemyPos.x - localPlayerPos.x, enemyPos.y - localPlayerPos.y, enemyPos.z - localPlayerPos.z };
                    Vector3 angleToEnemy = CalcAngle(localPlayerPos, enemyPos);
                    float fov = 3.0f;

                    if (fabs(angleToEnemy.y - viewAngles.y) < fov && distance < closestDistance) {
                        closestDistance = distance;
                        closestEntityPawn = entityPawn;
                    }
                }
            }
        }

        int PlayerHealth = mem.Read<int>(closestEntityPawn + offsets::m_iHealth);
        if (GetAsyncKeyState(VK_SHIFT) && config::aimbot && closestEntityPawn != 0 && PlayerHealth > 0 && PlayerHealth <= 100) {
            if (closestEntityPawn != 0) {
                if (PlayerHealth <= 0 || PlayerHealth > 100)
                    continue;
               
                Vector3 closestEnemyPos = mem.Read<Vector3>(closestEntityPawn + offsets::vecOrigin);
                Vector3 angleToEnemy = CalcAngle(localPlayerPos, closestEnemyPos);

              
                Vector3 currentViewAngles = mem.Read<Vector3>(client + offsets::dwViewAngles);
                angleToEnemy.x = currentViewAngles.x; 
                angleToEnemy.z = currentViewAngles.z; 
    

                mem.Write<Vector3>(client + offsets::dwViewAngles, angleToEnemy);
                continue;
            }
        }



    }
}

void Glowesp(Memory& mem, uintptr_t client)
{
    while (true) {

        uintptr_t localPlayer = mem.Read<uintptr_t>(client + offsets::dwLocalPlayerPawn);
        if (!localPlayer) {
            continue;
        }



        Vector3 viewAngles = mem.Read<Vector3>(client + offsets::dwViewAngles);

        float closestDistance = FLT_MAX;
        uintptr_t closestEntityPawn = 0;

        for (int i = 0; i < 64; i++) {
            uintptr_t Entity = mem.Read<uintptr_t>(client + offsets::dwEntityList);

            uintptr_t listEntity = mem.Read<uintptr_t>(Entity + ((8 * (i & 0x7FFF) >> 9) + 16));
            if (listEntity == 0)
                continue;

            uintptr_t entityController = mem.Read<uintptr_t>(listEntity + (120) * (i & 0x1FF));
            if (entityController == 0)
                continue;

            uintptr_t entityControllerPawn = mem.Read<uintptr_t>(entityController + 0x7E4);
            if (entityControllerPawn == 0)
                continue;

            listEntity = mem.Read<uintptr_t>(Entity + (0x8 * ((entityControllerPawn & 0x7FFF) >> 9) + 16));
            if (listEntity == 0)
                continue;

            uintptr_t entityPawn = mem.Read<uintptr_t>(listEntity + (120) * (entityControllerPawn & 0x1FF));
            if (entityPawn == 0)
                continue;

            if (config::Glow_esp == true)
            {
               
                    mem.Write<float>(entityPawn + offsets::m_fl_detected_by_enemy_sensor_time, 86400.f);
                
            }
            else
            {
                mem.Write<float>(entityPawn + offsets::m_fl_detected_by_enemy_sensor_time, 0.f);
            }
        }
    }
}




int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    Memory mem{ "cs2.exe" };
    const auto client = mem.GetModuleAddress("client.dll");


    if (!client)
    {
        cout << "cs2 not found";
        Sleep(5000);
        return 0;
    }


    
    std::thread ab(aimbot, std::ref(mem), client);

    std::thread bh_thread(bunny_hop, std::ref(mem), client);
    std::thread tb_thread(Trigger_bot, std::ref(mem), client);

    std::thread glowesp_thread(Glowesp, std::ref(mem), client);

    std::thread mm_thread(mainmenu);

  
    mm_thread.join();
    ab.join();

    glowesp_thread.join();

    bh_thread.join();
    tb_thread.join();
    



    return 0;
}
