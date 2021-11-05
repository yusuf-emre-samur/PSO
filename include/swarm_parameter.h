#ifndef SWARM_PARAMETER_H
#define SWARM_PARAMETER_H
#include "functional"
#include "string"
#include "particle_parameter.h"

namespace pso{

class SwarmParameter
{
public:
    SwarmParameter(unsigned int const& population_size, std::function<double const(Position const &)> problem_func, std::string const& function_name, ParticleParameter const& particle_parameter)
    : population_size(population_size), problem_func(problem_func), function_name(function_name), particle_parameter(particle_parameter)
    {}
    ~SwarmParameter() = default;

    const unsigned int population_size;
    const std::function<double const(Position const &)> problem_func;
    const std::string function_name;
    const ParticleParameter particle_parameter;
};

}


#endif