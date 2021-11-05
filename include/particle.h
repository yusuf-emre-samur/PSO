#ifndef PARTICLE_H
#define PARTICLE_H
#include "random"
#include "vector"
#include "iostream"
#include "functional"
#include "Eigen/Dense"
#include "i_particle.h"
#include "particle_parameter.h"



namespace pso{

class Particle : public IParticle
{
    public:
        Particle(ParticleParameter particle_params, std::function<double const(Position const&)> problem_func, unsigned int const& x_spawn);
        ~Particle() = default;

        
        // get
        Position const& pb() const override;
        Position const& p() const override;
        ParticleParameter const& particle_parameter() const;
        std::vector<Position> const& position_history() const override;
        //upadte
        void update_pg(Position const& new_pg) override;
        // set
        void set_pg(Position const& new_pg) override;
        // step
        Position const& step();

    private:
        void update_pb();
        ParticleParameter params_;

        std::function<double const (Position const&)> problem_func_;

        Velocity velocity_;
        Position position_;
        Position pb_;
        Position pg_;
        std::vector<Position> history_positions_;
};

}

#endif