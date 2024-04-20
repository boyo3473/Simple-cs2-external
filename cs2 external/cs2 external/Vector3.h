#include <cmath>
#include <corecrt_math_defines.h>

struct Vector3 {
    float x, y, z;
};

Vector3 CalcAngle(const Vector3& source, const Vector3& destination) {
    Vector3 angle;

    Vector3 delta = { destination.x - source.x, destination.y - source.y, destination.z - source.z };

    angle.y = atan2(delta.y, delta.x) * 180.0 / M_PI;

    float xyDist = sqrt(delta.x * delta.x + delta.y * delta.y);
    angle.x = atan2(-delta.z, xyDist) * 180.0 / M_PI;

    angle.z = 0;

    return angle;
}