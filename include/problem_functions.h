#ifndef PROBLEM_FUNCTIONS_H
#define PROBLEM_FUNCTIONS_H
#include "particle.h"
#include "cmath"
#include "math.h"


namespace pso{

class ProblemFunctions
{
public:
    static double const drop_wave(pso::Position const &pos)
    {
        const double x1 = pos.x();
        const double x2 = pos.y();
        return -(1 + std::cos(12 * std::sqrt(std::pow(x1, 2) + std::pow(x2, 2)))) / (0.5 * (std::pow(x1, 2) + std::pow(x2, 2)) + 2);
    }

    static double const ackley_function(pso::Position const &pos)
    {
        const double a = 20;
        const double b = 0.2;
        const double c = 2 * M_PI;
        const double x1 = pos.x();
        const double x2 = pos.y();
        return -a * std::exp(-b * std::sqrt(1/2*( std::pow(x1,2) + std::pow(x2,2) ))) - std::exp(1/2*( std::cos(c*x1) + std::cos(c*x2) )) + a + std::exp(1);
    }

    static double const rosenbrock_function(pso::Position const& pos)
    {
        const double x1 = pos.x();
        const double x2 = pos.y();
        return 100 * std::pow((x2 - std::pow(x1,2)),2 ) + std::pow(x1-1, 2);
    }


    static double const levy_n13_function(pso::Position const& pos)
    {
        const double x1 = pos.x();
        const double x2 = pos.y();
        return std::pow(std::sin(3*M_PI*x1), 2) + std::pow((x1-1), 2) * (1 + std::pow((3*M_PI*x2), 2)) + std::pow((x2-1), 2) * (1 + std::pow((2*M_PI*x2), 2));
    }
};

}

#endif