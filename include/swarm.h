#ifndef SWARM_H
#define SWARM_H
#include "Eigen/Dense"
#include "functional"
#include "particle.h"
// std lib
#include "swarm_parameter.h"
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace pso {

class Swarm
{
  public:
	Swarm(const SwarmParameter& swarm_params);

	// main
	void minimize();
	// to csv
	void print_summary() const;
	void summary_to_csv() const;

  private:
	const SwarmParameter swarm_parameter_;
	// population
	std::vector<std::shared_ptr<Particle>> particles_;
	// best position
	Position pg_;
	double cost_pg_;
	std::vector<double> history_min_cost_;
};

} // namespace pso

#endif