#include "Eigen/Dense"
#include "numeric"
#include "particle.h"
#include "particle_parameter.h"
#include "problem_functions.h"
#include "string"
#include "swarm.h"
#include "swarm_parameter.h"

int main(int argc, char* argv[]) {
    if (argc < 6) { // if not all args are set
        std::cout << "./main particles iterations v_max x_bounds function_no\n";
        std::cout << "\t1: Rosenbrock Function\n\t2: Drop Wave Function\n\t3: "
                     "Levy N13 Function\n\t4: Ackley Function\n";
        return 1;
    }
    // params
    const unsigned int population_size = std::stod(argv[1]);
    const unsigned int iterations = std::stod(argv[2]);
    const double v_max_input = (double)std::stod(argv[3]);
    const int x_spawn = std::stod(argv[4]);
    const pso::Velocity v_max{v_max_input, v_max_input};
    // function and function name
    std::function<double const(pso::Position const&)> problem_function;
    std::string problem_function_name;
    switch (std::stoi(argv[5])) {
    case 1:
        problem_function = pso::ProblemFunctions::rosenbrock_function;
        problem_function_name = "Rosenbrock Function";
        break;
    case 2:
        problem_function = pso::ProblemFunctions::drop_wave;
        problem_function_name = "Drop Wave Function";
        break;
    case 3:
        problem_function = pso::ProblemFunctions::levy_n13_function;
        problem_function_name = "Levy N13 Function";
        break;
    case 4:
        problem_function = pso::ProblemFunctions::ackley_function;
        problem_function_name = "Ackley Function";
        break;
    default:
        std::cout << "Using default problem function: Drop Wave Function\n";
        problem_function = pso::ProblemFunctions::drop_wave;
        problem_function_name = "Drop Wave Function";
        break;
    }
    srand((unsigned int)time(0));

    // parameter
    const pso::ParticleParameter particle_params(0.9, 0.5, 1.49, 1.49,
                                                 iterations, v_max, x_spawn);
    const pso::SwarmParameter swarm_params(population_size, problem_function,
                                           problem_function_name,
                                           particle_params);

    // pso simulation
    pso::Swarm* swarm = new pso::Swarm(swarm_params);
    swarm->minimize();
    swarm->print_summary();
    swarm->summary_to_csv();
}