#include <cstddef>
namespace offsets {
	//Buttons.hpp
	constexpr std::ptrdiff_t Force_Jump = 0x17348E0;

	//offsets.hpp
	constexpr std::ptrdiff_t dwEntityList = 0x18C7F98;
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x173B568;
	constexpr std::ptrdiff_t dwViewAngles = 0x1935FE0;


	//client.dll
	constexpr std::ptrdiff_t m_iIDEntIndex = 0x13B0;
	constexpr std::ptrdiff_t m_iTeamNum = 0x3CB;
	constexpr std::ptrdiff_t m_iHealth = 0x334;
	constexpr std::ptrdiff_t fFlags = 0x3D4;
	constexpr std::ptrdiff_t vecOrigin = 0x127C;
	constexpr std::ptrdiff_t m_flFlashDuration = 0x1364;
	constexpr std::ptrdiff_t m_entitySpottedState = 0x2278;
	constexpr std::ptrdiff_t m_bSpottedByMask = 0xC;
	


	//glow esp is patched
	constexpr std::ptrdiff_t m_fl_detected_by_enemy_sensor_time = 5184;

}
