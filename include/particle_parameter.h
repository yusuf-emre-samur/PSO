#ifndef PARTICLE_PARAMETER_H
#define PARTICLE_PARAMETER_H
#include "Eigen/Dense"

namespace pso {

using Scalar = double;
using Position = Eigen::Matrix<Scalar, 2, 1>;
using Velocity = Eigen::Matrix<Scalar, 2, 1>;

class ParticleParameter
{
  public:
    ParticleParameter(double const& _w_start, double const& _w_end,
                      double const& _c1, double const& _c2,
                      unsigned int const& iterations, Velocity const& v_max,
                      unsigned int const& x_spawn)
        : iterations(iterations), v_max(v_max), x_spawn(x_spawn)
    {
        w = _w_start;
        w_start = _w_start;
        w_end = _w_end;
        c1 = _c1;
        c2 = _c2;
    }
    ~ParticleParameter() = default;

    void cut_vmax(Velocity* const v) const
    {
        if (v->x() > v_max.x()) {
            v->x() = v_max.x();
        }
        if (v->y() > v_max.y()) {
            v->y() = v_max.y();
        }
    };

    void update_w()
    {
        w -= (w_start - w_end) * 1 / iterations;
    }
    // Position const& check_vmax();

    const unsigned int iterations;
    const Velocity v_max;
    const unsigned int x_spawn;
    double c1;
    double c2;
    double w_start;
    double w_end;
    double w;
};

} // namespace pso

#endif