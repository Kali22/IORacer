#include <Box2D.h>
#include <MathUtil.h>

float MathUtil::DegreeToRadian(float angle) {
    return angle * b2_pi / 180;
}

float MathUtil::RadianToDegree(float angle) {
    return angle * 180 / b2_pi;
}
