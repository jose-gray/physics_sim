#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <cmath>

struct sigFigsCalculator
{
    std::string roundSigFigs(double input)
    {
        if(input == 0)
        {
            return "0";
        }
        
        std::string output;
        if (input < 0)
        {
            output += "-";
            input *= -1; // hack 
        }

        const int order_of_magnitude = floor(log10(input));

        const int order_of_magnitude_of_last_sig_fig = order_of_magnitude - 1;

        int output_number;
        float sig_digits;

        if (order_of_magnitude_of_last_sig_fig >= 0)
        {
            sig_digits = round(input * pow(10, -1 * order_of_magnitude_of_last_sig_fig));

            output_number = sig_digits * pow(10, order_of_magnitude_of_last_sig_fig);

            output += std::to_string(output_number);
        }
        else if (order_of_magnitude == 0)
        {
            float sig_digits = round(input * 10);

            int first_sig_digit = floor(sig_digits / 10);

            int second_sig_digit = floor(sig_digits - 10 * first_sig_digit);

            output += std::to_string(first_sig_digit);
            output += ".";
            output += std::to_string(second_sig_digit);
        }
        else
        {
            output += "0.";
            for (int i = 0; i < -1 * order_of_magnitude - 1; i++)
            {
                output += "0";
            }

            sig_digits = round(input * pow(10, -1 * order_of_magnitude_of_last_sig_fig));
            output_number = (int)sig_digits;
            output += std::to_string(output_number);
        }

        return output;
    }
};