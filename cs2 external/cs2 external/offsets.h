#include <cstddef>
namespace offsets {
	//Buttons.hpp
	constexpr std::ptrdiff_t Force_Jump = 0x1736920;

	//offsets.hpp
	constexpr std::ptrdiff_t dwEntityList = 0x18C9E78;
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x173D5A8;
	constexpr std::ptrdiff_t dwViewAngles = 0x1937E50;


	//client.dll
	constexpr std::ptrdiff_t m_iIDEntIndex = 0x13B0;
	constexpr std::ptrdiff_t m_iTeamNum = 0x3CB;
	constexpr std::ptrdiff_t m_iHealth = 0x334;
	constexpr std::ptrdiff_t fFlags = 0x3D4;
	constexpr std::ptrdiff_t vecOrigin = 0x127C;
	


	//glow esp is patched
	constexpr std::ptrdiff_t m_fl_detected_by_enemy_sensor_time = 5184;

}
