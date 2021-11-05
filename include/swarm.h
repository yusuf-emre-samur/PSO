#ifndef SWARM_H
#define SWARM_H
#include "Eigen/Dense"
#include "vector"
#include "iostream"
#include "string"
#include "functional"
#include <fstream>
#include "i_swarm.h"
#include "particle.h"
#include "swarm_parameter.h"

namespace pso
{

class Swarm : public ISwarm
{
public:
    Swarm(SwarmParameter const& swarm_params);

    // main
    void minimize() override;
    // to csv
    void print_summary() const override;
    void summary_to_csv() const override;

private:
    const SwarmParameter swarm_parameter_;

    std::vector<Particle *> particles_;
    Position pg_;
    std::vector<double> history_min_cost;
};

}

#endif