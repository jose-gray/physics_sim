#include "../objects/Wall.h"
#include <math.h>

class WallCalculator
{
public:
    void updateWall(Wall &wall, float time_now);

private:
    void getWallVariables(Wall &wall, float time_now);

    void updatePositionOscillations(Wall &wall, float time_now);
    void updateVelocityOscillations(Wall &wall, float time_now);

    bool is_oscillating;

    float position;
    float velocity;
    float time_increment;
};