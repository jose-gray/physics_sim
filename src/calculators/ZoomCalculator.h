#include "../objects/objects.h"

class ZoomCalculator
{
public:
    ZoomCalculator(const Vector center) : center(center){};
    void zoomIn(Objects &objects);
    void zoomOut(Objects &objects);
    void noZoom(Objects &objects);

private:
    const Vector center;

    float scale_factor = 1;

    void zoom(Objects &objects, const float scale_factor);
    void zoomRocket(Rocket &rocket, const float scale_factor);
};
