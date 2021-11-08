#ifndef I_SWARM_H
#define I_SWARM_H

namespace pso {
class ISwarm
{
  public:
	~ISwarm() = default;
	// main
	virtual void minimize() = 0;
	// to csv
	virtual void print_summary() const = 0;
	virtual void summary_to_csv() const = 0;
};
} // namespace pso

#endif