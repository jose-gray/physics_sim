#include "Display.h"
#include <cstring>
#include <iostream>

Vector Display::convertToRaylibCoords(const Vector vector)
{
    return Vector{vector.getx(), box_dimensions.height - vector.gety()};
}

void Display::drawParticle(Particle &particle)
{
    const Vector position = convertToRaylibCoords(particle.getDisplayPosition());
    const int x_position = round(position[0]);
    const int y_position = round(position[1]);

    const int radius = particle.getDisplayRadius();

    Color color = particle.getColor();

    DrawCircle(x_position, y_position, radius, color);
}

void Display::drawWall(Wall &wall)
{
    const int x_1 = wall.getPosition_x_1();
    const int y_1 = box_dimensions.height - wall.getPosition_y_1();

    const int x_2 = wall.getPosition_x_2();
    const int y_2 = box_dimensions.height - wall.getPosition_y_2();

    DrawLine(x_1, y_1, x_2, y_2, RED);
}

void Display::drawRocket(Rocket &rocket)
{
    std::array<Vector, 4> vertices = rocket.getVertices();
    const int count = 4;
    for (int i = 0; i < count; i++)
    {
        const Vector vertex_1 = convertToRaylibCoords(vertices[i]);
        const Vector vertex_2 = convertToRaylibCoords(vertices[(i + 1) % count]);

        DrawLine(vertex_1.getx(), vertex_1.gety(), vertex_2.getx(), vertex_2.gety(), RED);
    }

    for(Engine engine : rocket.engines)
    {
        if(engine.is_on)
        {
            const Vector start = convertToRaylibCoords(engine.display_line[0]);
            const Vector end = convertToRaylibCoords(engine.display_line[1]);
            DrawLine(start[0], start[1], end[0], end[1], GREEN);
        }
    }

    const Vector center_top = convertToRaylibCoords(0.5 * (vertices[0] + vertices[1]));
    
    DrawCircle(center_top[0], center_top[1], 3, WHITE);
}

void Display::drawDot(Dot &dot)
{
    const Vector position = convertToRaylibCoords(dot.getDisplayPosition());
    const int x_position = round(position[0]);
    const int y_position = round(position[1]);

    const int radius = 1;

    Color color = WHITE;

    DrawCircle(x_position, y_position, radius, color);
}

void Display::intialiseWindow()
{
    InitWindow(box_dimensions.width, box_dimensions.height, "Particles");
    SetWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
    SetWindowSize(box_dimensions.width, box_dimensions.height);
    SetTargetFPS(1000);
}

void Display::drawTemperature(float T)
{
    std::string text;

    text += "T: ";
    text += sig_figs_calculator.roundSigFigs(T);
    text += " K";

    const int size = text.length() + 1;

    char text_char[size];
    strcpy(text_char, text.c_str());

    DrawRectangle(0, 0, 250, 75, {255, 255, 255, 200});

    DrawText(text_char, 15, 15, 40, BLACK);
}

void Display::drawPressure(float P)
{
    std::string text;

    text += "P: ";
    text += sig_figs_calculator.roundSigFigs(P);
    text += " Pa";

    const int size = text.length() + 1;

    char text_char[size];
    strcpy(text_char, text.c_str());

    DrawRectangle(0, 75, 250, 75, {255, 255, 255, 200});

    DrawText(text_char, 15, 90, 40, BLACK);
}

void Display::drawRocketData(const RocketData &rocket_data)
{
    std::string text;

    text += "Displacement: ";
    text += sig_figs_calculator.roundSigFigs(rocket_data.displacement.getx());
    text += " , ";
    text += sig_figs_calculator.roundSigFigs(rocket_data.displacement.gety());

    text += "\n";

    text += "Velocity: ";
    text += sig_figs_calculator.roundSigFigs(rocket_data.velocity.getx());
    text += ", ";
    text += sig_figs_calculator.roundSigFigs(rocket_data.velocity.gety());

    const int size = text.length() + 1;

    char text_char[size];
    strcpy(text_char, text.c_str());

    DrawRectangle(0, 75, 650, 150, {255, 255, 255, 200});

    DrawText(text_char, 15, 90, 40, BLACK);
}

void Display::drawRocketLineToPlanet(const Rocket &rocket, const RocketData &rocket_data)
{

    const std::optional<Vector> direction_option = rocket_data.displacement.getDirectionVector();
    if(direction_option.has_value())
    {
        const Vector rocket_pos = rocket.getDisplayPosition();
        const Vector start_position = convertToRaylibCoords(rocket_pos);

        const Vector direction = direction_option.value();
        const Vector end_position = convertToRaylibCoords(rocket_pos + direction * -50);

        DrawLine(start_position.getx(), start_position.gety(), end_position.getx(), end_position.gety(), BLUE);
    }
}

void Display::run(Objects &objects)
{
    intialiseWindow();

    int number_of_passes = 0;
    float total_time_in_function = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(Color{60, 60, 60, 255});

        const float time_before = time.getCurrentTime();

        calculator_manager.calculateUpdates(objects);

        for (Particle &particle : objects.particles)
        {
            drawParticle(particle);
        }

        if (demo_mode == thermo)
        {
            for (Wall &wall : objects.walls)
            {
                drawWall(wall);
            }

            const float T = calculator_manager.getTemperature(objects.particles);
            drawTemperature(T);

            const float P = calculator_manager.getPressure();
            drawPressure(P);
        }

        if (demo_mode == rocket_mode)
        {
            drawRocket(objects.rocket);
            drawRocketData(objects.rocket_data);
            drawRocketLineToPlanet(objects.rocket, objects.rocket_data);
        }

        for (Dot &dot : objects.dot_data.dots)
        {
            drawDot(dot);
        }

        EndDrawing();

        const float time_after = time.getCurrentTime();
        const float time_taken = time_after - time_before;
        number_of_passes++;

        total_time_in_function += time_taken;

        const int average_over = 2500;

        if (number_of_passes % average_over == 0)
        {
            const float mean_time = total_time_in_function / average_over;
            const float frame_rate = (float)1 / mean_time;
            std::string rounded_frame_rate = sig_figs_calculator.roundSigFigs(frame_rate);
            std::cout << rounded_frame_rate << " fps\n";
            total_time_in_function = 0;
        }
    }

    CloseWindow();
}
