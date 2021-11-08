#ifndef PARTICLE_H
#define PARTICLE_H
#include "Eigen/Dense"
#include "functional"
#include "i_particle.h"
#include "iostream"
#include "particle_parameter.h"
#include "random"
#include "vector"

namespace pso {

class Particle : public IParticle
{
  public:
    Particle(ParticleParameter particle_params,
             std::function<double const(Position const&)> problem_func,
             unsigned int const& x_spawn);
    ~Particle() = default;

    // get
    Position const& p() const override;
    Position const& pb() const override;
    double cost_pb() const override;
    ParticleParameter const& particle_parameter() const;
    std::vector<Position> const& position_history() const override;
    // upadte
    void update_pg(Position const& new_pg) override;
    // step
    double const step();

  private:
    void update_pb();
    ParticleParameter params_;

    std::function<double const(Position const&)> problem_func_;
    // current
    Velocity velocity_;
    Position position_;
    double cost_;
    // pb
    Position pb_;
    double cost_pb_;
    // pg
    Position pg_;
    double cost_pg_;

    std::vector<Position> history_positions_;
};

} // namespace pso

#endif