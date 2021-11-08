#ifndef SWARM_H
#define SWARM_H
#include "Eigen/Dense"
#include "functional"
#include "i_swarm.h"
#include "iostream"
#include "particle.h"
#include "string"
#include "swarm_parameter.h"
#include "vector"
#include <fstream>

namespace pso {

class Swarm : public ISwarm {
  public:
    Swarm(SwarmParameter const& swarm_params);

    // main
    void minimize() override;
    // to csv
    void print_summary() const override;
    void summary_to_csv() const override;

  private:
    const SwarmParameter swarm_parameter_;
    // population
    std::vector<Particle*> particles_;
    // best position
    Position pg_;
    double cost_pg_;
    std::vector<double> history_min_cost;
};

} // namespace pso

#endif