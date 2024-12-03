#include <servo.hpp>

int convertIntensityToDegrees(int intensityScore)
{
    return (maxDegree + 1) * (intensityScore - minIntensity) / (maxIntensity - minIntensity + 1);
}