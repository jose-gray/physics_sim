
class PressureCalculator
{
public:
    PressureCalculator();
    float getPressure() const;
    void addPressureOfFrame(float pressure);

private:
    void updateRollingAveragePressure();
    static const int number_of_frames_to_average = 400;
    float rolling_average_pressure;
    int number_of_frames;
    float pressure_each_frame[number_of_frames_to_average];
};
