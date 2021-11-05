#include "particle.h"

std::random_device rd;
std::mt19937 gen(rd());  
std::uniform_real_distribution<float> dis(0, 1);

namespace pso{

Particle::Particle(ParticleParameter particle_params, std::function<double const (Position const&)> problem_func, unsigned int const& x_spawn)
: params_(particle_params)
{   
    std::default_random_engine rand_gen;
    std::uniform_real_distribution<double> rand_dist(-(double)x_spawn, (double)x_spawn);

    problem_func_= problem_func;
    velocity_ = Velocity::Random(2,1);
    position_ = Position::Random(3,1) * rand_dist(rand_gen);
    position_.z() = problem_func_(position_);
    pb_ = position_;
    pg_ = position_;
}




// get
Position const& Particle::pb() const
{
    return pb_;
}

Position const& Particle::p() const 
{
    return position_;
}

std::vector<Position> const& Particle::position_history() const
{
    return history_positions_;
}

ParticleParameter const& Particle::particle_parameter() const
{
    return params_;
}

//upadte
void Particle::update_pg(Position const& new_pg)
{
    pg_ = new_pg;
}

//set 
void Particle::set_pg(Position const& new_pg){
    pg_ = new_pg;
}

//step
Position const& Particle::step(){
    params_.update_w();
    // calculate velocity and cuty to v_max, then p+=v
    velocity_ = params_.w * velocity_ + params_.c1 * dis(gen) * (pg_(Eigen::seq(0,1))) - position_(Eigen::seq(0,1)) + params_.c2 * dis(gen) * (pb_(Eigen::seq(0,1)) - position_(Eigen::seq(0,1)));
    params_.cut_vmax(&velocity_);
    position_ += Position(velocity_.x(), velocity_.y(), 0);
    position_.z() = problem_func_(position_);
    update_pb();
    history_positions_.push_back(position_);
    return position_;
}

void Particle::update_pb(){
    if (position_.z() < pb_.z()){
        pb_ = position_;
    }
    if (position_.z() < pg_.z()){
        pg_ = position_;
    }
}

} // namespace pso