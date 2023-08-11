#include <gtest/gtest.h>

#include "../src/calculators/SigFigsCalculator.h"


TEST(sig_figs, goldilocks_number)
{
    sigFigsCalculator sig_figs_calculator;
    //given
    double input = 12.3456;

    //when
    std::string output = sig_figs_calculator.roundSigFigs(input);

    //then
    ASSERT_EQ("12", output);
}

TEST(sig_figs, large_number)
{
    sigFigsCalculator sig_figs_calculator;
    //given
    double input = 123456;

    //when
    std::string output = sig_figs_calculator.roundSigFigs(input);

    //then
    ASSERT_EQ("120000", output);
}

TEST(sig_figs, medium_number)
{
    sigFigsCalculator sig_figs_calculator;
    //given
    double input = 1.23456;

    //when
    std::string output = sig_figs_calculator.roundSigFigs(input);

    //then
    ASSERT_EQ("1.2", output);
}

TEST(sig_figs, medium_number_rounding)
{
    sigFigsCalculator sig_figs_calculator;
    //given
    double input = 9.23456;

    //when
    std::string output = sig_figs_calculator.roundSigFigs(input);

    //then
    ASSERT_EQ("9.2", output);
}

TEST(sig_figs, medium_number_rounding_2)
{
    sigFigsCalculator sig_figs_calculator;
    //given
    double input = 6.93456;

    //when
    std::string output = sig_figs_calculator.roundSigFigs(input);

    //then
    ASSERT_EQ("6.9", output);
}

TEST(sig_figs, medium_number_rounding_3)
{
    sigFigsCalculator sig_figs_calculator;
    //given
    double input = 9.99456;

    //when
    std::string output = sig_figs_calculator.roundSigFigs(input);

    //then
    ASSERT_EQ("10.0", output);
}

TEST(sig_figs, small_number)
{
    sigFigsCalculator sig_figs_calculator;
    //given
    double input = 0.0123456;

    //when
    std::string output = sig_figs_calculator.roundSigFigs(input);

    //then
    ASSERT_EQ("0.012", output);
}