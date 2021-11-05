#ifndef I_PARTICLE_H
#define I_PARTICLE_H

#include "particle_parameter.h"
#include "vector"
#include "Eigen/Dense"

namespace pso{

using Scalar = double;
using Position = Eigen::Matrix<Scalar, 3, 1>;
using Velocity = Eigen::Matrix<Scalar, 2, 1>;

class IParticle{
public:
    ~IParticle() = default;

    // get
    virtual Position const& pb() const = 0;
    virtual Position const& p() const = 0;
    virtual std::vector<Position> const& position_history() const = 0;
    //upadte
    virtual void update_pg(Position const& new_pg) = 0;
    // set
    virtual void set_pg(Position const& new_pg) = 0;
    // step
    virtual Position const& step() = 0;
};

}


#endif 