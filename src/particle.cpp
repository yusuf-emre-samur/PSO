#include "particle.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(0, 1);

namespace pso {

Particle::Particle(ParticleParameter particle_params,
				   std::function<double const(Position const&)> problem_func,
				   unsigned int const& x_spawn)
	: params_(particle_params)
{
	std::uniform_real_distribution<double> rand_dist(-(double)x_spawn,
													 (double)x_spawn);

	this->problem_func_ = problem_func;
	// random start velocity
	this->velocity_ = Velocity::Random(2, 1);
	// random start position
	this->position_ = Position::Random(2, 1) * rand_dist(rd);
	this->pb_ = position_;
	this->pg_ = position_;
	// cost
	this->cost_ = this->problem_func_(this->position_);
	this->cost_pb_ = this->cost_;
	this->cost_pg_ = this->cost_;
}

// get
Position const& Particle::p() const
{
	return this->position_;
}

Position const& Particle::pb() const
{
	return this->pb_;
}

double Particle::cost_pb() const
{
	return this->cost_pb_;
}

std::vector<Position> const& Particle::position_history() const
{
	return this->history_positions_;
}

ParticleParameter const& Particle::particle_parameter() const
{
	return this->params_;
}

// upadte
void Particle::update_pg(const Position& new_pg)
{
	this->pg_ = new_pg;
}

// step
double const Particle::step()
{
	// decrease w
	this->params_.update_w();
	// calculate velocity and cut to v_max, then p+=v
	this->velocity_ =
		this->params_.w * this->velocity_ +
		this->params_.c1 * dis(gen) * (this->pg_ - this->position_) +
		this->params_.c2 * dis(gen) * (this->pb_ - this->position_);
	this->params_.cut_vmax(&velocity_);
	this->position_ += velocity_;
	this->cost_ = this->problem_func_(this->position_);
	this->update_pb();
	this->history_positions_.push_back(this->position_);
	return this->cost_pb_;
}

void Particle::update_pb()
{
	if ( cost_ < this->cost_pb_ ) {
		this->cost_pb_ = cost_;
	}
	if ( cost_ < this->cost_pg_ ) {
		this->cost_pg_ = cost_;
	}
}

} // namespace pso