#include "swarm.h"



namespace pso{

Swarm::Swarm(SwarmParameter const& swarm_parameter)
: swarm_parameter_(swarm_parameter)
{
    for(unsigned int i = 0; i<swarm_parameter_.population_size;i++){
        particles_.push_back(new Particle(swarm_parameter_.particle_parameter, swarm_parameter_.problem_func, swarm_parameter_.particle_parameter.x_spawn));
    }
    pg_ = particles_[0]->pb();
}


void Swarm::minimize()
{
    Eigen::Vector3d tmp_p;
    for(unsigned int i=0;i<swarm_parameter_.particle_parameter.iterations;i++){
        for(auto const& particle : particles_){
        tmp_p = particle->step();
        if(tmp_p.z() < pg_.z()){
            pg_ = tmp_p;
        }
        particle->set_pg(pg_);
    }
    history_min_cost.push_back(pg_.z());
    }
}


void Swarm::print_summary() const
{
    std::cout << "Summary of Swarm:" << std::endl;
    std::cout << "\tProblem Function: " << swarm_parameter_.function_name << std::endl;
    std::cout << "\tPopulation size: " << swarm_parameter_.population_size << std::endl;
    std::cout << "\tIterations: " << swarm_parameter_.particle_parameter.iterations << std::endl;
    std::cout << "\tv_max: " << swarm_parameter_.particle_parameter.v_max.x() << ", " << swarm_parameter_.particle_parameter.v_max.y() << std::endl;
    std::cout << "\tx_spawn: " << swarm_parameter_.particle_parameter.x_spawn << std::endl;
    std::cout << "\tCoefficients:" << std::endl;
    std::cout << "\t\tw: " << swarm_parameter_.particle_parameter.w_start <<" -> " << swarm_parameter_.particle_parameter.w_end << "\n\t\tc1: " << swarm_parameter_.particle_parameter.c1 << "\n\t\tc2: " << swarm_parameter_.particle_parameter.c2 << std::endl;
    std::cout << "\tpg: [" << pg_.x() << ", " << pg_.y() << ", " << pg_.z() << "]\n";
}


void Swarm::summary_to_csv() const
{
    // position history of each particle
    {
        unsigned int particle_num = 0;
        for(auto const& particle : particles_){
            std::ofstream csvfile;
            csvfile.open("./data/positions/history_" + std::to_string(particle_num) + ".csv");
            auto history = particle->position_history();
            for(auto const& position : history){
                csvfile << position.x() << "," << position.y() << "\n";
            }
            particle_num++;
        }
    }
    // min cost history
    {
        std::ofstream csvfile;
        csvfile.open("./data/swarm_min_cost_history.csv");
        for(auto const& pg : history_min_cost){
            csvfile << pg << "\n";
        }
    }
    // swarm summary
    {
        std::ofstream csvfile;
        csvfile.open("./data/swarm_summary.csv");
        csvfile << "population_size,function_name,v_max,x_spawn,iterations\n";
        csvfile << swarm_parameter_.population_size << "," << swarm_parameter_.function_name << ",";
        csvfile << swarm_parameter_.particle_parameter.v_max.x() << "," << swarm_parameter_.particle_parameter.x_spawn << ",";
        csvfile << swarm_parameter_.particle_parameter.iterations<<"\n";
    }
}

} // namespace pso