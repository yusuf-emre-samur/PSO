#include "particle.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0, 1);

namespace pso {

Particle::Particle(ParticleParameter particle_params,
				   std::function<double const(Position const&)> problem_func,
				   unsigned int const& x_spawn)
	: params_(particle_params)
{
	std::default_random_engine rand_gen;
	std::uniform_real_distribution<double> rand_dist(-(double)x_spawn,
													 (double)x_spawn);

	problem_func_ = problem_func;
	// random start velocity
	velocity_ = Velocity::Random(2, 1);
	// random start position
	position_ = Position::Random(2, 1) * rand_dist(rand_gen);
	pb_ = position_;
	pg_ = position_;
	// cost
	cost_ = problem_func_(position_);
	cost_pb_ = cost_;
	cost_pg_ = cost_;
}

// get
Position const& Particle::p() const
{
	return position_;
}

Position const& Particle::pb() const
{
	return pb_;
}

double Particle::cost_pb() const
{
	return cost_pb_;
}

std::vector<Position> const& Particle::position_history() const
{
	return history_positions_;
}

ParticleParameter const& Particle::particle_parameter() const
{
	return params_;
}

// upadte
void Particle::update_pg(Position const& new_pg)
{
	pg_ = new_pg;
}

// step
double const Particle::step()
{
	// decrease w
	params_.update_w();
	// calculate velocity and cut to v_max, then p+=v
	velocity_ = params_.w * velocity_ +
				params_.c1 * dis(gen) * (pg_ - position_) +
				params_.c2 * dis(gen) * (pb_ - position_);
	params_.cut_vmax(&velocity_);
	position_ += velocity_;
	cost_ = problem_func_(position_);
	update_pb();
	history_positions_.push_back(position_);
	return cost_pb_;
}

void Particle::update_pb()
{
	if ( cost_ < cost_pb_ ) {
		cost_pb_ = cost_;
	}
	if ( cost_ < cost_pg_ ) {
		cost_pg_ = cost_;
	}
}

} // namespace pso