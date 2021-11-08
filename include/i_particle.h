#ifndef I_PARTICLE_H
#define I_PARTICLE_H

#include "Eigen/Dense"
#include "particle_parameter.h"
#include "vector"

namespace pso {

using Scalar = double;
using Position = Eigen::Matrix<Scalar, 2, 1>;
using Velocity = Eigen::Matrix<Scalar, 2, 1>;

class IParticle
{
  public:
	~IParticle() = default;

	// get
	virtual Position const& p() const = 0;
	virtual Position const& pb() const = 0;
	virtual double cost_pb() const = 0;
	virtual std::vector<Position> const& position_history() const = 0;
	// upadte
	virtual void update_pg(Position const& new_pg) = 0;
	// step
	virtual double const step() = 0;
};

} // namespace pso

#endif